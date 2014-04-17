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
    \qmltype KeyPanel
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard.Styles
    \brief A base type of the styled keys.
    \ingroup qtvirtualkeyboard-styles-qml

    All the key delegates provided by the style should be based on this type.
*/

Item {
    /*! Provides access to properties in BaseKey.

        A list of available properties in control:
        \list
            \li \c control.key Unicode code of the key.
            \li \c control.text Unicode text of the key.
            \li \c control.displayText Display text of the key.
            \li \c control.alternativeKeys List of alternative key sequences.
            \li \c control.enabled Set to true when the key is enabled.
            \li \c control.pressed Set to true when the key is currently pressed.
            \li \c control.uppercased Set to true when the key is uppercased.
            \li \c control.capsLock Set to true when caps lock is enabled.
        \endlist
    */
    property Item control
    // Uncomment the following to reveal the key sizes
    /*
    Rectangle {
        id: root
        z: 1
        color: "transparent"
        border.color: "white"
        anchors.fill: parent
        Rectangle {
            color: "black"
            opacity: 0.6
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.left: parent.left
            anchors.leftMargin: 1
            implicitWidth: keyPanelInfoText.width + 4
            implicitHeight: keyPanelInfoText.height + 4
            Text {
                id: keyPanelInfoText
                text: root.parent.width + "x" + root.parent.height
                font.pixelSize: 12
                color: "white"
                anchors.centerIn: parent
            }
        }
    }
    */
}
