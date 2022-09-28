// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDOBSERVER_H
#define QVIRTUALKEYBOARDOBSERVER_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardObserverPrivate;

class Q_VIRTUALKEYBOARD_EXPORT QVirtualKeyboardObserver : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QVirtualKeyboardObserver)
    Q_DISABLE_COPY(QVirtualKeyboardObserver)
    Q_PROPERTY(QVariant layout READ layout NOTIFY layoutChanged)
    QML_NAMED_ELEMENT(KeyboardObserver)
    QML_ADDED_IN_VERSION(6, 1)

public:
    explicit QVirtualKeyboardObserver(QObject *parent = nullptr);

    QVariant layout();

Q_SIGNALS:
    void layoutChanged();

private Q_SLOTS:
    void invalidateLayout();
};

QT_END_NAMESPACE

#endif // QVIRTUALKEYBOARDOBSERVER_H
