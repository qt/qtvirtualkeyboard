/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 2.0

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
            color: "#2B2C2E"
            cursorVisible: activeFocus
            passwordCharacter: "\u2022"
            font.pixelSize: textField.fontPixelSize
            selectionColor: Qt.rgba(0.0, 0.0, 0.0, 0.15)
            selectedTextColor: color
            selectByMouse: true
            width: Math.max(flickable.width, implicitWidth)-2

            Binding {
                target: textInput
                property: "passwordMaskDelay"
                value: textField.passwordMaskDelay
                when: textInput.hasOwnProperty("passwordMaskDelay")
            }
        }
    }
}
