/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
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

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.VirtualKeyboard 2.15

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
