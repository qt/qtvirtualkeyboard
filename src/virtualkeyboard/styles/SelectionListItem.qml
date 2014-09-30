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

/*!
    \qmltype SelectionListItem
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard.Styles
    \brief A base type for selection list item delegates.
    \ingroup qtvirtualkeyboard-styles-qml

    The SelectionListItem enables mouse handling for the selection list item
    delegates.
*/

Item {
    id: selectionListItem
    height: parent.height

    /*!
        \since QtQuick.Enterprise.VirtualKeyboard.Styles 1.1

        Sets the sound effect to be played on touch event.
    */
    property url soundEffect

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            selectionListItem.ListView.view.currentIndex = index
            selectionListItem.ListView.view.model.selectItem(index)
        }
    }
}
