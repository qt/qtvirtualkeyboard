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
import QtQuick.Enterprise.VirtualKeyboard 1.3

InputMethod {
    property string multitapSequence
    property int multitapIndex: -1

    onMultitapSequenceChanged: selectionListChanged(SelectionListModel.WordCandidateList)
    onMultitapIndexChanged: selectionListActiveItemChanged(SelectionListModel.WordCandidateList, multitapIndex)

    property variant multiTapTimer: Timer {
        interval: 1200
        onTriggered: {
            update()
        }
    }

    function inputModes(locale) {
        return [InputEngine.Latin, InputEngine.Numeric, InputEngine.Dialable];
    }

    function setInputMode(locale, inputMode) {
        return true
    }

    function setTextCase(textCase) {
        return true
    }

    function reset() {
        multiTapTimer.stop()
        multitapIndex = -1
        multitapSequence = ""
    }

    function update() {
        multiTapTimer.stop()
        multitapIndex = -1
        multitapSequence = ""
        if (inputContext !== null && inputContext.preeditText.length > 0) {
            inputContext.commit()
        }
    }

    function keyEvent(key, text, modifiers) {
        var accept = false
        switch (key) {
        case Qt.Key_Enter:
        case Qt.Key_Return:
        case Qt.Key_Tab:
            update()
            break
        case Qt.Key_Backspace:
            if (inputContext.preeditText.length > 0) {
                inputContext.clear()
                update()
                accept = true
            }
            break
        default:
            if (key !== inputEngine.previousKey) {
                update()
            }
            multitapSequence = text
            if (multitapSequence.length > 1) {
                multitapIndex = multiTapTimer.running ? (multitapIndex + 1) % multitapSequence.length : 0
                inputContext.preeditText = multitapSequence.charAt(multitapIndex)
                multiTapTimer.restart()
            } else {
                inputContext.commit(text)
            }
            accept = true
            break
        }
        return accept;
    }

    function selectionLists() {
        return [SelectionListModel.WordCandidateList];
    }

    function selectionListItemCount(type) {
        return multitapSequence.length > 1 ? multitapSequence.length : 0
    }

    function selectionListData(type, index, role) {
        var result = null
        switch (role) {
        case SelectionListModel.DisplayRole:
            result = multitapSequence.charAt(index)
            break
        default:
            break
        }
        return result
    }

    function selectionListItemSelected(type, index) {
        multitapIndex = index
        inputContext.preeditText = multitapSequence.charAt(multitapIndex)
        update()
    }
}
