// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.VirtualKeyboard

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Modal Popup Test")
    id: root

    Page {
        Button {
            id: popupButton
            Layout.fillWidth: true
            font.pixelSize: 20
            text: qsTr("Popup")
            onClicked: {
                passwordsuspendInput.focus = true
                suspendPopup.open()
            }
        }

        TextField {
            placeholderText: qsTr("Test")
            implicitWidth: 200
            focus: true
            font.pixelSize: 24
            x: popupButton.width
        }

    }

    Popup {
        id: suspendPopup
        x: root.width /2 - suspendPopup.width /2
        y: root.height /8
        modal: true
        focus: true
        closePolicy: Popup.NoAutoClose

        contentItem: GridLayout {
            rows: 2
            columns: 1
            columnSpacing: 20
            rowSpacing: 20

            TextField {
                id: passwordsuspendInput
                placeholderText: qsTr("Password")
                implicitWidth: 200
                focus: true
                font.pixelSize: 24

                onAccepted: loginsuspendButton.clicked()
            }

            Button {
                id: loginsuspendButton
                text: "Done"
                flat: true
                implicitWidth: 200
                font.pixelSize: 24
                onClicked: {
                    passwordsuspendInput.text =""
                    suspendPopup.close()
                }
            }
        }
    }

    InputPanel {
        id: inputPanel
        x: 0
        y: root.height
        width: root.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: root.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
