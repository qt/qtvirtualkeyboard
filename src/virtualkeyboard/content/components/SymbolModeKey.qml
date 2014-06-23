/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
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
