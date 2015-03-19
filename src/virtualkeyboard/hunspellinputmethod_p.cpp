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
#include <QFileInfo>
#include <QDir>
#include "virtualkeyboarddebug.h"
#include <QTextCodec>
#include <QtCore/QLibraryInfo>

HunspellInputMethodPrivate::HunspellInputMethodPrivate(HunspellInputMethod *q_ptr) :
    AbstractInputMethodPrivate(),
    q_ptr(q_ptr),
    hunspellWorker(0),
    locale(),
    word(),
    wordCandidates(),
    activeWordIndex(-1),
    wordCompletionPoint(2),
    ignoreUpdate(false),
    autoSpaceAllowed(false)
{
}

HunspellInputMethodPrivate::~HunspellInputMethodPrivate()
{
}

bool HunspellInputMethodPrivate::createHunspell(const QString &locale)
{
    if (this->locale != locale) {
        hunspellWorker.reset(0);
        Hunhandle *hunspell = 0;
        QString hunspellDataPath(QString::fromLatin1(qgetenv("QT_VIRTUALKEYBOARD_HUNSPELL_DATA_PATH").constData()));
        const QString pathListSep(
#if defined(Q_OS_WIN32)
            QStringLiteral(";")
#else
            QStringLiteral(":")
#endif
        );
        QStringList searchPaths(hunspellDataPath.split(pathListSep, QString::SkipEmptyParts));
        searchPaths.append(QDir(QLibraryInfo::location(QLibraryInfo::DataPath) + "/qtvirtualkeyboard/hunspell").absolutePath());
#if !defined(Q_OS_WIN32)
        searchPaths.append(QStringLiteral("/usr/share/hunspell"));
        searchPaths.append(QStringLiteral("/usr/share/myspell/dicts"));
#endif
        foreach (const QString &searchPath, searchPaths) {
            QByteArray affpath(QString("%1/%2.aff").arg(searchPath).arg(locale).toUtf8());
            QByteArray dpath(QString("%1/%2.dic").arg(searchPath).arg(locale).toUtf8());
            if (QFileInfo(dpath).exists()) {
                hunspell = Hunspell_create(affpath.constData(), dpath.constData());
                if (hunspell) {
                    /*  Make sure the encoding used by the dictionary is supported
                        by the QTextCodec.
                    */
                    if (QTextCodec::codecForName(Hunspell_get_dic_encoding(hunspell))) {
                        break;
                    } else {
                        qWarning() << "The Hunspell dictionary" << QString("%1/%2.dic").arg(searchPath).arg(locale) << "cannot be used because it uses an unknown text codec" << QString(Hunspell_get_dic_encoding(hunspell));
                        Hunspell_destroy(hunspell);
                        hunspell = 0;
                    }
                }
            }
        }
        if (!hunspell) {
            VIRTUALKEYBOARD_DEBUG() << "Missing Hunspell dictionary for locale" << locale << "in" << searchPaths;
            this->locale.clear();
            return false;
        }
        this->locale = locale;
        hunspellWorker.reset(new HunspellWorker(hunspell));
        if (!hunspellWorker) {
            Hunspell_destroy(hunspell);
            this->locale.clear();
            return false;
        }
        hunspellWorker->start();
    }
    return true;
}

bool HunspellInputMethodPrivate::updateSuggestions()
{
    bool wordCandidateListChanged = false;
    if (!word.isEmpty()) {
        if (hunspellWorker)
            hunspellWorker->removeAllTasks();
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
        hunspellWorker->removeAllTasks();
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
