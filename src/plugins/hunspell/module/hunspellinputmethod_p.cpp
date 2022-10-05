// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "hunspellinputmethod_p_p.h"
#include "hunspellinputmethod_p.h"
#include "hunspellworker_p.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QStringList>
#include <QDir>
#include <QtCore/QLibraryInfo>
#include <QStandardPaths>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

const int HunspellInputMethodPrivate::userDictionaryMaxSize = 100;

/*!
    \class QtVirtualKeyboard::HunspellInputMethodPrivate
    \internal
*/

HunspellInputMethodPrivate::HunspellInputMethodPrivate(HunspellInputMethod *q_ptr) :
    q_ptr(q_ptr),
    hunspellWorker(new HunspellWorker()),
    locale(),
    wordCompletionPoint(2),
    ignoreUpdate(false),
    autoSpaceAllowed(false),
    dictionaryState(DictionaryNotLoaded),
    userDictionaryWords(new HunspellWordList(userDictionaryMaxSize)),
    blacklistedWords(new HunspellWordList(userDictionaryMaxSize)),
    wordCandidatesUpdateTag(0)
{
    if (hunspellWorker)
        hunspellWorker->start();
}

HunspellInputMethodPrivate::~HunspellInputMethodPrivate()
{
}

bool HunspellInputMethodPrivate::createHunspell(const QString &locale)
{
    Q_Q(HunspellInputMethod);
    if (!hunspellWorker)
        return false;
    if (this->locale != locale) {
        clearSuggestionsRelatedTasks();
        hunspellWorker->waitForAllTasks();
        QString hunspellDataPath(qEnvironmentVariable("QT_VIRTUALKEYBOARD_HUNSPELL_DATA_PATH"));
        const QString pathListSep(
#if defined(Q_OS_WIN32)
            QStringLiteral(";")
#else
            QStringLiteral(":")
#endif
        );
        QStringList searchPaths(hunspellDataPath.split(pathListSep, Qt::SkipEmptyParts));
        const QStringList defaultPaths = QStringList()
                << QDir(QLibraryInfo::path(QLibraryInfo::DataPath) + QStringLiteral("/qtvirtualkeyboard/hunspell")).absolutePath()
#if !defined(Q_OS_WIN32)
                << QStringLiteral("/usr/share/hunspell")
                << QStringLiteral("/usr/share/myspell/dicts")
#endif
                   ;
        for (const QString &defaultPath : defaultPaths) {
            if (!searchPaths.contains(defaultPath))
                searchPaths.append(defaultPath);
        }
        QSharedPointer<HunspellLoadDictionaryTask> loadDictionaryTask(new HunspellLoadDictionaryTask(locale, searchPaths));
        QObjectPrivate::connect(loadDictionaryTask.data(), &HunspellLoadDictionaryTask::completed, this, &HunspellInputMethodPrivate::dictionaryLoadCompleted);
        dictionaryState = HunspellInputMethodPrivate::DictionaryLoading;
        emit q->selectionListsChanged();
        hunspellWorker->addTask(loadDictionaryTask);
        this->locale = locale;

        loadCustomDictionary(userDictionaryWords, QLatin1String("userdictionary"));
        addToHunspell(userDictionaryWords);
        loadCustomDictionary(blacklistedWords, QLatin1String("blacklist"));
        removeFromHunspell(blacklistedWords);
    }
    return true;
}

void HunspellInputMethodPrivate::reset()
{
    if (clearSuggestions(true)) {
        Q_Q(HunspellInputMethod);
        emit q->selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
        emit q->selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, wordCandidates.index());
    }
    autoSpaceAllowed = false;
}

bool HunspellInputMethodPrivate::updateSuggestions()
{
    bool wordCandidateListChanged = false;
    QString word = wordCandidates.wordAt(0);
    if (!word.isEmpty() && dictionaryState != HunspellInputMethodPrivate::DictionaryNotLoaded) {
        wordCandidateListChanged = true;
        if (word.size() >= wordCompletionPoint) {
            if (hunspellWorker) {
                QSharedPointer<HunspellWordList> wordList(new HunspellWordList(wordCandidates));

                // Clear obsolete tasks from the worker queue
                clearSuggestionsRelatedTasks();

                // Build suggestions
                QSharedPointer<HunspellBuildSuggestionsTask> buildSuggestionsTask(new HunspellBuildSuggestionsTask());
                buildSuggestionsTask->wordList = wordList;
                buildSuggestionsTask->autoCorrect = false;
                hunspellWorker->addTask(buildSuggestionsTask);

                // Filter out blacklisted word (sometimes Hunspell suggests,
                // e.g. with different text case)
                QSharedPointer<HunspellFilterWordTask> filterWordTask(new HunspellFilterWordTask());
                filterWordTask->wordList = wordList;
                filterWordTask->filterList = blacklistedWords;
                hunspellWorker->addTask(filterWordTask);

                // Boost words from user dictionary
                QSharedPointer<HunspellBoostWordTask> boostWordTask(new HunspellBoostWordTask());
                boostWordTask->wordList = wordList;
                boostWordTask->boostList = userDictionaryWords;
                hunspellWorker->addTask(boostWordTask);

                // Update word candidate list
                QSharedPointer<HunspellUpdateSuggestionsTask> updateSuggestionsTask(new HunspellUpdateSuggestionsTask());
                updateSuggestionsTask->wordList = wordList;
                updateSuggestionsTask->tag = ++wordCandidatesUpdateTag;
                QObjectPrivate::connect(updateSuggestionsTask.data(), &HunspellUpdateSuggestionsTask::updateSuggestions, this, &HunspellInputMethodPrivate::updateSuggestionsCompleted);
                hunspellWorker->addTask(updateSuggestionsTask);
            }
        }
    } else {
        wordCandidateListChanged = clearSuggestions();
    }
    return wordCandidateListChanged;
}

