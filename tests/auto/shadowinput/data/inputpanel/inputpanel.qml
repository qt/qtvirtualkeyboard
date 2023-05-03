// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtTest
import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Settings

InputPanel {
    id: inputPanel
    z: 99
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    visible: active
    property bool fullScreenMode: true
    property bool shadowInputVisible: keyboard.shadowInputControl.visible
    property string shadowInputText: keyboard.shadowInputControl.textEdit.text
    Binding {
        target: VirtualKeyboardSettings
        property: "fullScreenMode"
        value: inputPanel.fullScreenMode
    }
}
