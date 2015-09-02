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

import QtTest 1.0
import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 2.0
import "handwriting.js" as Handwriting
import "utils.js" as Utils

HandwritingInputPanel {
    id: handwritingInputPanel
    z: 99

    property var testcase
    readonly property var wordCandidatePopupList: Utils.findChildByProperty(handwritingInputPanel, "objectName", "wordCandidatePopupList", null)

    anchors.fill: parent

    signal inputMethodResult(var text)

    Connections {
        target: InputContext
        onPreeditTextChanged: if (InputContext.preeditText.length > 0) inputMethodResult(InputContext.preeditText)
    }

    Connections {
        target: InputContext.inputEngine
        onVirtualKeyClicked: inputMethodResult(text)
    }

    SignalSpy {
        id: inputMethodResultSpy
        target: handwritingInputPanel
        signalName: "inputMethodResult"
    }

    function wordCandidatePopupListSearchSuggestion(suggestion, timeout) {
        if (timeout === undefined || timeout < 0)
            timeout = 0
        var suggestionFound = false
        var dt = new Date()
        var startTime = dt.getTime()
        while (true) {
            var origIndex = handwritingInputPanel.wordCandidatePopupList.currentIndex
            if (origIndex !== -1) {
                while (true) {
                    if (handwritingInputPanel.wordCandidatePopupList.model.itemData(handwritingInputPanel.wordCandidatePopupList.currentIndex) === suggestion) {
                        suggestionFound = true
                        break
                    }
                    if (handwritingInputPanel.wordCandidatePopupList.currentIndex === handwritingInputPanel.wordCandidatePopupList.count - 1)
                        break
                    handwritingInputPanel.wordCandidatePopupList.incrementCurrentIndex()
                }
                if (!suggestionFound) {
                    while (handwritingInputPanel.wordCandidatePopupList.currentIndex !== origIndex) {
                        handwritingInputPanel.wordCandidatePopupList.decrementCurrentIndex()
                    }
                }
                testcase.waitForRendering(handwritingInputPanel)
            }
            dt = new Date()
            var elapsedTime = dt.getTime() - startTime
            if (suggestionFound || elapsedTime >= timeout)
                break
            var maxWait = Math.min(timeout - elapsedTime, 50)
            testcase.wait(maxWait)
        }
        return suggestionFound
    }

    function wordCandidatePopupListSelectCurrentItem() {
        if (handwritingInputPanel.wordCandidatePopupList.currentItem === -1)
            return false
        testcase.wait(200)
        var itemPos = handwritingInputPanel.mapFromItem(handwritingInputPanel.wordCandidatePopupList.currentItem,
                                                        handwritingInputPanel.wordCandidatePopupList.currentItem.width / 2,
                                                        handwritingInputPanel.wordCandidatePopupList.currentItem.height / 2)
        testcase.mouseClick(handwritingInputPanel, itemPos.x, itemPos.y, Qt.LeftButton, 0, 20)
        testcase.waitForRendering(handwritingInputPanel)
        return true
    }

    function emulateHandwriting(ch, instant) {
        if (!available)
            return false
        active = true
        var hwrInputArea = Utils.findChildByProperty(handwritingInputPanel, "objectName", "hwrInputArea", null)
        inputMethodResultSpy.clear()
        if (!Handwriting.emulate(testcase, hwrInputArea, ch, instant)) {
            console.warn("Cannot produce the symbol '%1' in full screen handwriting mode".arg(ch))
            return false
        }
        inputMethodResultSpy.wait(3000)
        return inputMethodResultSpy.count > 0
    }
}
