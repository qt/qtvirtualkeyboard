/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
// Deliberately imported after QtQuick to avoid missing restoreMode property in Binding. Fix in Qt 6.
import QtQml
import QtQuick.VirtualKeyboard

PopupList {
    id: wordCandidatePopupList

    readonly property int preferredVisibleItems: {
        if (!currentItem)
            return 0
        var maxHeight = flipVertical ? Qt.inputMethod.cursorRectangle.y : parent.height - Qt.inputMethod.cursorRectangle.height - Qt.inputMethod.cursorRectangle.y
        var result = Math.min(count, maxVisibleItems)
        while (result > 2 && result * currentItem.height > maxHeight)
            --result
        return result
    }
    readonly property bool flipVertical: currentItem &&
                                         Qt.inputMethod.cursorRectangle.y + (Qt.inputMethod.cursorRectangle.height / 2) > (parent.height / 2) &&
                                         Qt.inputMethod.cursorRectangle.y + Qt.inputMethod.cursorRectangle.height + (currentItem.height * 2) > parent.height

    height: currentItem ? currentItem.height * preferredVisibleItems + (spacing * preferredVisibleItems - 1) : 0
    Binding {
        target: wordCandidatePopupList
        property: "x"
        value: Math.round(Qt.inputMethod.cursorRectangle.x -
               (wordCandidatePopupList.currentItem ?
                    (wordCandidatePopupList.currentItem.hasOwnProperty("cursorAnchor") ?
                         wordCandidatePopupList.currentItem.cursorAnchor : wordCandidatePopupList.currentItem.width) : 0))
        when: wordCandidatePopupList.visible
        restoreMode: Binding.RestoreBinding
    }
    Binding {
        target: wordCandidatePopupList
        property: "y"
        value: Math.round(wordCandidatePopupList.flipVertical ? Qt.inputMethod.cursorRectangle.y - wordCandidatePopupList.height : Qt.inputMethod.cursorRectangle.y + Qt.inputMethod.cursorRectangle.height)
        when: wordCandidatePopupList.visible
        restoreMode: Binding.RestoreBinding
    }
    model: enabled ? InputContext.inputEngine.wordCandidateListModel : null

    onContentWidthChanged: viewResizeTimer.restart()

    Timer {
        id: viewResizeTimer
        interval: 0
        repeat: false
        onTriggered: wordCandidatePopupList.width = wordCandidatePopupList.contentWidth
    }

    Connections {
        target: wordCandidatePopupList.model ? wordCandidatePopupList.model : null
        function onActiveItemChanged(index) { wordCandidatePopupList.currentIndex = index }
        function onItemSelected() { if (wordCandidatePopupList.currentItem) keyboard.soundEffect.play(wordCandidatePopupList.currentItem.soundEffect) }
    }
}
