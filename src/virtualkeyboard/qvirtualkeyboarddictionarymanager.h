/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

#ifndef QVIRTUALKEYBOARDDICTIONARYMANAGER_H
#define QVIRTUALKEYBOARDDICTIONARYMANAGER_H

#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QStringList>
#include <QObject>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardDictionary;
class QVirtualKeyboardDictionaryManagerPrivate;

class QVIRTUALKEYBOARD_EXPORT QVirtualKeyboardDictionaryManager : public QObject
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
