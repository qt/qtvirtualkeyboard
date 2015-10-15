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

/*!
    \qmltype ModeKey
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits Key
    \since QtQuick.Enterprise.VirtualKeyboard 2.0

    \brief Generic mode key for keyboard layouts.

    This key provides generic mode button functionality.

    A key press toggles the current mode without emitting key event
    for input method processing.

    ModeKey can be used in situations where a particular mode is switched
    "ON / OFF", and where the mode change does not require changing the
    keyboard layout. When this component is used, the \l { BaseKey::displayText } { displayText } should
    remain the same regardless of the mode, because the keyboard style
    visualizes the status.
*/

Key {
    /*! This property provides the current mode.

        The default is false.
    */
    property bool mode
    noKeyEvent: true
    functionKey: true
    onClicked: mode = !mode
    keyPanelDelegate: keyboard.style ? keyboard.style.modeKeyPanel : undefined
}
