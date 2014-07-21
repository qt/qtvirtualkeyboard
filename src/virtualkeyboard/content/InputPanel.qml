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
import QtQuick.Enterprise.VirtualKeyboard 1.1

/*!
    \qmltype InputPanel
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard

    \brief Provides the virtual keyboard UI.
    \ingroup qtvirtualkeyboard-qml

    The keyboard size is automatically calculated from the available
    width, i.e. the keyboard maintains the aspect ratio specified by the current
    style. Therefore the application should only set the \c width and \c y
    coordinates of the InputPanel, and not the height.
*/

Item {
    implicitHeight: keyboard.height
    Keyboard {
        id: keyboard
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
    AutoScroller { }
    MouseArea {
        z: -1
        anchors.fill: keyboard
    }
}
