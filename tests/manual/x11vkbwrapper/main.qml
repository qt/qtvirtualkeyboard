/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

import QtQuick 2.12
import QtQuick.Window 2.2

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

