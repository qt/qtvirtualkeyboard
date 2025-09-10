// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtHunspellInputMethod/private/hunspellworker_p.h>
#include <QList>
#include <QFileInfo>
#include <QRegularExpression>
#include <QElapsedTimer>
#include <QFile>
#include <QDir>
#include <QtAlgorithms>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::HunspellTask
    \internal
*/

/*!
    \class QtVirtualKeyboard::HunspellLoadDictionaryTask
    \internal
*/

HunspellLoadDictionaryTask::HunspellLoadDictionaryTask(const QString &locale, const QStringList &searchPaths) :
    HunspellTask(),
    hunspellPtr(nullptr),
    locale(locale),
    searchPaths(searchPaths)
{
}

void HunspellLoadDictionaryTask::run()
{
    Q_ASSERT(hunspellPtr != nullptr);

    qCDebug(lcHunspell) << "HunspellLoadDictionaryTask::run(): locale:" << locale;

    if (*hunspellPtr) {
        Hunspell_destroy(*hunspellPtr);
        *hunspellPtr = nullptr;
    }

    QString affPath;
    QString dicPath;
    for (const QString &searchPath : searchPaths) {
        affPath = QStringLiteral("%1/%2.aff").arg(searchPath, locale);
        if (QFileInfo::exists(affPath)) {
            dicPath = QStringLiteral("%1/%2.dic").arg(searchPath, locale);
            if (QFileInfo::exists(dicPath))
                break;
            dicPath.clear();
        }
        affPath.clear();
    }

    if (!affPath.isEmpty() && !dicPath.isEmpty()) {
        *hunspellPtr = Hunspell_create(affPath.toUtf8().constData(), dicPath.toUtf8().constData());
        if (*hunspellPtr) {
            /*  Make sure the encoding used by the dictionary is supported
                by the QStringConverter.
            */
            if (!QStringConverter::encodingForName(Hunspell_get_dic_encoding(*hunspellPtr))) {
                qCWarning(lcHunspell) << "The Hunspell dictionary" << dicPath << "cannot be used because it uses an unknown text codec" << QLatin1String(Hunspell_get_dic_encoding(*hunspellPtr));
                Hunspell_destroy(*hunspellPtr);
                *hunspellPtr = nullptr;
            }
        }
    } else {
        qCWarning(lcHunspell).nospace() << "Hunspell dictionary is missing for " << locale << ". Search paths " << searchPaths;
    }

    emit completed(*hunspellPtr != nullptr);
}

/*!
    \class QtVirtualKeyboard::HunspellBuildSuggestionsTask
    \internal
*/

