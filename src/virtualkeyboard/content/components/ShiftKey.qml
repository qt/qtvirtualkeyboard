/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 1.0

BaseKey {
    id: shiftKey
    key: Qt.Key_Shift
    enabled: !keyboard.uppercaseOnly && !keyboard.lowercaseOnly
    visible: enabled
    highlighted: InputContext.capsLock
    functionKey: true
    keyPanelDelegate: keyboard.style ? keyboard.style.shiftKeyPanel : undefined
    property bool capsLock: InputContext.capsLock
    property bool shift: InputContext.shift
    onClicked: {
        if (InputContext.inputMethodHints & Qt.ImhNoAutoUppercase) {
            InputContext.capsLock = !InputContext.capsLock
            InputContext.shift = !InputContext.shift
        } else {
            InputContext.capsLock = !InputContext.capsLock && (InputContext.shift && !keyboard.shiftChanged)
            InputContext.shift = InputContext.capsLock || !InputContext.shift ? true : false
            keyboard.shiftChanged = false
        }
    }
}
