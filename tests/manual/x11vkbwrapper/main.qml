// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Window

Window {
    id: window
    width: d.vkbSwitchSize
    height: d.vkbSwitchSize
    x: Screen.width - width
    y: Screen.height - height
    color: "transparent"
    visible: true
    flags: Qt.WindowStaysOnTopHint | Qt.WindowDoesNotAcceptFocus | Qt.FramelessWindowHint

    QtObject {
        id: d
        readonly property int vkbSwitchSize: 30
    }

    Image {
        id: qtLogo
        anchors.fill: parent
        source: "graphics/Qt_logo.png"

        MouseArea {
            anchors.fill: parent
            onClicked: atspiFocus.setKeyboardVisible(!Qt.inputMethod.visible)
        }
    }

    Keyboard {}
}