void HunspellBuildSuggestionsTask::run()
{
    if (wordList->isEmpty())
        return;

    wordList->clearSuggestions();
    QString word = wordList->wordAt(0);

    /*  Select text codec based on the dictionary encoding.
        Hunspell_get_dic_encoding() should always return at least
        "ISO8859-1", but you can never be too sure.
     */
    textDecoder = QStringDecoder(Hunspell_get_dic_encoding(hunspell));
    textEncoder = QStringEncoder(Hunspell_get_dic_encoding(hunspell));
    if (!textDecoder.isValid() || !textEncoder.isValid())
        return;

    char **slst = nullptr;
    int n = Hunspell_suggest(hunspell, &slst, QByteArray { textEncoder(word) }.constData());
    if (n > 0) {
        /*  Collect word candidates from the Hunspell suggestions.
            Insert word completions in the beginning of the list.
        */
        const int firstWordCompletionIndex = wordList->size();
        int lastWordCompletionIndex = firstWordCompletionIndex;
        bool suggestCapitalization = false;
        for (int i = 0; i < n; i++) {
            QString wordCandidate(textDecoder(slst[i]));
            wordCandidate.replace(QChar(0x2019), QLatin1Char('\''));
            QString normalizedWordCandidate = removeAccentsAndDiacritics(wordCandidate);
            /*  Prioritize word Capitalization */
            if (!wordCandidate.compare(word, Qt::CaseInsensitive)) {
                if (suggestCapitalization) {
                    bool wordCandidateIsCapital = wordCandidate.at(0).isUpper();
                    bool wordIsCapital = word.at(0).isUpper();
                    if (wordCandidateIsCapital == wordIsCapital) {
                        if (wordCandidateIsCapital)
                            wordCandidate = wordCandidate.toLower();
                        else
                            wordCandidate[0] = wordCandidate.at(0).toUpper();
                    }
                    wordList->insertWord(1, wordCandidate);
                    lastWordCompletionIndex++;
                    suggestCapitalization = true;
                }
            /*  Prioritize word completions, missing punctuation or missing accents */
            } else if ((normalizedWordCandidate.size() > word.size() &&
                        normalizedWordCandidate.startsWith(word)) ||
                       wordCandidate.contains(QLatin1Char('\''))) {
                wordList->insertWord(lastWordCompletionIndex++, wordCandidate);
            } else {
                wordList->appendWord(wordCandidate);
            }
        }
        /*  Prioritize words with missing spaces next to word completions.
        */
        for (int i = lastWordCompletionIndex; i < wordList->size(); i++) {
            QString wordCandidate(wordList->wordAt(i));
            if (wordCandidate.contains(QLatin1String(" "))) {
                wordList->updateWord(i, wordCandidate, wordList->wordFlagsAt(i) | HunspellWordList::CompoundWord);
                if (i != lastWordCompletionIndex) {
                    wordList->moveWord(i, lastWordCompletionIndex);
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
        if (autoCorrect && wordList->size() > 1 && (!spellCheck(word) || suggestCapitalization)) {
            if (lastWordCompletionIndex > firstWordCompletionIndex || levenshteinDistance(word, wordList->wordAt(firstWordCompletionIndex)) < 3)
                wordList->setIndex(firstWordCompletionIndex);
        }
    }
    Hunspell_free_list(hunspell, &slst, n);

    for (int i = 0, count = wordList->size(); i < count; ++i) {
        HunspellWordList::Flags flags;
        wordList->wordAt(i, word, flags);
        if (flags.testFlag(HunspellWordList::CompoundWord))
            continue;
        if (Hunspell_spell(hunspell, QByteArray { textEncoder(word) }.constData()) != 0)
            wordList->updateWord(i, word, wordList->wordFlagsAt(i) | HunspellWordList::SpellCheckOk);
    }
}

bool HunspellBuildSuggestionsTask::spellCheck(const QString &word)
{
    if (!hunspell)
        return false;
    if (word.contains(QRegularExpression(QLatin1String("[0-9]"))))
        return true;
    return Hunspell_spell(hunspell, QByteArray { textEncoder(word) }.constData()) != 0;
}

// source: http://en.wikipedia.org/wiki/Levenshtein_distance
int HunspellBuildSuggestionsTask::levenshteinDistance(const QString &s, const QString &t)
{
    if (s == t)
        return 0;
    if (s.size() == 0)
        return t.size();
    if (t.size() == 0)
        return s.size();
    QList<int> v0(t.size() + 1);
    QList<int> v1(t.size() + 1);
    for (int i = 0; i < v0.size(); i++)
        v0[i] = i;
    for (int i = 0; i < s.size(); i++) {
        v1[0] = i + 1;
        for (int j = 0; j < t.size(); j++) {
            int cost = (s[i].toLower() == t[j].toLower()) ? 0 : 1;
            v1[j + 1] = qMin(qMin(v1[j] + 1, v0[j + 1] + 1), v0[j] + cost);
        }
        for (int j = 0; j < v0.size(); j++)
            v0[j] = v1[j];
    }
    return v1[t.size()];
}

QString HunspellBuildSuggestionsTask::removeAccentsAndDiacritics(const QString& s)
{
    QString normalized = s.normalized(QString::NormalizationForm_D);
    for (int i = 0; i < normalized.size();) {
        QChar::Category category = normalized[i].category();
        if (category <= QChar::Mark_Enclosing) {
            normalized.remove(i, 1);
        } else {
            i++;
        }
    }
    return normalized;
}

/*!
    \class QtVirtualKeyboard::HunspellUpdateSuggestionsTask
    \internal
*/

void HunspellUpdateSuggestionsTask::run()
{
    emit updateSuggestions(wordList, tag);
}

void HunspellAddWordTask::run()
{
    auto fromUtf16 = QStringEncoder(Hunspell_get_dic_encoding(hunspell));
    if (!fromUtf16.isValid())
        return;

    QString tmpWord;
    tmpWord.reserve(64);
    for (int i = 0, count = wordList->size(); i < count; ++i) {
        const QString word(wordList->wordAt(i));
        if (word.size() < 2)
            continue;
        Hunspell_add(hunspell, QByteArray { fromUtf16(word) }.constData());
        if (HunspellAddWordTask::alternativeForm(word, tmpWord))
            Hunspell_add(hunspell, QByteArray { fromUtf16(tmpWord) }.constData());
    }
}

bool HunspellAddWordTask::alternativeForm(const QString &word, QString &alternativeForm)
{
    if (word.size() < 2)
        return false;
    if (!word.mid(1).isLower())
        return false;

    const QChar initial(word.at(0));
    const QChar newInitial = initial.isUpper() ? initial.toLower() : initial.toUpper();
    if (newInitial == initial)
        return false;

    alternativeForm.truncate(0);
    alternativeForm.append(word);
    alternativeForm[0] = newInitial;

    return true;
}

void HunspellRemoveWordTask::run()
{
    auto fromUtf16 = QStringEncoder(Hunspell_get_dic_encoding(hunspell));
    if (!fromUtf16.isValid())
        return;

    QString tmpWord;
    tmpWord.reserve(64);
    for (int i = 0, count = wordList->size(); i < count; ++i) {
        const QString word(wordList->wordAt(i));
        if (word.isEmpty())
            continue;
        Hunspell_remove(hunspell, QByteArray { fromUtf16(word) }.constData());
        if (HunspellAddWordTask::alternativeForm(word, tmpWord))
            Hunspell_remove(hunspell, QByteArray { fromUtf16(tmpWord) }.constData());
    }
}

void HunspellLoadWordListTask::run()
{
    wordList->clear();

    QFile inputFile(filePath);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream inStream(&inputFile);
        QString word;
        word.reserve(64);
        while (inStream.readLineInto(&word)) {
            if (!word.isEmpty())
                wordList->appendWord(word);
        }
        inputFile.close();
    }
}

void HunspellSaveWordListTask::run()
{
    QFile outputFile(filePath);
    if (!QFileInfo::exists(filePath))
        QDir().mkpath(QFileInfo(filePath).absoluteDir().path());
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream outStream(&outputFile);
        for (int i = 0, count = wordList->size(); i < count; ++i) {
            const QString word(wordList->wordAt(i));
            outStream << word.toUtf8() << '\n';
        }
        outputFile.close();
    }
}

void HunspellFilterWordTask::run()
{
    if (filterList->isEmpty())
        return;

    filterList->rebuildSearchIndex();

    for (int i = startIndex, count = wordList->size(); i < count;) {
        if (filterList->contains(wordList->wordAt(i))) {
            wordList->removeWordAt(i);
            --count;
        } else {
            ++i;
        }
    }
}

void HunspellBoostWordTask::run()
{
    if (boostList->isEmpty())
        return;

    boostList->rebuildSearchIndex();

    const QString word(wordList->wordAt(0));
    const QString wordCompletion(boostList->findWordCompletion(word));
    if (!wordCompletion.isEmpty()) {
        int from = wordList->indexOfWord(wordCompletion);
        if (from != 1) {
            int to;
            for (to = 1; to < wordList->size() && wordList->wordAt(to).startsWith(word); ++to)
                ;
            if (from != -1) {
                if (to < from)
                    wordList->moveWord(from, to);
            } else {
                wordList->insertWord(to, wordCompletion, HunspellWordList::SpellCheckOk);
            }
        }
    }
}

/*!
    \class QtVirtualKeyboard::HunspellWorker
    \internal
*/

HunspellWorker::HunspellWorker(QObject *parent) :
    QThread(parent),
    idleSema(),
    taskSema(),
    taskLock(),
    hunspell(nullptr)
{
    abort = false;
    qRegisterMetaType<QSharedPointer<HunspellWordList>>("QSharedPointer<HunspellWordList>");
}

HunspellWorker::~HunspellWorker()
{
    abort = true;
    taskSema.release(1);
    wait();
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
}

void HunspellWorker::waitForAllTasks()
{
    qCDebug(lcHunspell) << "waitForAllTasks enter";
    while (isRunning()) {
        idleSema.acquire();
        QMutexLocker guard(&taskLock);
        if (taskList.isEmpty()) {
            idleSema.release();
            break;
        }
        idleSema.release();
    }
    qCDebug(lcHunspell) << "waitForAllTasks leave";
}

void HunspellWorker::run()
{
    QElapsedTimer perf;
    while (!abort) {
        idleSema.release();
        taskSema.acquire();
        if (abort)
            break;
        idleSema.acquire();
        QSharedPointer<HunspellTask> currentTask;
        {
            QMutexLocker guard(&taskLock);
            if (!taskList.isEmpty()) {
                currentTask = taskList.front();
                taskList.pop_front();
            }
        }
        if (currentTask) {
            QSharedPointer<HunspellLoadDictionaryTask> loadDictionaryTask(currentTask.objectCast<HunspellLoadDictionaryTask>());
            if (loadDictionaryTask)
                loadDictionaryTask->hunspellPtr = &hunspell;
            else if (hunspell)
                currentTask->hunspell = hunspell;
            else
                continue;
            perf.start();
            currentTask->run();
            qCDebug(lcHunspell) << QString(QLatin1String(currentTask->metaObject()->className()) + QLatin1String("::run(): time:")).toLatin1().constData() << perf.elapsed() << "ms";
        }
    }
    if (hunspell) {
        Hunspell_destroy(hunspell);
        hunspell = nullptr;
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
