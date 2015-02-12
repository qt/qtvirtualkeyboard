/****************************************************************************
**
** Copyright (C) 2015 Digia Plc
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

/*!
    \qmltype HandwritingModeKey
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits Key
    \since QtQuick.Enterprise.VirtualKeyboard 1.4

    \brief Hand writing mode key for keyboard layouts.

    This key toggles between the handwriting mode layout and the main layout.
*/

Key {
    key: Qt.Key_Context2
    displayText: "HWR"
    functionKey: true
    visible: VirtualKeyboardInputMethods.indexOf("HandwritingInputMethod") !== -1
    onClicked: keyboard.handwritingMode = !keyboard.handwritingMode
    keyPanelDelegate: keyboard.style ? keyboard.style.handwritingKeyPanel : undefined
}
