/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

#include "hunspellworker.h"
#include <QVector>
#include <QTextCodec>

void HunspellBuildSuggestionsTask::run()
{
    wordList->list.append(word);
    wordList->index = 0;

    /*  Select text codec based on the dictionary encoding.
        Hunspell_get_dic_encoding() should always return at least
        "ISO8859-1", but you can never be too sure.
     */
    textCodec = QTextCodec::codecForName(Hunspell_get_dic_encoding(hunspell));
    if (!textCodec)
        return;

    char **slst = 0;
    int n = Hunspell_suggest(hunspell, &slst, textCodec->fromUnicode(word).constData());
    if (n > 0) {
        /*  Collect word candidates from the Hunspell suggestions.
            Insert word completions in the beginning of the list.
        */
        const int firstWordCompletionIndex = wordList->list.length();
        int lastWordCompletionIndex = firstWordCompletionIndex;
        bool suggestCapitalization = false;
        for (int i = 0; i < n; i++) {
            QString wordCandidate(textCodec->toUnicode(slst[i]));
            wordCandidate.replace(QChar(0x2019), '\'');
            if (wordCandidate.compare(word) != 0) {
                QString normalizedWordCandidate = removeAccentsAndDiacritics(wordCandidate);
                /*  Prioritize word Capitalization */
                if (!suggestCapitalization && !wordCandidate.compare(word, Qt::CaseInsensitive)) {
                    wordList->list.insert(1, wordCandidate);
                    lastWordCompletionIndex++;
                    suggestCapitalization = true;
                /*  Prioritize word completions, missing punctuation or missing accents */
                } else if (normalizedWordCandidate.startsWith(word) ||
                    wordCandidate.contains(QChar('\''))) {
                    wordList->list.insert(lastWordCompletionIndex++, wordCandidate);
                } else {
                    wordList->list.append(wordCandidate);
                }
            }
        }
        /*  Prioritize words with missing spaces next to word completions.
        */
        for (int i = lastWordCompletionIndex; i < wordList->list.length(); i++) {
            if (QString(wordList->list.at(i)).replace(" ", "").compare(word) == 0) {
                if (i != lastWordCompletionIndex) {
                    wordList->list.move(i, lastWordCompletionIndex);
                }
                lastWordCompletionIndex++;
            }
        }
        /*  Do spell checking and suggest the first candidate, if:
            - the word matches partly the suggested word; or
            - the quality of the suggested word is good enough.

            The quality is measured here using the Levenshtein Distance,
            which may be suboptimal for the purpose, but gives some clue
            how much the suggested word differs from the given word.
        */
        if (autoCorrect && wordList->list.length() > 1 && (!spellCheck(word) || suggestCapitalization)) {
            if (lastWordCompletionIndex > firstWordCompletionIndex || levenshteinDistance(word, wordList->list.at(firstWordCompletionIndex)) < 3)
                wordList->index = firstWordCompletionIndex;
        }
    }
    Hunspell_free_list(hunspell, &slst, n);
}

bool HunspellBuildSuggestionsTask::spellCheck(const QString &word)
{
    if (!hunspell)
        return false;
    if (word.contains(QRegExp("[0-9]")))
        return true;
    return Hunspell_spell(hunspell, textCodec->fromUnicode(word).constData()) != 0;
}

// source: http://en.wikipedia.org/wiki/Levenshtein_distance
int HunspellBuildSuggestionsTask::levenshteinDistance(const QString &s, const QString &t)
{
    if (s == t)
        return 0;
    if (s.length() == 0)
        return t.length();
    if (t.length() == 0)
        return s.length();
    QVector<int> v0(t.length() + 1);
    QVector<int> v1(t.length() + 1);
    for (int i = 0; i < v0.size(); i++)
        v0[i] = i;
    for (int i = 0; i < s.size(); i++) {
        v1[0] = i + 1;
        for (int j = 0; j < t.length(); j++) {
            int cost = (s[i].toLower() == t[j].toLower()) ? 0 : 1;
            v1[j + 1] = qMin(qMin(v1[j] + 1, v0[j + 1] + 1), v0[j] + cost);
        }
        for (int j = 0; j < v0.size(); j++)
            v0[j] = v1[j];
    }
    return v1[t.length()];
}

QString HunspellBuildSuggestionsTask::removeAccentsAndDiacritics(const QString& s)
{
    QString normalized = s.normalized(QString::NormalizationForm_D);
    for (int i = 0; i < normalized.length();) {
        QChar::Category category = normalized[i].category();
        if (category <= QChar::Mark_Enclosing) {
            normalized.remove(i, 1);
        } else {
            i++;
        }
    }
    return normalized;
}

void HunspellUpdateSuggestionsTask::run()
{
    emit updateSuggestions(wordList->list, wordList->index);
}

HunspellWorker::HunspellWorker(Hunhandle *hunspell, QObject *parent) :
    QThread(parent),
    taskSema(),
    taskLock(),
    hunspell(hunspell),
    abort(false)
{
}

HunspellWorker::~HunspellWorker()
{
    abort = true;
    taskSema.release(1);
    wait();
    if (hunspell) {
        Hunspell_destroy(hunspell);
        hunspell = 0;
    }
}

void HunspellWorker::addTask(QSharedPointer<HunspellTask> task)
{
    if (task) {
        QMutexLocker guard(&taskLock);
        taskList.append(task);
        taskSema.release();
    }
}

void HunspellWorker::removeAllTasks()
{
    QMutexLocker guard(&taskLock);
    taskList.clear();
    if (taskSema.available())
        taskSema.acquire(taskSema.available());
}

void HunspellWorker::run()
{
    while (!abort) {
        taskSema.acquire();
        if (abort)
            break;
        QSharedPointer<HunspellTask> currentTask;
        {
            QMutexLocker guard(&taskLock);
            if (!taskList.isEmpty()) {
                currentTask = taskList.front();
                taskList.pop_front();
            }
        }
        if (currentTask) {
            currentTask->hunspell = hunspell;
            currentTask->run();
        }
    }
}
