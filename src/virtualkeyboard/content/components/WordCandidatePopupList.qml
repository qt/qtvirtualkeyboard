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

ListView {
    id: wordCandidatePopupList

    property int maxVisibleItems: 5
    readonly property real contentWidth: contentItem.childrenRect.width

    clip: true
    visible: enabled && count > 0
    height: currentItem ? currentItem.height * Math.min(maxVisibleItems, count) + (spacing * Math.min(maxVisibleItems, count) - 1) : 0
    Binding {
        target: wordCandidatePopupList
        property: "x"
        value: Qt.inputMethod.cursorRectangle.x -
               (wordCandidatePopupList.currentItem ?
                    (wordCandidatePopupList.currentItem.hasOwnProperty("cursorAnchor") ?
                         wordCandidatePopupList.currentItem.cursorAnchor : wordCandidatePopupList.currentItem.width) : 0)
        when: wordCandidatePopupList.visible
    }
    Binding {
        target: wordCandidatePopupList
        property: "y"
        value: Qt.inputMethod.cursorRectangle.y + Qt.inputMethod.cursorRectangle.height
        when: wordCandidatePopupList.visible
    }
    orientation: ListView.Vertical
    snapMode: ListView.SnapToItem
    delegate: keyboard.style.popupListDelegate
    highlight: keyboard.style.popupListHighlight ? keyboard.style.popupListHighlight : null
    highlightMoveDuration: 0
    highlightResizeDuration: 0
    add: keyboard.style.popupListAdd
    remove: keyboard.style.popupListRemove
    keyNavigationWraps: true
    model: enabled ? InputContext.inputEngine.wordCandidateListModel : null

    onContentWidthChanged: viewResizeTimer.restart()
    onCurrentItemChanged: if (currentItem) keyboard.soundEffect.register(currentItem.soundEffect)

    Timer {
        id: viewResizeTimer
        interval: 0
        repeat: false
        onTriggered: wordCandidatePopupList.width = wordCandidatePopupList.contentWidth
    }

    Connections {
        target: wordCandidatePopupList.model ? wordCandidatePopupList.model : null
        onActiveItemChanged: wordCandidatePopupList.currentIndex = index
        onItemSelected: if (wordCandidatePopupList.currentItem) keyboard.soundEffect.play(wordCandidatePopupList.currentItem.soundEffect)
    }

    Loader {
        sourceComponent: keyboard.style.popupListBackground
        anchors.fill: parent
        z: -1
    }
}
