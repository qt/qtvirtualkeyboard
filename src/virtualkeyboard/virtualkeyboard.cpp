// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/virtualkeyboard_p.h>
#include <QtVirtualKeyboard/private/virtualkeyboardattachedtype_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \qmltype VirtualKeyboard
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qmlclass
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
        VirtualKeyboard.extraDictionaries: ["myDictionary"]
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
    \qmlattachedproperty list VirtualKeyboard::extraDictionaries

    Sets active user dictionaries in this context.
*/

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
