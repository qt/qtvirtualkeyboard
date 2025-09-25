// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtTest
import QtQuick
import QtQuick.VirtualKeyboard

Item {
    width: 800
    height: 640
    Column {
        TextInput {
            objectName: "textInput"
            width: 400
            height: 40
        }
        TextInput {
            objectName: "numericTextInput"
            width: 400
            height: 40
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }
    }
    InputPanel {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: active
    }
}
