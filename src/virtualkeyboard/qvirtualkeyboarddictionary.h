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

#ifndef QVIRTUALKEYBOARDDICTIONARY_H
#define QVIRTUALKEYBOARDDICTIONARY_H

#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QStringList>
#include <QObject>

QT_BEGIN_NAMESPACE

class QVIRTUALKEYBOARD_EXPORT QVirtualKeyboardDictionary : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QStringList contents READ contents WRITE setContents NOTIFY contentsChanged)

    explicit QVirtualKeyboardDictionary(const QString &name, QObject *parent = nullptr);
    friend class QVirtualKeyboardDictionaryManager;

public:
    QString name() const;

    QStringList contents() const;
    void setContents(const QStringList &contents);

Q_SIGNALS:
    void contentsChanged();

private:
    const QString _name;
    QStringList _wordList;
};

QT_END_NAMESPACE

#endif // QVIRTUALKEYBOARDDICTIONARY_H
