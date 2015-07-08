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
import QtQuick.Enterprise.VirtualKeyboard 2.0

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
    id: inputPanel

    /*! \qmlproperty bool Active state of the input panel
        \since QtQuick.Enterprise.VirtualKeyboard 2.0

        This property reflects the active status of the input panel.
        The keyboard should be made visible to user when the active is true.
    */
    property alias active: keyboard.active

    /*! \internal */
    property alias keyboard: keyboard

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
