// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDDICTIONARYMANAGER_H
#define QVIRTUALKEYBOARDDICTIONARYMANAGER_H

#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/QStringList>
#include <QtCore/QObject>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardDictionary;
class QVirtualKeyboardDictionaryManagerPrivate;

class Q_VIRTUALKEYBOARD_EXPORT QVirtualKeyboardDictionaryManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QVirtualKeyboardDictionaryManager)
    Q_DECLARE_PRIVATE(QVirtualKeyboardDictionaryManager)
    Q_PROPERTY(QStringList availableDictionaries READ availableDictionaries NOTIFY availableDictionariesChanged)
    Q_PROPERTY(QStringList baseDictionaries READ baseDictionaries WRITE setBaseDictionaries NOTIFY baseDictionariesChanged)
    Q_PROPERTY(QStringList extraDictionaries READ extraDictionaries WRITE setExtraDictionaries NOTIFY extraDictionariesChanged)
    Q_PROPERTY(QStringList activeDictionaries READ activeDictionaries NOTIFY activeDictionariesChanged)

    explicit QVirtualKeyboardDictionaryManager(QObject *parent = nullptr);
    friend struct QVirtualKeyboardDictionaryManagerSingleton;

public:
    static QVirtualKeyboardDictionaryManager *instance();

    QStringList availableDictionaries() const;

    QStringList baseDictionaries() const;
    void setBaseDictionaries(const QStringList &baseDictionaries);

    QStringList extraDictionaries() const;
    void setExtraDictionaries(const QStringList &extraDictionaries);

    QStringList activeDictionaries() const;

    QVirtualKeyboardDictionary *createDictionary(const QString &name);
    QVirtualKeyboardDictionary *dictionary(const QString &name) const;

Q_SIGNALS:
    void availableDictionariesChanged();
    void baseDictionariesChanged();
    void extraDictionariesChanged();
    void activeDictionariesChanged();
};

QT_END_NAMESPACE

#endif // QVIRTUALKEYBOARDDICTIONARYMANAGER_H
