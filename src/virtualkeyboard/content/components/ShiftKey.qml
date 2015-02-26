/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

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
