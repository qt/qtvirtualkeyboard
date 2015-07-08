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
    \qmltype HandwritingModeKey
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits Key
    \since QtQuick.Enterprise.VirtualKeyboard 2.0

    \brief Hand writing mode key for keyboard layouts.

    This key toggles between the handwriting mode layout and the main layout.
*/

Key {
    key: Qt.Key_Context2
    displayText: "HWR"
    functionKey: true
    visible: keyboard.isHandwritingAvailable()
    onClicked: keyboard.handwritingMode = !keyboard.handwritingMode
    keyPanelDelegate: keyboard.style ? keyboard.style.handwritingKeyPanel : undefined
}