bool HunspellInputMethodPrivate::clearSuggestions(bool clearInputWord)
{
    clearSuggestionsRelatedTasks();
    return clearInputWord ? wordCandidates.clear() : wordCandidates.clearSuggestions();
}

void HunspellInputMethodPrivate::clearSuggestionsRelatedTasks()
{
    if (hunspellWorker) {
        hunspellWorker->removeAllTasksOfType<HunspellBuildSuggestionsTask>();
        hunspellWorker->removeAllTasksOfType<HunspellFilterWordTask>();
        hunspellWorker->removeAllTasksOfType<HunspellBoostWordTask>();
        hunspellWorker->removeAllTasksOfType<HunspellUpdateSuggestionsTask>();
    }
}

bool HunspellInputMethodPrivate::isAutoSpaceAllowed() const
{
    Q_Q(const HunspellInputMethod);
    if (!autoSpaceAllowed)
        return false;
    if (q->inputEngine()->inputMode() == QVirtualKeyboardInputEngine::InputMode::Numeric)
        return false;
    QVirtualKeyboardInputContext *ic = q->inputContext();
    if (!ic)
        return false;
    Qt::InputMethodHints inputMethodHints = ic->inputMethodHints();
    return !inputMethodHints.testFlag(Qt::ImhUrlCharactersOnly) &&
           !inputMethodHints.testFlag(Qt::ImhEmailCharactersOnly);
}

bool HunspellInputMethodPrivate::isValidInputChar(const QChar &c) const
{
    if (c.isLetterOrNumber())
        return true;
    if (isJoiner(c))
        return true;
    if (c.isMark())
        return true;
    return false;
}

bool HunspellInputMethodPrivate::isJoiner(const QChar &c) const
{
    if (c.isPunct() || c.isSymbol()) {
        Q_Q(const HunspellInputMethod);
        QVirtualKeyboardInputContext *ic = q->inputContext();
        if (ic) {
            Qt::InputMethodHints inputMethodHints = ic->inputMethodHints();
            if (inputMethodHints.testFlag(Qt::ImhUrlCharactersOnly) || inputMethodHints.testFlag(Qt::ImhEmailCharactersOnly))
                return QString(QStringLiteral(":/?#[]@!$&'()*+,;=-_.%")).contains(c);
        }
        ushort unicode = c.unicode();
        if (unicode == Qt::Key_Apostrophe || unicode == Qt::Key_Minus)
            return true;
    }
    return false;
}

QString HunspellInputMethodPrivate::customDictionaryLocation(const QString &dictionaryType) const
{
    if (dictionaryType.isEmpty() || locale.isEmpty())
        return QString();

    QString location = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
    if (location.isEmpty())
        return QString();

    return QStringLiteral("%1/qtvirtualkeyboard/hunspell/%2-%3.txt")
                    .arg(location)
                    .arg(dictionaryType)
                    .arg(locale);
}

void HunspellInputMethodPrivate::loadCustomDictionary(const QSharedPointer<HunspellWordList> &wordList,
                                                      const QString &dictionaryType) const
{
    QSharedPointer<HunspellLoadWordListTask> loadWordsTask(new HunspellLoadWordListTask());
    loadWordsTask->filePath = customDictionaryLocation(dictionaryType);
    loadWordsTask->wordList = wordList;
    hunspellWorker->addTask(loadWordsTask);
}

void HunspellInputMethodPrivate::saveCustomDictionary(const QSharedPointer<HunspellWordList> &wordList,
                                                      const QString &dictionaryType) const
{
    QSharedPointer<HunspellSaveWordListTask> saveWordsTask(new HunspellSaveWordListTask());
    saveWordsTask->filePath = customDictionaryLocation(dictionaryType);
    saveWordsTask->wordList = wordList;
    hunspellWorker->addTask(saveWordsTask);
}

