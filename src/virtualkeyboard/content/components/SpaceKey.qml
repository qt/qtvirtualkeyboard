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
    \qmltype SpaceKey
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits Key

    \brief Space key for keyboard layouts.

    This key emits a space for input method processing.
*/

Key {
    text: " "
    displayText: ""
    repeat: true
    showPreview: false
    key: Qt.Key_Space
    keyPanelDelegate: keyboard.style ? keyboard.style.spaceKeyPanel : undefined
}
