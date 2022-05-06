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

#include <QtVirtualKeyboard/private/virtualkeyboard_p.h>
#include <QtVirtualKeyboard/private/virtualkeyboardattachedtype_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \qmltype VirtualKeyboard
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \brief Provides attached properties for customizing the virtual keyboard.
    \since QtQuick.VirtualKeyboard 6.1

    The VirtualKeyboard type provides attached properties which allow
    customizing the virtual keyboard, such as attaching custom dictionaries.

    The VirtualKeyboard must be used directly inside the item
    receiving input focus, e.g. TextInput.

    For example:
    \code
    TextInput {
        VirtualKeyboard.dictionaries: ["myDictionary"]
    }
    \endcode
*/

/*!
    \class QtVirtualKeyboard::VirtualKeyboard
    \internal
*/

/*!
    \internal
*/
VirtualKeyboardAttachedType *VirtualKeyboard::qmlAttachedProperties(QObject *object)
{
    return new VirtualKeyboardAttachedType(object);
}

/*!
    \qmlattachedproperty list VirtualKeyboard::dictionaries

    Sets active user dictionaries in this context.
*/

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
