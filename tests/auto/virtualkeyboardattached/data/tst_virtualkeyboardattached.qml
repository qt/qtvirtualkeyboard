// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtTest
import QtQuick
import QtQuick.Window
import QtQuick.VirtualKeyboard

Rectangle {
    id: container
    width: 800
    height: 640
    color: "blue"

    TestCase {
        id: testcase
        name: "tst_virtualkeyboardattached"
        when: windowShown

        property var inputPanel: null

        function initTestCase() {
            var inputPanelComp = Qt.createComponent("inputpanel/inputpanel.qml")
            compare(inputPanelComp.status, Component.Ready, "Failed to create component: "+inputPanelComp.errorString())
            inputPanel = inputPanelComp.createObject(container)
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
        }

        Component {
            id: textInputWithVirtualKeyboardAttachedComp
            TextEdit {
                anchors.fill: parent
                visible: true
                focus: true
                color: "white"
                VirtualKeyboard.extraDictionaries: ["example"]
            }
        }

        function test_virtualKeyboardAttached() {
            prepareTest()

            container.forceActiveFocus()
            waitForRendering(container)

            let textInput = textInputWithVirtualKeyboardAttachedComp.createObject(container)

            verify(textInput !== null)

            textInput.forceActiveFocus()
            waitForRendering(inputPanel)

            verify(inputPanel.visible === true)
            verify(textInput.activeFocus === true)
        }

        Component {
            id: textInputWithEnterKeyActionAttachedComp
            TextEdit {
                anchors.fill: parent
                visible: true
                focus: true
                color: "white"
                EnterKeyAction.actionId: EnterKeyAction.Done
                EnterKeyAction.label: "hello"
                EnterKeyAction.enabled: true
            }
        }

        function test_enterKeyActionAttached() {
            prepareTest()

            container.forceActiveFocus()
            waitForRendering(container)

            let textInput = textInputWithEnterKeyActionAttachedComp.createObject(container)

            verify(textInput !== null)

            textInput.forceActiveFocus()
            waitForRendering(inputPanel)

            verify(inputPanel.visible === true)
            verify(textInput.activeFocus === true)
        }
    }
}
