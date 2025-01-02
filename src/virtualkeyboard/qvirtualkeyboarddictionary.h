// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDDICTIONARY_H
#define QVIRTUALKEYBOARDDICTIONARY_H

#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/QStringList>
#include <QtCore/QObject>

QT_BEGIN_NAMESPACE

class Q_VIRTUALKEYBOARD_EXPORT QVirtualKeyboardDictionary : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QStringList contents READ contents WRITE setContents NOTIFY contentsChanged RESET resetContents)

    explicit QVirtualKeyboardDictionary(const QString &name, QObject *parent = nullptr);
    friend class QVirtualKeyboardDictionaryManager;

public:
    QString name() const;

    QStringList contents() const;
    void setContents(const QStringList &contents);
    void resetContents() { setContents({}); }

Q_SIGNALS:
    void contentsChanged();

private:
    const QString _name;
    QStringList _wordList;
};

QT_END_NAMESPACE

#endif // QVIRTUALKEYBOARDDICTIONARY_H
