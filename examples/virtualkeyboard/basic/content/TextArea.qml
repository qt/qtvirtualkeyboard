// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls as Controls
import QtQuick.VirtualKeyboard

Controls.TextArea {
    id: control
    color: "#2B2C2E"
    selectionColor: Qt.rgba(0.0, 0.0, 0.0, 0.15)
    selectedTextColor: color
    selectByMouse: true
    font.pixelSize: Qt.application.font.pixelSize * 2

    property int enterKeyAction: EnterKeyAction.None
    readonly property bool enterKeyEnabled: enterKeyAction === EnterKeyAction.None || text.length > 0 || inputMethodComposing

    EnterKeyAction.actionId: control.enterKeyAction
    EnterKeyAction.enabled: control.enterKeyEnabled

    background: Rectangle {
        color: "#FFFFFF"
        border.width: 1
        border.color: control.activeFocus ? "#5CAA15" : "#BDBEBF"
    }
}
