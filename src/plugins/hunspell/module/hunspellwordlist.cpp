// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "hunspellwordlist_p.h"
#include <QtAlgorithms>
#include <hunspell/hunspell.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::HunspellWordList
    \internal
*/

HunspellWordList::HunspellWordList(int limit) :
    _index(0),
    _limit(limit)
{
}

HunspellWordList::HunspellWordList(HunspellWordList &other)
{
    *this = other;
}

HunspellWordList &HunspellWordList::operator=(HunspellWordList &other)
{
    if (this != &other) {
        QMutexLocker guard(&_lock);
        QMutexLocker otherGuard(&other._lock);
        _list = other._list;
        _flags = other._flags;
        _index = other._index;
        _limit = other._limit;
        _searchIndex = other._searchIndex;
    }
    return *this;
}

int HunspellWordList::index() const
{
    return _index < _list.size() ? _index : -1;
}

void HunspellWordList::setIndex(int index)
{
    QMutexLocker guard(&_lock);
    _index = index;
}

bool HunspellWordList::clear()
{
    QMutexLocker guard(&_lock);
    bool result = !_list.isEmpty();
    _list.clear();
    _flags.clear();
    _index = 0;
    _searchIndex.clear();
    return result;
}

bool HunspellWordList::clearSuggestions()
{
    QMutexLocker guard(&_lock);
    if (_list.isEmpty())
        return false;

    _searchIndex.clear();
    if (_list.size() > 1) {
        QString word = _list.at(0);
        Flags flags = _flags.at(0);
        _list.clear();
        _flags.clear();
        if (!word.isEmpty()) {
            _index = 0;
            _list.append(word);
            _flags.append(flags);
        }
        return true;
    } else if (_list.at(0).isEmpty()) {
        _list.clear();
        _flags.clear();
        _index = 0;
        return true;
    }
    return false;
}

bool HunspellWordList::hasSuggestions() const
{
    return _list.size() > 1;
}

int HunspellWordList::size() const
{
    return _list.size();
}

int HunspellWordList::isEmpty() const
{
    return _list.isEmpty() || _list.at(0).isEmpty();
}

bool HunspellWordList::contains(const QString &word)
{
    QMutexLocker guard(&_lock);

    // Use index search when the search index is available.
    // This provides a lot faster search than QList::contains().
    // Search index is available when it has been rebuilt using
    // rebuildSearchIndex() method. Search index is automatically
    // cleared when the word list is modified.
    if (!_searchIndex.isEmpty()) {
        Q_ASSERT(_searchIndex.size() == _list.size());

        SearchContext searchContext(word, _list);
        return std::binary_search(_searchIndex.begin(), _searchIndex.end(), -1, [searchContext](const int &a, const int &b) {
            const QString &wordA = (a == -1) ? searchContext.word : searchContext.list[a];
            const QString &wordB = (b == -1) ? searchContext.word : searchContext.list[b];
            return wordA.compare(wordB, Qt::CaseInsensitive) < 0;
        });
    }

    return _list.contains(word, Qt::CaseInsensitive);
}

QString HunspellWordList::findWordCompletion(const QString &word)
{
    QMutexLocker guard(&_lock);

    if (!_searchIndex.isEmpty()) {
        Q_ASSERT(_searchIndex.size() == _list.size());

        SearchContext searchContext(word, _list);
        auto match = std::lower_bound(_searchIndex.begin(), _searchIndex.end(), -1, [searchContext](const int &a, const int &b) {
            const QString &wordA = (a == -1) ? searchContext.word : searchContext.list[a];
            const QString &wordB = (b == -1) ? searchContext.word : searchContext.list[b];
            return wordA.compare(wordB, Qt::CaseInsensitive) < 0;
        });

        if (match == _searchIndex.end())
            return QString();

        if (!word.compare(_list[*match], Qt::CaseInsensitive)) {
            match++;
            if (match == _searchIndex.end())
                return QString();
        }

        return _list[*match].startsWith(word, Qt::CaseInsensitive) ? _list[*match] : QString();
    }

    QString bestMatch;
    for (int i = 0, count = _list.size(); i < count; ++i) {
        const QString &wordB(_list[i]);
        if (wordB.size() > bestMatch.size() &&
                word.size() < wordB.size() &&
                wordB.startsWith(word, Qt::CaseInsensitive))
            bestMatch = wordB;
    }

    return bestMatch;
}

