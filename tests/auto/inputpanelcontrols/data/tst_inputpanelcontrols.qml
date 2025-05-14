// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtTest
import QtQuick
import QtQuick.Window
import QtQuick.Controls

Rectangle {
    id: container
    width: 800
    height: 640
    color: "blue"

    Component {
        id: textInputComp
        TextEdit {
            anchors.fill: parent
            visible: true
            focus: true
            color: "white"
        }
    }

    TestCase {
        id: testcase
        name: "tst_inputpanelcontrols"
        when: windowShown

        property var inputPanel: null
        property var textInput: null

        function initTestCase() {
            var inputPanelComp = Qt.createComponent("inputpanel/inputpanel.qml")
            compare(inputPanelComp.status, Component.Ready, "Failed to create component: "+inputPanelComp.errorString())
            inputPanel = inputPanelComp.createObject(container)

            textInput = textInputComp.createObject(container)
        }

        function cleanupTestCase() {
            if (inputPanel)
                inputPanel.destroy()
        }

        function prepareTest() {
            var window = container.Window.window
            verify(window)
            window.raise()
            window.requestActivate()
            tryCompare(window, "active", true)

            container.forceActiveFocus()
            waitForRendering(container)
            textInput.forceActiveFocus()
            waitForRendering(inputPanel)

            textInput.text = ""
            verify(inputPanel.visible === true)
            verify(textInput.activeFocus === true)
        }

        Component {
            id: modalDialogComp
            Dialog {
                id: dialog
                modal: true
                anchors.centerIn: parent
                width: 200
                height: 150
                property alias textEdit: textEdit
                TextEdit {
                    id: textEdit
                    visible: true
                    focus: true
                    color: "red"
                }
            }
        }

        function test_worksWithModal() {
            prepareTest()
            var modalDialog = modalDialogComp.createObject(container)
            modalDialog.open()
            modalDialog.forceActiveFocus()

            verify(modalDialog.textEdit.activeFocus === true)
            compare(modalDialog.textEdit.text, "")
            verify(inputPanel.visible === true)
            waitForRendering(inputPanel)

            mousePress(inputPanel, 10, 10, Qt.LeftButton, Qt.NoModifier, 20)
            verify(modalDialog.visible === true)
            mouseRelease(inputPanel, 10, 10, Qt.LeftButton, Qt.NoModifier, 20)
            compare(modalDialog.textEdit.text, "Q")
        }

        Component {
            id: buttonComp

            Button {
                id: button
                text: "overlapping VKB blocks hover"
                height: parent.height

                background: Rectangle {
                    color: button.hovered ? "tomato" : "wheat"
                    radius: 2
                }
            }
        }

        function test_blockHover() {
            if ((Qt.platform.pluginName === "offscreen")
                || (Qt.platform.pluginName === "minimal"))
                skip("Mouse hovering not functional on offscreen/minimal platforms")

            prepareTest()
            var button = buttonComp.createObject(container)

            mouseMove(inputPanel, 10, inputPanel.height / 2)
            compare(button.hovered, false)
        }
    }
}
