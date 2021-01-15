/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

import QtQuick 2.0

/*!
    \qmltype SymbolModeKey
    \inqmlmodule QtQuick.VirtualKeyboard
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
