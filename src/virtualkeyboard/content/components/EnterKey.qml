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
    \qmltype EnterKey
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits BaseKey

    \brief Enter key for keyboard layouts.

    Sends an enter key for input method processing.
*/

BaseKey {
    /*! This property holds the action id for the enter key.

    */
    readonly property int actionId: InputContext.hasEnterKeyAction(InputContext.inputItem) ? InputContext.inputItem.EnterKeyAction.actionId : EnterKeyAction.None

    text: "\n"
    displayText: InputContext.hasEnterKeyAction(InputContext.inputItem) ? InputContext.inputItem.EnterKeyAction.label : ""
    key: Qt.Key_Return
    showPreview: false
    highlighted: enabled && displayText.length > 0
    enabled: InputContext.hasEnterKeyAction(InputContext.inputItem) ? InputContext.inputItem.EnterKeyAction.enabled : true
    keyPanelDelegate: keyboard.style ? keyboard.style.enterKeyPanel : undefined
}
