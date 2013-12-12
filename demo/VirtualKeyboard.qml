/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

import QtQuick 2.0
import "content"

Image {
    source: "content/images/background.png"

    Flickable {
        id: flickable

        property real scrollMarginVertical: 20

        anchors.fill: parent
        contentWidth: content.width
        contentHeight: content.height
        interactive: contentHeight > height
        flickableDirection: Flickable.VerticalFlick
        children: ScrollBar {}

        MouseArea  {
            id: content

            width: flickable.width
            height: textEditors.height + 24

            onClicked: focus = true

            Column {
                id: textEditors
                spacing: 15
                x: 12; y: 12
                width: parent.width - 26

                Text {
                    color: "#EEEEEE"
                    text: "Tap fields to enter text"
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 22
                }
                TextField {
                    width: parent.width
                    previewText: "One line field"
                    enterKeyText: "Next"
                    onEnterKeyClicked: passwordField.focus = true
                }
                TextField {
                    id: passwordField

                    width: parent.width
                    echoMode: TextInput.PasswordEchoOnEdit
                    previewText: "Password field"
                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhPreferLowercase | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText
                    enterKeyText: "Next"
                    onEnterKeyClicked: numberField.focus = true
                }
                TextField {
                    id: numberField

                    validator: RegExpValidator { regExp: /^[0-9\+\-\#\*\ ]{6,}$/ }
                    width: parent.width
                    previewText: "Phone number field"
                    inputMethodHints: Qt.ImhDialableCharactersOnly
                    enterKeyText: "Next"
                    onEnterKeyClicked: textArea.focus = true
                }
                TextArea {
                    id: textArea

                    width: parent.width
                    previewText: "Multiple lines field"
                    height: Math.max(206, implicitHeight)
                }
            }
        }
    }
}