int HunspellWordList::indexOfWord(const QString &word)
{
    QMutexLocker guard(&_lock);

    if (!_searchIndex.isEmpty()) {
        Q_ASSERT(_searchIndex.size() == _list.size());

        SearchContext searchContext(word, _list);
        auto match = std::lower_bound(_searchIndex.begin(), _searchIndex.end(), -1, [searchContext](int a, int b) {
            const QString &wordA = (a == -1) ? searchContext.word : searchContext.list[a];
            const QString &wordB = (b == -1) ? searchContext.word : searchContext.list[b];
            return wordA.compare(wordB, Qt::CaseInsensitive) < 0;
        });
        return (match != _searchIndex.end()) ? *match : -1;
    }

    return _list.indexOf(word);
}

QString HunspellWordList::wordAt(int index)
{
    QMutexLocker guard(&_lock);

    return index >= 0 && index < _list.size() ? _list.at(index) : QString();
}

void HunspellWordList::wordAt(int index, QString &word, Flags &flags)
{
    QMutexLocker guard(&_lock);
    Q_ASSERT(index >= 0 && index < _list.size());

    word = _list.at(index);
    flags = _flags.at(index);
}

const HunspellWordList::Flags &HunspellWordList::wordFlagsAt(int index)
{
    QMutexLocker guard(&_lock);

    return _flags[index];
}

void HunspellWordList::appendWord(const QString &word, const Flags &flags)
{
    QMutexLocker guard(&_lock);

    _searchIndex.clear();
    if (_limit > 0) {
        while (_list.size() >= _limit) {
            _list.removeAt(0);
            _flags.removeAt(0);
        }
    }
    _list.append(word);
    _flags.append(flags);
}

void HunspellWordList::insertWord(int index, const QString &word, const Flags &flags)
{
    QMutexLocker guard(&_lock);
    Q_ASSERT(_limit == 0);

    _searchIndex.clear();
    _list.insert(index, word);
    _flags.insert(index, flags);
}

void HunspellWordList::updateWord(int index, const QString &word, const Flags &flags)
{
    Q_ASSERT(index >= 0);
    QMutexLocker guard(&_lock);

    if (index < _list.size()) {
        if (word != _list[index])
            _searchIndex.clear();
        _list[index] = word;
        _flags[index] = flags;
    } else {
        _searchIndex.clear();
        _list.append(word);
        _flags.append(flags);
    }
}

void HunspellWordList::moveWord(int from, int to)
{
    QMutexLocker guard(&_lock);

    if (from < 0 || from >= _list.size())
        return;
    if (to < 0 || to >= _list.size())
        return;
    if (from == to)
        return;

    _searchIndex.clear();
    _list.move(from, to);
    _flags.move(from, to);
}

int HunspellWordList::removeWord(const QString &word)
{
    QMutexLocker guard(&_lock);
    int removeCount = 0;
    for (int i = 0, count = _list.size(); i < count;) {
        if (!_list[i].compare(word, Qt::CaseInsensitive)) {
            _list.removeAt(i);
            _flags.removeAt(i);
            --count;
            ++removeCount;
        } else {
            ++i;
        }
    }
    if (removeCount > 0)
        _searchIndex.clear();
    return removeCount;
}

void HunspellWordList::removeWordAt(int index)
{
    QMutexLocker guard(&_lock);

    _list.removeAt(index);
}

void HunspellWordList::rebuildSearchIndex()
{
    QMutexLocker guard(&_lock);
    _searchIndex.clear();

    if (_list.isEmpty())
        return;

    _searchIndex.resize(_list.size());
    std::iota(_searchIndex.begin(), _searchIndex.end(), 0);

    const QStringList list(_list);
    std::sort(_searchIndex.begin(), _searchIndex.end(), [list](int a, int b) { return list[a].compare(list[b], Qt::CaseInsensitive) < 0; });
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
