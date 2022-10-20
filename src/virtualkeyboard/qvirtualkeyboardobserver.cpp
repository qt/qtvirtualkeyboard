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
