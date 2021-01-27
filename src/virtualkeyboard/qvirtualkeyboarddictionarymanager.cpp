/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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

#include <QtVirtualKeyboard/qvirtualkeyboarddictionarymanager.h>
#include <QtVirtualKeyboard/qvirtualkeyboarddictionary.h>
#include <QtGlobal>
#include <QSet>

#include <QtCore/private/qobject_p.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardDictionaryManagerPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QVirtualKeyboardDictionaryManager)
public:
    QVirtualKeyboardDictionaryManagerPrivate(QVirtualKeyboardDictionaryManager *q)
    {
        q_ptr = q;
    }

    void updateActiveDictionaries()
    {
        Q_Q(QVirtualKeyboardDictionaryManager);
        QSet<QString> newActiveDictionaries(baseDictionaries);
        newActiveDictionaries.unite(extraDictionaries);
        if (activeDictionaries != newActiveDictionaries) {
            activeDictionaries = newActiveDictionaries;
            emit q->activeDictionariesChanged();
        }
    }

    QSet<QString> baseDictionaries;
    QSet<QString> extraDictionaries;
    QSet<QString> activeDictionaries;
    QMap<QString, QVirtualKeyboardDictionary *> dictionaries;
};

struct QVirtualKeyboardDictionaryManagerSingleton {
    QVirtualKeyboardDictionaryManager instance;
};

Q_GLOBAL_STATIC(QVirtualKeyboardDictionaryManagerSingleton, singleton)

QVirtualKeyboardDictionaryManager::QVirtualKeyboardDictionaryManager(QObject *parent) :
    QObject(*new QVirtualKeyboardDictionaryManagerPrivate(this), parent)
{
    Q_D(QVirtualKeyboardDictionaryManager);
    connect(this, &QVirtualKeyboardDictionaryManager::baseDictionariesChanged,
            [=](){ d->updateActiveDictionaries(); });
    connect(this, &QVirtualKeyboardDictionaryManager::extraDictionariesChanged,
            [=](){ d->updateActiveDictionaries(); });
}

QVirtualKeyboardDictionaryManager *QVirtualKeyboardDictionaryManager::instance()
{
    return &singleton->instance;
}

QStringList QVirtualKeyboardDictionaryManager::availableDictionaries() const
{
    Q_D(const QVirtualKeyboardDictionaryManager);
    return d->dictionaries.keys();
}

QStringList QVirtualKeyboardDictionaryManager::baseDictionaries() const
{
    Q_D(const QVirtualKeyboardDictionaryManager);
    return d->baseDictionaries.values();
}

void QVirtualKeyboardDictionaryManager::setBaseDictionaries(const QStringList &baseDictionaries)
{
    Q_D(QVirtualKeyboardDictionaryManager);
    QSet<QString> newBaseDictionaries(baseDictionaries.begin(), baseDictionaries.end());
    const QStringList availableDict = availableDictionaries();
    newBaseDictionaries.intersect(QSet<QString>(availableDict.begin(), availableDict.end()));
    if (d->baseDictionaries != newBaseDictionaries) {
        d->baseDictionaries = newBaseDictionaries;
        emit baseDictionariesChanged();
    }
}

QStringList QVirtualKeyboardDictionaryManager::extraDictionaries() const
{
    Q_D(const QVirtualKeyboardDictionaryManager);
    return d->extraDictionaries.values();
}

void QVirtualKeyboardDictionaryManager::setExtraDictionaries(const QStringList &extraDictionaries)
{
    Q_D(QVirtualKeyboardDictionaryManager);
    QSet<QString> newExtraDictionaries(extraDictionaries.begin(), extraDictionaries.end());
    const QStringList availableDict = availableDictionaries();
    newExtraDictionaries.intersect(QSet<QString>(availableDict.begin(), availableDict.end()));
    if (d->extraDictionaries != newExtraDictionaries) {
        d->extraDictionaries = newExtraDictionaries;
        emit extraDictionariesChanged();
    }
}

QStringList QVirtualKeyboardDictionaryManager::activeDictionaries() const
{
    Q_D(const QVirtualKeyboardDictionaryManager);
    return d->activeDictionaries.values();
}

QVirtualKeyboardDictionary *QVirtualKeyboardDictionaryManager::createDictionary(const QString &name)
{
    Q_D(QVirtualKeyboardDictionaryManager);

    QVirtualKeyboardDictionary *dictionary = d->dictionaries.value(name);
    if (!dictionary) {
        dictionary = new QVirtualKeyboardDictionary(name, this);
        d->dictionaries[name] = dictionary;
        emit availableDictionariesChanged();
    }

    return dictionary;
}

QVirtualKeyboardDictionary *QVirtualKeyboardDictionaryManager::dictionary(const QString &name) const
{
    Q_D(const QVirtualKeyboardDictionaryManager);

    return d->dictionaries.value(name);
}

QT_END_NAMESPACE
