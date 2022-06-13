// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtTest
import QtQuick
import QtQuick.VirtualKeyboard
import "handwriting.js" as Handwriting
import "utils.js" as Utils

HandwritingInputPanel {
    id: handwritingInputPanel
    z: 99

    property var testcase
    readonly property var inputMethod: InputContext.inputEngine.inputMethod
    readonly property var wordCandidatePopupList: Utils.findChildByProperty(handwritingInputPanel, "objectName", "wordCandidatePopupList", null)

    anchors.fill: parent

    signal inputMethodResult(var text)

    Connections {
        target: InputContext
        function onPreeditTextChanged() { if (InputContext.preeditText.length > 0) inputMethodResult(InputContext.preeditText) }
    }

    Connections {
        target: InputContext.inputEngine
        function onVirtualKeyClicked(key, text, modifiers, isAutoRepeat) { inputMethodResult(text) }
    }

    SignalSpy {
        id: inputMethodResultSpy
        target: handwritingInputPanel
        signalName: "inputMethodResult"
    }

    SignalSpy {
        id: wordCandidateListChangedSpy
        target: wordCandidatePopupList.model
        signalName: "dataChanged"
    }

    function wordCandidatePopupListSearchSuggestion(suggestion, timeout) {
        if (wordCandidatePopupList.visible === false)
            return false

        if (timeout !== undefined && timeout > 0) {
            // Note: Not using SignalSpy.wait() since it causes the test case to fail in case the signal is not emitted
            wordCandidateListChangedSpy.clear()
            var dt = new Date()
            var startTime = dt.getTime()
            while (wordCandidateListChangedSpy.count == 0) {
                dt = new Date()
                var elapsedTime = dt.getTime() - startTime
                if (elapsedTime >= timeout)
                    break
                var maxWait = Math.min(timeout - elapsedTime, 50)
                testcase.wait(maxWait)
            }
        }

        var suggestionFound = false
        var origIndex = handwritingInputPanel.wordCandidatePopupList.currentIndex
        if (origIndex !== -1) {
            while (true) {
                if (handwritingInputPanel.wordCandidatePopupList.model.dataAt(handwritingInputPanel.wordCandidatePopupList.currentIndex) === suggestion) {
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
        return suggestionFound
    }

    function wordCandidatePopupListSelectCurrentItem() {
        if (!handwritingInputPanel.wordCandidatePopupList.currentItem)
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
        if (isSuperimposedHandwriting())
            return true;
        inputMethodResultSpy.wait(3000)
        return inputMethodResultSpy.count > 0
    }

    function isSuperimposedHandwriting() {
        if (!available)
            return false
        return inputMethod != null && inputMethod.hasOwnProperty("superimposed") && inputMethod.superimposed;
    }
}
