// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.VirtualKeyboard as VKB
import QtQuick.VirtualKeyboard.Components

// Custom layout that creates a QML InputMethod and exposes counters
KeyboardLayout {
    id: root

    // Provide an input method instance for this layout
    property var im: VKB.InputMethod {
        id: testIM
        objectName: "testIM"

        // Counters
        property int inputModesCount: 0
        property int setInputModeCount: 0
        property int setTextCaseCount: 0
        property int resetCount: 0
        property int updateCount: 0
        property int clearInputModeCount: 0
        property int keyEventCount: 0

        // Selection lists
        property int selectionListsCount: 0
        property int selectionListItemCountCount: 0
        property int selectionListDataCount: 0
        property int selectionListItemSelectedCount: 0

        // Pattern recognition / traces
        property int patternRecognitionModesCount: 0
        property int traceBeginCount: 0
        property int traceEndCount: 0

        // Reselect / click on preedit
        property int reselectCount: 0
        property int clickPreeditTextCount: 0

        function inputModes(locale) {
            inputModesCount++
            return [VKB.InputEngine.InputMode.Latin, VKB.InputEngine.InputMode.Numeric]
        }
        function setInputMode(locale, mode) {
            setInputModeCount++
            return true
        }
        function setTextCase(tc) {
            setTextCaseCount++
            return true
        }
        /* This is commented out on purpose to test regression on QTBUG-140521
        function reset() {
            resetCount++
        }
        */
        function update() {
            updateCount++
        }
        function clearInputMode() {
            clearInputModeCount++
        }
        function keyEvent(key, text, modifiers) {
            keyEventCount++
            return false
        }

        // --- Selection list API ---
        function selectionLists() {
            selectionListsCount++
            // Advertise a candidate list (count may be zero)
            return [VKB.SelectionListModel.Type.WordCandidateList]
        }
        function selectionListItemCount(type) {
            selectionListItemCountCount++
            return 0
        }
        function selectionListData(type, index, role) {
            selectionListDataCount++
            return null
        }
        function selectionListItemSelected(type, index) {
            selectionListItemSelectedCount++
        }

        // --- Pattern recognition / traces ---
        function patternRecognitionModes() {
            patternRecognitionModesCount++
            // No handwriting/swipe by default
            return []
        }
        function traceBegin(traceId, patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo) {
            traceBeginCount++
            // Not accepting traces -> return null
            return null
        }
        function traceEnd(trace) {
            traceEndCount++
            return false
        }

        // --- Reselect / click in preedit ---
        function reselect(cursorPosition, reselectFlags) {
            reselectCount++
            return false
        }
        function clickPreeditText(cursorPosition) {
            clickPreeditTextCount++
            return false
        }
    }

    // Bind the custom input method for this layout
    inputMethod: im

    // Minimal visible key to ensure the layout is valid
    KeyboardRow {
        Key { objectName: "testKeyA"; key: Qt.Key_A; text: "a" }
    }
}
