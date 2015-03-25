/****************************************************************************
**
** Copyright (C) 2015 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

#include "hunspellinputmethod_p.h"
#include "declarativeinputcontext.h"
#include <hunspell/hunspell.h>
#include <QStringList>
#include <QDir>
#include "virtualkeyboarddebug.h"
#include <QTextCodec>
#include <QtCore/QLibraryInfo>

HunspellInputMethodPrivate::HunspellInputMethodPrivate(HunspellInputMethod *q_ptr) :
    AbstractInputMethodPrivate(),
    q_ptr(q_ptr),
    hunspellWorker(new HunspellWorker()),
    locale(),
    word(),
    wordCandidates(),
    activeWordIndex(-1),
    wordCompletionPoint(2),
    ignoreUpdate(false),
    autoSpaceAllowed(false)
{
    if (hunspellWorker)
        hunspellWorker->start();
}

HunspellInputMethodPrivate::~HunspellInputMethodPrivate()
{
}

bool HunspellInputMethodPrivate::createHunspell(const QString &locale)
{
    if (!hunspellWorker)
        return false;
    if (this->locale != locale) {
        hunspellWorker->removeAllTasks();
        QString hunspellDataPath(QString::fromLatin1(qgetenv("QT_VIRTUALKEYBOARD_HUNSPELL_DATA_PATH").constData()));
        const QString pathListSep(
#if defined(Q_OS_WIN32)
            QStringLiteral(";")
#else
            QStringLiteral(":")
#endif
        );
        QStringList searchPaths(hunspellDataPath.split(pathListSep, QString::SkipEmptyParts));
        const QStringList defaultPaths = QStringList()
                << QDir(QLibraryInfo::location(QLibraryInfo::DataPath) + QStringLiteral("/qtvirtualkeyboard/hunspell")).absolutePath()
#if !defined(Q_OS_WIN32)
                << QStringLiteral("/usr/share/hunspell")
                << QStringLiteral("/usr/share/myspell/dicts")
#endif
                   ;
        foreach (const QString &defaultPath, defaultPaths) {
            if (!searchPaths.contains(defaultPath))
                searchPaths.append(defaultPath);
        }
        QSharedPointer<HunspellLoadDictionaryTask> loadDictionaryTask(new HunspellLoadDictionaryTask(locale, searchPaths));
        hunspellWorker->addTask(loadDictionaryTask);
        this->locale = locale;
    }
    return true;
}

void HunspellInputMethodPrivate::reset()
{
    if (clearSuggestions()) {
        Q_Q(HunspellInputMethod);
        emit q->selectionListChanged(DeclarativeSelectionListModel::WordCandidateList);
        emit q->selectionListActiveItemChanged(DeclarativeSelectionListModel::WordCandidateList, activeWordIndex);
    }
    word.clear();
    autoSpaceAllowed = false;
}

bool HunspellInputMethodPrivate::updateSuggestions()
{
    bool wordCandidateListChanged = false;
    if (!word.isEmpty()) {
        if (hunspellWorker)
            hunspellWorker->removeAllTasksExcept<HunspellLoadDictionaryTask>();
        if (wordCandidates.isEmpty()) {
            wordCandidates.append(word);
            activeWordIndex = 0;
            wordCandidateListChanged = true;
        } else if (wordCandidates.at(0) != word) {
            wordCandidates.replace(0, word);
            activeWordIndex = 0;
            wordCandidateListChanged = true;
        }
        if (word.length() >= wordCompletionPoint) {
            if (hunspellWorker) {
                QSharedPointer<HunspellWordList> wordList(new HunspellWordList());
                QSharedPointer<HunspellBuildSuggestionsTask> buildSuggestionsTask(new HunspellBuildSuggestionsTask());
                buildSuggestionsTask->word = word;
                buildSuggestionsTask->wordList = wordList;
                buildSuggestionsTask->autoCorrect = false;
                hunspellWorker->addTask(buildSuggestionsTask);
                QSharedPointer<HunspellUpdateSuggestionsTask> updateSuggestionsTask(new HunspellUpdateSuggestionsTask());
                updateSuggestionsTask->wordList = wordList;
                Q_Q(HunspellInputMethod);
                q->connect(updateSuggestionsTask.data(), SIGNAL(updateSuggestions(QStringList, int)), SLOT(updateSuggestions(QStringList, int)));
                hunspellWorker->addTask(updateSuggestionsTask);
            }
        } else if (wordCandidates.length() > 1) {
            wordCandidates.clear();
            wordCandidates.append(word);
            activeWordIndex = 0;
            wordCandidateListChanged = true;
        }
    } else {
        wordCandidateListChanged = clearSuggestions();
    }
    return wordCandidateListChanged;
}

bool HunspellInputMethodPrivate::clearSuggestions()
{
    if (hunspellWorker)
        hunspellWorker->removeAllTasksExcept<HunspellLoadDictionaryTask>();
    if (wordCandidates.isEmpty())
        return false;
    wordCandidates.clear();
    activeWordIndex = -1;
    return true;
}

bool HunspellInputMethodPrivate::hasSuggestions() const
{
    return !wordCandidates.isEmpty();
}

bool HunspellInputMethodPrivate::isAutoSpaceAllowed() const
{
    Q_Q(const HunspellInputMethod);
    if (!autoSpaceAllowed)
        return false;
    if (q->inputEngine()->inputMode() != DeclarativeInputEngine::Latin)
        return false;
    DeclarativeInputContext *ic = q->inputContext();
    if (!ic)
        return false;
    Qt::InputMethodHints inputMethodHints = ic->inputMethodHints();
    return !inputMethodHints.testFlag(Qt::ImhUrlCharactersOnly) &&
           !inputMethodHints.testFlag(Qt::ImhEmailCharactersOnly);
}
