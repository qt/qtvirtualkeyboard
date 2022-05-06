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

#include "qvirtualkeyboardobserver.h"

#include <QtCore/private/qobject_p.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardObserverPrivate : public QObjectPrivate
{
public:
    QVirtualKeyboardObserverPrivate()
    {}

    QVariant layout;
};

/*!
    \qmltype KeyboardObserver
    \instantiates QVirtualKeyboardObserver
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \brief Acts as a hub for keyboard event notifications.
*/

/*!
    \class QVirtualKeyboardObserver
    \inmodule QtVirtualKeyboard
    \brief Acts as a hub for keyboard event notifications.
*/

QVirtualKeyboardObserver::QVirtualKeyboardObserver(QObject *parent) :
    QObject(*new QVirtualKeyboardObserverPrivate, parent)
{
    connect(this, &QVirtualKeyboardObserver::layoutChanged, this, &QVirtualKeyboardObserver::invalidateLayout);
}

/*!
    \property QVirtualKeyboardObserver::layout
    \brief The current keyboard layout expressed as a variant.
*/
/*!
    \qmlproperty variant KeyboardObserver::layout
    \readonly
    \brief The current keyboard layout expressed as a variant.
*/
QVariant QVirtualKeyboardObserver::layout()
{
    Q_D(QVirtualKeyboardObserver);

    if (d->layout.isNull())
        QMetaObject::invokeMethod(this, "scanLayout", Q_RETURN_ARG(QVariant, d->layout));

    return d->layout;
}

void QVirtualKeyboardObserver::invalidateLayout()
{
    Q_D(QVirtualKeyboardObserver);
    d->layout = QVariant();
}

QT_END_NAMESPACE
