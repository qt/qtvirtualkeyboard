/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
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
import QtQuick.Enterprise.VirtualKeyboard 1.0

/*!
    \qmltype EnterKey
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits BaseKey

    \brief Enter key for keyboard layouts.

    Sends an enter key for input method processing.
*/

BaseKey {
    text: "\n"
    displayText: InputContext.inputItem && InputContext.inputItem.enterKeyText !== undefined ? InputContext.inputItem.enterKeyText : ""
    key: Qt.Key_Return
    functionKey: true
    highlighted: enabled && displayText.length > 0
    enabled: InputContext.inputItem && InputContext.inputItem.enterKeyEnabled !== undefined ? InputContext.inputItem.enterKeyEnabled : true
    keyPanelDelegate: keyboard.style ? keyboard.style.enterKeyPanel : undefined
}
