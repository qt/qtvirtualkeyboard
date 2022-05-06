/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

import QtQuick
import QtQuick.VirtualKeyboard

/*!
    \qmltype HandwritingModeKey
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits Key
    \since QtQuick.VirtualKeyboard 2.0

    \brief Hand writing mode key for keyboard layouts.

    This key toggles between the handwriting mode layout and the main layout.

    The key is automatically hidden from the keyboard layout if handwriting support
    is not enabled for the virtual keyboard.
*/

Key {
    keyType: QtVirtualKeyboard.HandwritingModeKey
    key: Qt.Key_Context2
    displayText: "HWR"
    functionKey: true
    highlighted: true
    visible: keyboard.isKeyboardFunctionAvailable(QtVirtualKeyboard.ToggleHandwritingMode)
    onClicked: keyboard.doKeyboardFunction(QtVirtualKeyboard.ToggleHandwritingMode)
    keyPanelDelegate: keyboard.style ? keyboard.style.handwritingKeyPanel : undefined
}
