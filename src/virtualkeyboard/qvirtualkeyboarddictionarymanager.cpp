// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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

/*!
    \class QVirtualKeyboardDictionaryManager

    \inmodule QtVirtualKeyboard
    \ingroup qtvirtualkeyboard-cpp-for-apps

    \brief Dictionary management for application-defined dictionaries.

    This class allows you to manage dictionaries for virtual keyboard input
    methods. Dictionaries are application-defined and can be activated in the
    desired context.

    \note Dictionaries do not refer to the built-in dictionaries of the input
    method, but to the application's own dictionaries (for example, a phonebook
    application).

    The following operations are supported by the dictionary manager:
    \list
        \li Create dictionaries using the \c createDictionary() function.
        \li Add or modify content of the dictionary instance.
        \li Activate dictionaries by adding them to the list of
            \l {baseDictionaries}{base dictionaries} or
            \l {extraDictionaries}{extra dictionaries}.
    \endlist

    To activate dictionaries from QML, use the \l VirtualKeyboard attached
    type.
*/

QVirtualKeyboardDictionaryManager::QVirtualKeyboardDictionaryManager(QObject *parent) :
    QObject(*new QVirtualKeyboardDictionaryManagerPrivate(this), parent)
{
    Q_D(QVirtualKeyboardDictionaryManager);
    connect(this, &QVirtualKeyboardDictionaryManager::baseDictionariesChanged,
            [=](){ d->updateActiveDictionaries(); });
    connect(this, &QVirtualKeyboardDictionaryManager::extraDictionariesChanged,
            [=](){ d->updateActiveDictionaries(); });
}

/*!
    Returns the singleton instance of the QVirtualKeyboardDictionaryManager.

    All the functionalities must be called from the main thread.
 */

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

/*!
    Create a dictionary with the given \a name or return the dictionary if it
    already exists.

    The dictionary instance is owned by the dictionary manager and must not be
    destroyed manually. To free memory allocated for the dictionary, the
    application may reset the \l{QVirtualKeyboardDictionary::contents}{contents}
    of the dictionary.

    \sa dictionary()
 */

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

/*!
    Returns an existing dictionary with the given \a name if it exists, otherwise returns
    \nullptr.

    \sa createDictionary()
 */

QVirtualKeyboardDictionary *QVirtualKeyboardDictionaryManager::dictionary(const QString &name) const
{
    Q_D(const QVirtualKeyboardDictionaryManager);

    return d->dictionaries.value(name);
}

/*!
    \property QVirtualKeyboardDictionaryManager::availableDictionaries
    \brief the list of all dictionaries.

    This property holds the names of all existing dictionaries.
*/

/*!
    \property QVirtualKeyboardDictionaryManager::baseDictionaries
    \brief the list of currently active base dictionaries.

    This property holds the names of base dictionaries. The application manages
    this property.
*/

/*!
    \property QVirtualKeyboardDictionaryManager::extraDictionaries
    \brief the list of currently active extra dictionaries.

    This property holds the names of extra dictionaries. The application manages
    this property.
*/

/*!
    \property QVirtualKeyboardDictionaryManager::activeDictionaries
    \brief the list of currently active dictionaries.

    This property holds the list of active dictionaries, which is a combination
    of unique names included in baseDictionaries and extraDictionaries.
*/

QT_END_NAMESPACE
