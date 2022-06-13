// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Window
import QtQuick.VirtualKeyboard

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Virtual Keyboard")
    id: root

    TextInput {
        anchors.fill: parent
        Component.onCompleted: {
            forceActiveFocus()
            Qt.quit()
        }
    }

    InputPanel {
        id: inputPanel
        anchors.bottom: parent.bottom
        width: root.width
    }
}
