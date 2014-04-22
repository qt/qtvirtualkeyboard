/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "enterkeyaction.h"
#include "enterkeyactionattachedtype.h"

/*!
    \qmltype EnterKeyAction
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
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
    \internal
*/
EnterKeyActionAttachedType *EnterKeyAction::qmlAttachedProperties(QObject *object)
{
    return new EnterKeyActionAttachedType(object);
}

/*!
    \qmlattachedproperty string EnterKeyAction::label

    Sets the label for the enter key in virtual keyboard.
*/

/*!
    \qmlattachedproperty bool EnterKeyAction::enabled

    Enables or disables the enter key button in virtual keyboard.
*/
