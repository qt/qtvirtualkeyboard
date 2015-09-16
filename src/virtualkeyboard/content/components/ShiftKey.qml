/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 1.3

/*!
    \qmltype ShiftKey
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits BaseKey

    \brief Shift key for keyboard layouts.

    This key changes the shift state of the keyboard.
*/

BaseKey {
    id: shiftKey
    key: Qt.Key_Shift
    enabled: InputContext.shiftHandler.toggleShiftEnabled
    highlighted: InputContext.capsLock
    functionKey: true
    keyPanelDelegate: keyboard.style ? keyboard.style.shiftKeyPanel : undefined
    /*! \internal */
    property bool capsLock: InputContext.capsLock
    /*! \internal */
    property bool shift: InputContext.shift
    onClicked: InputContext.shiftHandler.toggleShift()
}
