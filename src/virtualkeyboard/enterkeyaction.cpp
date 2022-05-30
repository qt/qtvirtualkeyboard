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

#include <QtVirtualKeyboard/private/enterkeyaction_p.h>
#include <QtVirtualKeyboard/private/enterkeyactionattachedtype_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \qmltype EnterKeyAction
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \brief Provides attached properties for customizing the enter key.

    The EnterKeyAction type provides attached properties which allows
    customizing the enter key button of the keyboard.

    The EnterKeyAction must be used directly inside the item
    receiving input focus, e.g. TextInput.

    For example:
    \code
    TextInput {
        id: myInput
        EnterKeyAction.enabled: myInput.text.length > 0 || myInput.inputMethodComposing
        EnterKeyAction.label: "Next"
        Keys.onReleased: {
            if (event.key === Qt.Key_Return) {
                // execute action
            }
        }
    }
    \endcode
*/

/*!
    \class QtVirtualKeyboard::EnterKeyAction
    \internal
*/

/*!
    \internal
*/
EnterKeyActionAttachedType *EnterKeyAction::qmlAttachedProperties(QObject *object)
{
    return new EnterKeyActionAttachedType(object);
}

/*!
    \qmlattachedproperty int EnterKeyAction::actionId

    Sets the action id for the enter key in virtual keyboard.
    When the action id is set, it takes preference over the label
    and sets the icon for the enter key.

    \list
        \li \c EnterKeyAction.None No action defined.
        \li \c EnterKeyAction.Go Action performs go operation.
               For example taking user to the entered url.
        \li \c EnterKeyAction.Search Action performs search operation.
        \li \c EnterKeyAction.Send Action sends the entered text.
        \li \c EnterKeyAction.Next Action moves the input focus to
               the next field accepting text input.
        \li \c EnterKeyAction.Done Same as \c EnterKeyAction.Next,
               except all the text input is done.
    \endlist
*/

/*!
    \qmlattachedproperty string EnterKeyAction::label

    Sets the label for the enter key in virtual keyboard.
*/

/*!
    \qmlattachedproperty bool EnterKeyAction::enabled

    Enables or disables the enter key button in virtual keyboard.
*/

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
