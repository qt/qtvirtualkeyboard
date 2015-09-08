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
            if (index === -1)
                return
            selectionListItem.ListView.view.currentIndex = index
            selectionListItem.ListView.view.model.selectItem(index)
        }
    }
}
