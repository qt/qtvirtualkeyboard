/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
