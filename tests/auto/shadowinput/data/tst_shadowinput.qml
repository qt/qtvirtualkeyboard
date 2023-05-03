// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtTest
import QtQuick
import QtQuick.Window

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

            textInput = textEditComp.createObject(container)
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
            id: textEditComp
            TextEdit {
                id: textEdit
                visible: true
                focus: true
                color: "white"
            }
        }

        function test_fullScreenModeBindingWorks() {
            prepareTest()

            verify(inputPanel.visible === true)
            waitForRendering(inputPanel)

            // VirtualKeyboardSettings.fullScreeenMode is initially true
            // Verity that shadow input is visible and the content match with the edit field
            verify(inputPanel.shadowInputVisible)
            textInput.text = "hello"
            compare(inputPanel.shadowInputText, textInput.text)

            // Disable fullScreenMode and verify
            inputPanel.fullScreenMode = false
            waitForRendering(inputPanel)
            verify(!inputPanel.shadowInputVisible)
            textInput.text = "world"
            compare(inputPanel.shadowInputText, "")
        }
    }
}
