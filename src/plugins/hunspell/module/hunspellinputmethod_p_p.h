// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef HUNSPELLINPUTMETHOD_P_P_H
#define HUNSPELLINPUTMETHOD_P_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtHunspellInputMethod/qhunspellinputmethod_global.h>
#include <QtHunspellInputMethod/private/hunspellwordlist_p.h>
#include <QtVirtualKeyboard/private/qvirtualkeyboardabstractinputmethod_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class HunspellInputMethod;
class HunspellWorker;

class Q_HUNSPELLINPUTMETHOD_EXPORT HunspellInputMethodPrivate : public QVirtualKeyboardAbstractInputMethodPrivate
{
public:
    Q_DECLARE_PUBLIC(HunspellInputMethod)

    HunspellInputMethodPrivate(HunspellInputMethod *q_ptr);
    ~HunspellInputMethodPrivate();

    enum DictionaryState {
        DictionaryNotLoaded,
        DictionaryLoading,
        DictionaryReady
    };

    bool createHunspell(const QString &locale);
    void reset();
    bool updateSuggestions();
    bool clearSuggestions(bool clearInputWord = false);
    void clearSuggestionsRelatedTasks();
    bool isAutoSpaceAllowed() const;
    bool isValidInputChar(const QChar &c) const;
    bool isJoiner(const QChar &c) const;
    QString customDictionaryLocation(const QString &dictionaryType) const;
    void loadCustomDictionary(const QSharedPointer<HunspellWordList> &wordList, const QString &dictionaryType) const;
    void saveCustomDictionary(const QSharedPointer<HunspellWordList> &wordList, const QString &dictionaryType) const;
    void addToHunspell(const QSharedPointer<HunspellWordList> &wordList) const;
    void removeFromHunspell(const QSharedPointer<HunspellWordList> &wordList) const;
    void removeFromDictionary(const QString &word);
    void addToDictionary();
    void updateSuggestionsCompleted(const QSharedPointer<HunspellWordList> &wordList, int tag);
    void dictionaryLoadCompleted(bool success);

    HunspellInputMethod *q_ptr;
    QScopedPointer<HunspellWorker> hunspellWorker;
    QString locale;
    HunspellWordList wordCandidates;
    int wordCompletionPoint;
    bool ignoreUpdate;
    bool autoSpaceAllowed;
    DictionaryState dictionaryState;
    QSharedPointer<HunspellWordList> userDictionaryWords;
    QSharedPointer<HunspellWordList> blacklistedWords;
    int wordCandidatesUpdateTag;
    static const int userDictionaryMaxSize;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // HUNSPELLINPUTMETHOD_P_P_H
