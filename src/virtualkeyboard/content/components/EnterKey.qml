/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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