void HunspellInputMethodPrivate::addToHunspell(const QSharedPointer<HunspellWordList> &wordList) const
{
    QSharedPointer<HunspellAddWordTask> addWordTask(new HunspellAddWordTask());
    addWordTask->wordList = wordList;
    hunspellWorker->addTask(addWordTask);
}

void HunspellInputMethodPrivate::removeFromHunspell(const QSharedPointer<HunspellWordList> &wordList) const
{
    QSharedPointer<HunspellRemoveWordTask> removeWordTask(new HunspellRemoveWordTask());
    removeWordTask->wordList = wordList;
    hunspellWorker->addTask(removeWordTask);
}

void HunspellInputMethodPrivate::removeFromDictionary(const QString &word)
{
    if (userDictionaryWords->removeWord(word) > 0) {
        saveCustomDictionary(userDictionaryWords, QLatin1String("userdictionary"));
    } else if (!blacklistedWords->contains(word)) {
        blacklistedWords->appendWord(word);
        saveCustomDictionary(blacklistedWords, QLatin1String("blacklist"));
    }

    QSharedPointer<HunspellWordList> wordList(new HunspellWordList());
    wordList->appendWord(word);
    removeFromHunspell(wordList);

    updateSuggestions();
}

void HunspellInputMethodPrivate::addToDictionary()
{
    Q_Q(HunspellInputMethod);
    // This feature is not allowed when dealing with sensitive information
    const Qt::InputMethodHints inputMethodHints(q->inputContext()->inputMethodHints());
    const bool userDictionaryEnabled =
            !inputMethodHints.testFlag(Qt::ImhHiddenText) &&
            !inputMethodHints.testFlag(Qt::ImhSensitiveData);
    if (!userDictionaryEnabled)
        return;

    if (wordCandidates.isEmpty())
        return;

    QString word;
    HunspellWordList::Flags wordFlags;
    const int activeWordIndex = wordCandidates.index();
    wordCandidates.wordAt(activeWordIndex, word, wordFlags);
    if (activeWordIndex == 0) {
        if (blacklistedWords->removeWord(word) > 0) {
            saveCustomDictionary(blacklistedWords, QLatin1String("blacklist"));
        } else if (word.size() > 1 && !wordFlags.testFlag(HunspellWordList::SpellCheckOk) && !userDictionaryWords->contains(word)) {
            userDictionaryWords->appendWord(word);
            saveCustomDictionary(userDictionaryWords, QLatin1String("userdictionary"));
        } else {
            // Avoid adding words to Hunspell which are too short or passed spell check
            return;
        }

        QSharedPointer<HunspellWordList> wordList(new HunspellWordList());
        wordList->appendWord(word);
        addToHunspell(wordList);
    } else {
        // Check if found in the user dictionary and move as last in the list.
        // This way the list is always ordered by use.
        // If userDictionaryMaxSize is greater than zero the number of words in the
        // list will be limited to that amount. By pushing last used items to end of
        // list we can avoid (to certain extent) removing frequently used words.
        int userDictionaryIndex = userDictionaryWords->indexOfWord(word);
        if (userDictionaryIndex != -1) {
            userDictionaryWords->moveWord(userDictionaryIndex, userDictionaryWords->size() - 1);
            saveCustomDictionary(userDictionaryWords, QLatin1String("userdictionary"));
        }
    }
}

void HunspellInputMethodPrivate::updateSuggestionsCompleted(const QSharedPointer<HunspellWordList> &wordList, int tag)
{
    if (dictionaryState == HunspellInputMethodPrivate::DictionaryNotLoaded) {
        qCDebug(lcHunspell) << "updateSuggestions: skip (dictionary not loaded)";
        Q_Q(HunspellInputMethod);
        q->update();
        return;
    }
    if (wordCandidatesUpdateTag != tag) {
        qCDebug(lcHunspell) << "updateSuggestions: skip tag" << tag << "current" << wordCandidatesUpdateTag;
        return;
    }
    QString word(wordCandidates.wordAt(0));
    wordCandidates = *wordList;
    if (wordCandidates.wordAt(0).compare(word) != 0)
        wordCandidates.updateWord(0, word);
    Q_Q(HunspellInputMethod);
    emit q->selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
    emit q->selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, wordCandidates.index());
}

void HunspellInputMethodPrivate::dictionaryLoadCompleted(bool success)
{
    Q_Q(HunspellInputMethod);
    QVirtualKeyboardInputContext *ic = q->inputContext();
    if (!ic)
        return;

    QList<QVirtualKeyboardSelectionListModel::Type> oldSelectionLists = q->selectionLists();
    dictionaryState = success ? HunspellInputMethodPrivate::DictionaryReady :
                                HunspellInputMethodPrivate::DictionaryNotLoaded;
    QList<QVirtualKeyboardSelectionListModel::Type> newSelectionLists = q->selectionLists();
    if (oldSelectionLists != newSelectionLists)
        emit q->selectionListsChanged();
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
