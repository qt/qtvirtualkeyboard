// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
    \nativetype QVirtualKeyboardObserver
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qtvirtualkeyboard-internal-qml
    \brief Acts as a hub for keyboard event notifications.
*/

/*!
    \class QVirtualKeyboardObserver
    \inmodule QtVirtualKeyboard
    \ingroup qtvirtualkeyboard-cpp-for-devs
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
