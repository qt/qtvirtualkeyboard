/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
    }
}
