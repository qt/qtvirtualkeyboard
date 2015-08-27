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
import QtQuick.Enterprise.VirtualKeyboard 2.0

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
