// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef HUNSPELLWORDLIST_P_H
#define HUNSPELLWORDLIST_P_H

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

#include <QMutex>
#include <QStringList>
#include <QtHunspellInputMethod/qhunspellinputmethod_global.h>

QT_BEGIN_NAMESPACE

namespace QtVirtualKeyboard {

class Q_HUNSPELLINPUTMETHOD_EXPORT HunspellWordList
{
public:
    enum Flag
    {
        SpellCheckOk = 0x1,
        CompoundWord = 0x2
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    HunspellWordList(int limit = 0);
    HunspellWordList(HunspellWordList &other);

    HunspellWordList &operator=(HunspellWordList &other);

    int index() const;
    void setIndex(int index);
    bool clear();
    bool clearSuggestions();
    bool hasSuggestions() const;
    int size() const;
    int isEmpty() const;
    bool contains(const QString &word);
    QString findWordCompletion(const QString &word);
    int indexOfWord(const QString &word);
    QString wordAt(int index);
    void wordAt(int index, QString &word, Flags &flags);
    const Flags &wordFlagsAt(int index);
    void appendWord(const QString &word, const Flags &flags = Flags());
    void insertWord(int index, const QString &word, const Flags &flags = Flags());
    void updateWord(int index, const QString &word, const Flags &flags = Flags());
    void moveWord(int from, int to);
    int removeWord(const QString &word);
    void removeWordAt(int index);
    void rebuildSearchIndex();

private:
    class SearchContext {
    public:
        SearchContext(const QString &word,
                      const QStringList &list) :
            word(word),
            list(list)
        {}
        const QString &word;
        const QStringList &list;
    };

private:
    QMutex _lock;
    QStringList _list;
    QList<Flags> _flags;
    QList<int> _searchIndex;
    int _index;
    int _limit;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // HUNSPELLWORDLIST_P_H
