/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 1.3

TextBase {
    id: textField

    property alias color: textInput.color
    property alias text: textInput.text
    property alias textWidth: textInput.width
    property alias readOnly: textInput.readOnly
    property alias inputMethodHints: textInput.inputMethodHints
    property alias validator: textInput.validator
    property alias echoMode: textInput.echoMode
    property int passwordMaskDelay: 1000

    editor: textInput
    mouseParent: flickable

    Flickable {
        id: flickable

        x: 12
        clip: true
        width: parent.width-24
        height: parent.height
        flickableDirection: Flickable.HorizontalFlick
        interactive: contentWidth - 4 > width

        contentWidth: textInput.width+2
        contentHeight: textInput.height
        TextInput {
            id: textInput

            EnterKeyAction.actionId: textField.enterKeyAction
            EnterKeyAction.label: textField.enterKeyText
            EnterKeyAction.enabled: textField.enterKeyEnabled

            y: 6
            focus: true
            color: "#EEEEEE"
            cursorVisible: activeFocus
            passwordCharacter: "\u2022"
            font.pixelSize: textField.fontPixelSize
            selectionColor: Qt.rgba(1.0, 1.0, 1.0, 0.5)
            selectedTextColor: Qt.rgba(0.0, 0.0, 0.0, 0.8)
            width: Math.max(flickable.width, implicitWidth)-2
            onActiveFocusChanged: if (!activeFocus) deselect()

            Binding {
                target: textInput
                property: "passwordMaskDelay"
                value: textField.passwordMaskDelay
                when: textInput.hasOwnProperty("passwordMaskDelay")
            }
        }
    }
}
