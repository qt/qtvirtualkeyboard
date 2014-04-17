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

/*!
    \qmltype BackspaceKey
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits BaseKey

    \brief Backspace key for keyboard layouts.

    Sends a backspace key for input method processing.
    This key is repeatable.
*/

BaseKey {
    key: Qt.Key_Backspace
    repeat: true
    functionKey: true
    keyPanelDelegate: keyboard.style ? keyboard.style.backspaceKeyPanel : undefined
}
