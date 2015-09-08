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
    \qmltype SymbolModeKey
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits Key

    \brief Symbol mode key for keyboard layouts.

    This key toggles between the symbol mode layout and the main layout.
*/

Key {
    key: Qt.Key_Context1
    displayText: "&123"
    functionKey: true
    onClicked: keyboard.symbolMode = !keyboard.symbolMode
    keyPanelDelegate: keyboard.style ? keyboard.style.symbolKeyPanel : undefined
}
