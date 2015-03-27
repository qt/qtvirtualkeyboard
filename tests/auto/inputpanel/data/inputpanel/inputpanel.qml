/****************************************************************************
**
** Copyright (C) 2015 Digia Plc
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

import QtTest 1.0
import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 1.3
import QtQuick.Enterprise.VirtualKeyboard.Settings 1.2
import "unipen_data.js" as UnipenData

InputPanel {
    id: inputPanel
    z: 99
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    visible: Qt.inputMethod.visible

    property var testcase
    property var virtualKeyPressPoint: null
    readonly property bool autoCapitalizationEnabled: InputContext.shiftHandler.autoCapitalizationEnabled
    readonly property bool toggleShiftEnabled: InputContext.shiftHandler.toggleShiftEnabled
    readonly property string locale: InputContext.locale
    readonly property int inputMode: InputContext.inputEngine.inputMode
    readonly property var keyboard: findChildByProperty(inputPanel, "objectName", "keyboard", null)
    readonly property bool handwritingMode: keyboard.handwritingMode
    readonly property var keyboardLayoutLoader: findChildByProperty(keyboard, "objectName", "keyboardLayoutLoader", null)
    readonly property var keyboardInputArea: findChildByProperty(keyboard, "objectName", "keyboardInputArea", null)
    readonly property var characterPreviewBubble: findChildByProperty(keyboard, "objectName", "characterPreviewBubble", null)
    readonly property var alternativeKeys: findChildByProperty(keyboard, "objectName", "alternativeKeys", null)
    readonly property var naviationHighlight: findChildByProperty(keyboard, "objectName", "naviationHighlight", null)
    readonly property var wordCandidateView: findChildByProperty(keyboard, "objectName", "wordCandidateView", null)
    readonly property bool keyboardLayoutsAvailable: keyboard.availableLocaleIndices.length > 0 && keyboard.availableLocaleIndices.indexOf(-1) === -1
    property alias keyboardLayoutsAvailableSpy: keyboardLayoutsAvailableSpy
    property alias keyboardLayoutLoaderItemSpy: keyboardLayoutLoaderItemSpy
    property alias characterPreviewBubbleSpy: characterPreviewBubbleSpy
    property alias alternativeKeysSpy: alternativeKeysSpy
    property alias activeKeyChangedSpy: activeKeyChangedSpy
    property alias virtualKeyClickedSpy: virtualKeyClickedSpy
    property alias dragSymbolModeSpy: dragSymbolModeSpy
    property alias styleSpy: styleSpy
    property alias soundEffectSpy: soundEffectSpy

    SignalSpy {
        id: keyboardLayoutsAvailableSpy
        target: inputPanel
        signalName: "onKeyboardLayoutsAvailableChanged"
    }

    SignalSpy {
        id: keyboardLayoutLoaderItemSpy
        target: keyboardLayoutLoader
        signalName: "onItemChanged"
    }

    SignalSpy {
        id: characterPreviewBubbleSpy
        target: characterPreviewBubble
        signalName: "onVisibleChanged"
    }

    SignalSpy {
        id: alternativeKeysSpy
        target: alternativeKeys
        signalName: "onVisibleChanged"
    }

    SignalSpy {
        id: activeKeyChangedSpy
        target: InputContext.inputEngine
        signalName: "activeKeyChanged"
    }

    SignalSpy {
        id: virtualKeyClickedSpy
        target: InputContext.inputEngine
        signalName: "virtualKeyClicked"
    }

    SignalSpy {
        id: dragSymbolModeSpy
        target: keyboardInputArea
        signalName: "onDragSymbolModeChanged"
    }

    SignalSpy {
        id: styleSpy
        target: keyboard
        signalName: "onStyleChanged"
    }

    SignalSpy {
        id: soundEffectSpy
        target: keyboard.soundEffect
        signalName: "onPlayingChanged"
    }

    function findChildByProperty(parent, propertyName, propertyValue, compareCb) {
        var obj = null
        if (parent === null)
            return null
        var children = parent.children
        for (var i = 0; i < children.length; i++) {
            obj = children[i]
            if (obj.hasOwnProperty(propertyName)) {
                if (compareCb !== null) {
                    if (compareCb(obj[propertyName], propertyValue))
                        break
                } else if (obj[propertyName] === propertyValue) {
                    break
                }
            }
            obj = findChildByProperty(obj, propertyName, propertyValue, compareCb)
            if (obj)
                break
        }
        return obj
    }

    function isLocaleSupported(inputLocale) {
        var localeIndex = keyboard.findLocale(inputLocale, -1)
        return localeIndex !== -1
    }

    function setLocale(inputLocale) {
        var localeIndex = keyboard.findLocale(inputLocale, -1)
        if (localeIndex === -1)
            return false
        var origLocaleIndex = keyboard.localeIndex
        if (keyboard.localeIndex !== localeIndex) {
            keyboard.localeIndex = localeIndex
            keyboardLayoutLoaderItemSpy.wait()
        }
        var success = keyboardLayoutLoader.item !== null
        if (keyboardLayoutLoader.item === null) {
            if (keyboard.localeIndex !== origLocaleIndex) {
                keyboard.localeIndex = origLocaleIndex
                keyboardLayoutLoaderItemSpy.wait()
            }
        }
        return success
    }

    function mapInputMode(inputModeName) {
        if (inputModeName === "Latin")
            return InputEngine.Latin
        else if (inputModeName === "Numeric")
            return InputEngine.Numeric
        else if (inputModeName === "Dialable")
            return InputEngine.Dialable
        else if (inputModeName === "Pinyin")
            return InputEngine.Pinyin
        else if (inputModeName === "Hangul")
            return InputEngine.Hangul
        else if (inputModeName === "Hiragana")
            return InputEngine.Hiragana
        else if (inputModeName === "Katakana")
            return InputEngine.Katakana
        else if (inputModeName === "FullwidthLatin")
            return InputEngine.FullwidthLatin
        else
            return -1
    }

    function setInputMode(inputMode) {
        if (InputContext.inputEngine.inputModes.indexOf(inputMode) === -1)
            return false
        if (InputContext.inputEngine.inputMode !== inputMode)
            InputContext.inputEngine.inputMode = inputMode
        return true
    }

    function findVirtualKey(key) {
        return findChildByProperty(keyboardLayoutLoader, (typeof key == "number") ? "key" : "text", key, null)
    }

    function findVirtualKeyAlternative(key) {
        if (typeof key != "string")
            return null
        return findChildByProperty(keyboardLayoutLoader, "alternativeKeys", key, function(propertyValue, key) { return propertyValue.indexOf(key) !== -1 })
    }

    function virtualKeyPressOnCurrentLayout(key) {
        var keyObj = findVirtualKey(key)
        var alternativeKey = false
        if (!keyObj && typeof key == "string") {
            keyObj = findVirtualKeyAlternative(key)
            alternativeKey = keyObj !== null
            if (alternativeKey)
                alternativeKeysSpy.clear()
        }
        if (keyObj) {
            virtualKeyPressPoint = inputPanel.mapFromItem(keyObj, keyObj.width / 2, keyObj.height / 2)
            testcase.mousePress(inputPanel, virtualKeyPressPoint.x, virtualKeyPressPoint.y)
            testcase.waitForRendering(inputPanel)
            if (alternativeKey) {
                alternativeKeysSpy.wait()
                var keyIndex = keyObj.alternativeKeys.indexOf(key)
                var itemX = keyIndex * keyboard.style.alternateKeysListItemWidth + keyboard.style.alternateKeysListItemWidth / 2
                virtualKeyPressPoint.x = inputPanel.mapFromItem(alternativeKeys.listView, itemX, 0).x
                testcase.mouseMove(inputPanel, virtualKeyPressPoint.x, virtualKeyPressPoint.y)
                testcase.waitForRendering(inputPanel)
            }
            return true
        }
        return false
    }

    function multiLayoutKeyActionHelper(key, keyActionOnCurrentLayoutCb) {
        var success = keyActionOnCurrentLayoutCb(key)
        for (var c = 0; !success && c < 2; c++) {
            // Check if the current layout contains multiple layouts
            if (keyboardLayoutLoader.item.hasOwnProperty("item")) {
                if (keyboardLayoutLoader.item.hasOwnProperty("secondPage")) {
                    keyboardLayoutLoader.item.secondPage = !keyboardLayoutLoader.item.secondPage
                    testcase.waitForRendering(inputPanel)
                    success = keyActionOnCurrentLayoutCb(key)
                } else if (keyboardLayoutLoader.item.hasOwnProperty("page") && keyboardLayoutLoader.item.hasOwnProperty("numPages")) {
                    for (var page = 0; !success && page < keyboardLayoutLoader.item.numPages; page++) {
                        keyboardLayoutLoader.item.page = page
                        testcase.waitForRendering(inputPanel)
                        success = keyActionOnCurrentLayoutCb(key)
                    }
                } else {
                    // Some layouts (such as Arabic, Hindi) may have a second layout
                    InputContext.shiftHandler.toggleShift()
                    testcase.waitForRendering(inputPanel)
                    success = keyActionOnCurrentLayoutCb(key)
                    InputContext.shiftHandler.toggleShift()
                }
                if (success)
                    break
            }

            // Symbol mode not allowed in handwriting mode
            if (inputPanel.handwritingMode)
                break

            // Toggle symbol mode
            keyboard.symbolMode = !keyboard.symbolMode
            testcase.waitForRendering(inputPanel)
            success = keyActionOnCurrentLayoutCb(key)
        }
        if (!success)
            console.warn("Key not found '%1'".arg(key))
        return success
    }

    function virtualKeyPress(key) {
        return multiLayoutKeyActionHelper(key, virtualKeyPressOnCurrentLayout)
    }

    function virtualKeyDrag(key) {
        if (virtualKeyPressPoint !== null) {
            var keyObj = findChildByProperty(keyboardLayoutLoader, (typeof key == "number") ? "key" : "text", key, null)
            if (keyObj !== null) {
                virtualKeyPressPoint = inputPanel.mapFromItem(keyObj, keyObj.width / 2, keyObj.height / 2)
                testcase.mouseMove(inputPanel, virtualKeyPressPoint.x, virtualKeyPressPoint.y)
                testcase.waitForRendering(inputPanel)
                return true
            }
        }
        return false
    }

    function virtualKeyRelease() {
        if (virtualKeyPressPoint !== null) {
            testcase.mouseRelease(inputPanel, virtualKeyPressPoint.x, virtualKeyPressPoint.y)
            virtualKeyPressPoint = null
            return true
        }
        return false
    }

    function virtualKeyClick(key) {
        if (virtualKeyPress(key)) {
            virtualKeyRelease()
            return true
        }
        return false
    }

    function emulateNavigationKeyClick(navigationKey) {
        testcase.keyClick(navigationKey)
        testcase.waitForRendering(inputPanel)
    }

    function navigationHighlightContains(point) {
        var navigationPoint = inputPanel.mapToItem(inputPanel.naviationHighlight, point.x, point.y)
        return inputPanel.naviationHighlight.contains(Qt.point(navigationPoint.x, navigationPoint.y))
    }

    function navigateToKeyOnPoint(point) {
        activateNavigationKeyMode()
        if (inputPanel.naviationHighlight.visible) {
            while (true) {
                var navigationPoint = inputPanel.mapToItem(inputPanel.naviationHighlight, point.x, point.y)
                if (navigationHighlightContains(point))
                    return true
                if (inputPanel.naviationHighlight.y > point.y)
                    emulateNavigationKeyClick(Qt.Key_Up)
                else if (inputPanel.naviationHighlight.y + inputPanel.naviationHighlight.height < point.y)
                    emulateNavigationKeyClick(Qt.Key_Down)
                else if (inputPanel.naviationHighlight.x > point.x)
                    emulateNavigationKeyClick(Qt.Key_Left)
                else if (inputPanel.naviationHighlight.x + inputPanel.naviationHighlight.width < point.x)
                    emulateNavigationKeyClick(Qt.Key_Right)
                testcase.wait(inputPanel.naviationHighlight.moveDuration)
            }
        }
        return false
    }

    function navigateToKeyOnCurrentLayout(key) {
        var keyObj = findVirtualKey(key)
        var alternativeKey = false
        if (!keyObj && typeof key == "string") {
            keyObj = findVirtualKeyAlternative(key)
            alternativeKey = keyObj !== null
        }
        if (keyObj) {
            var point = inputPanel.mapFromItem(keyObj, keyObj.width / 2, keyObj.height / 2)
            if (!navigateToKeyOnPoint(point))
                return false
            if (alternativeKey) {
                alternativeKeysSpy.clear()
                testcase.keyPress(Qt.Key_Return)
                alternativeKeysSpy.wait()
                testcase.keyRelease(Qt.Key_Return)
                var keyIndex = keyObj.alternativeKeys.indexOf(key)
                while (inputPanel.alternativeKeys.listView.currentIndex !== keyIndex) {
                    testcase.verify(inputPanel.alternativeKeys.listView.currentIndex !== -1)
                    emulateNavigationKeyClick(inputPanel.alternativeKeys.listView.currentIndex < keyIndex ? Qt.Key_Right : Qt.Key_Left)
                }
            }
            return true
        }
        return false
    }

    function navigationKeyClickOnCurrentLayout(key) {
        if (navigateToKeyOnCurrentLayout(key)) {
            testcase.keyClick(Qt.Key_Return)
            return true
        }
        return false
    }

    function navigateToKey(key) {
        return multiLayoutKeyActionHelper(key, navigateToKeyOnCurrentLayout)
    }

    function navigationKeyClick(key) {
        return multiLayoutKeyActionHelper(key, navigationKeyClickOnCurrentLayout)
    }

    function activateNavigationKeyMode() {
        if (!inputPanel.naviationHighlight.visible) {
            emulateNavigationKeyClick(Qt.Key_Right)
            if (inputPanel.naviationHighlight.visible)
                testcase.wait(inputPanel.naviationHighlight.moveDuration)
        }
        return inputPanel.naviationHighlight.visible
    }

    function toggleShift() {
        InputContext.shiftHandler.toggleShift()
    }

    function style() {
        return VirtualKeyboardSettings.styleName
    }

    function setStyle(style) {
        VirtualKeyboardSettings.styleName = style
    }

    function selectionListSearchSuggestion(suggestion, timeout) {
        if (timeout === undefined || timeout < 0)
            timeout = 0
        var suggestionFound = false
        var dt = new Date()
        var startTime = dt.getTime()
        while (true) {
            var origIndex = inputPanel.wordCandidateView.currentIndex
            if (origIndex !== -1) {
                while (true) {
                    if (inputPanel.wordCandidateView.model.itemData(inputPanel.wordCandidateView.currentIndex) === suggestion) {
                        suggestionFound = true
                        break
                    }
                    if (inputPanel.wordCandidateView.currentIndex === inputPanel.wordCandidateView.count - 1)
                        break
                    inputPanel.wordCandidateView.incrementCurrentIndex()
                }
                if (!suggestionFound) {
                    while (inputPanel.wordCandidateView.currentIndex !== origIndex) {
                        inputPanel.wordCandidateView.decrementCurrentIndex()
                    }
                }
                testcase.waitForRendering(inputPanel)
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

    function selectionListSelectCurrentItem() {
        if (inputPanel.wordCandidateView.currentItem === -1)
            return false
        testcase.wait(200)
        var itemPos = inputPanel.mapFromItem(inputPanel.wordCandidateView.currentItem, 0, 0)
        testcase.mouseClick(inputPanel, itemPos.x, itemPos.y, Qt.LeftButton, 0, 20)
        testcase.waitForRendering(inputPanel)
        return true
    }

    function setHandwritingMode(enabled) {
        if (inputPanel.keyboard.handwritingMode !== enabled)
            virtualKeyClick(Qt.Key_Context2)
        return inputPanel.keyboard.handwritingMode === enabled
    }

    function emulateHandwriting(ch, instant) {
        if (!inputPanel.keyboard.handwritingMode)
            return false
        var chKey = "0x" + (ch.charCodeAt(0) + 0x10000).toString(16).substr(-4)
        if (!UnipenData.unipenData.hasOwnProperty(chKey)) {
            if (virtualKeyClick(ch))
                return true
            console.warn("Cannot produce the symbol '%1' in handwriting mode".arg(ch))
            return false
        }
        var chData = UnipenData.unipenData[chKey]
        var hwrInputArea = findChildByProperty(keyboard, "objectName", "hwrInputArea", null)
        var scale = hwrInputArea.height / chData[".Y_DIM"]
        var strokes = UnipenData.unipenData[chKey][".PEN"]
        var boundingBox = calculateBoundingBox(strokes)
        var boxOffset = Qt.point(-boundingBox.x * scale + (hwrInputArea.width - boundingBox.width * scale) / 2, -boundingBox.y * scale + (hwrInputArea.height - boundingBox.height * scale) / 2)
        var t = 0
        for (var strokeIndex = 0; strokeIndex < strokes.length; strokeIndex++) {
            var stroke = strokes[strokeIndex]
            for (var i = 0; i < stroke.length; i++) {
                var strokeData = stroke[i]
                var pt = Qt.point(strokeData[0] * scale + boxOffset.x, strokeData[1] * scale + boxOffset.y)
                if (instant)
                    t = strokeData[2]
                if (i == 0) {
                    t = strokeData[2]
                    testcase.mousePress(hwrInputArea, pt.x, pt.y, Qt.LeftButton, 0, strokeData[2] - t)
                } else {
                    testcase.mouseMove(hwrInputArea, pt.x, pt.y, strokeData[2] - t, Qt.LeftButton)
                }
                if (i + 1 === stroke.length)
                    testcase.mouseRelease(hwrInputArea, pt.x, pt.y, Qt.LeftButton, 0, instant ? 1 : strokeData[2] - t)
                t = strokeData[2]
            }
        }
        virtualKeyClickedSpy.clear()
        virtualKeyClickedSpy.wait(3000)
        return virtualKeyClickedSpy.count === 1
    }

    function calculateBoundingBox(unipenStrokes) {
        var bboxLeft = 2147483647
        var bboxRight = -2147483647
        var bboxTop = 2147483647
        var bboxBottom = -2147483647
        for (var strokeIndex = 0; strokeIndex < unipenStrokes.length; strokeIndex++) {
            var stroke = unipenStrokes[strokeIndex]
            for (var i = 0; i < stroke.length; i++) {
                var strokeData = stroke[i]
                var x = strokeData[0]
                if (bboxLeft > x)
                    bboxLeft = x
                if (bboxRight < x)
                    bboxRight = x
                var y = strokeData[1]
                if (bboxTop > y)
                    bboxTop = y
                if (bboxBottom < y)
                    bboxBottom = y
            }
        }
        if (bboxLeft > bboxRight || bboxTop > bboxBottom)
            return Qt.rect(0, 0, 0, 0)
        return Qt.rect(bboxLeft, bboxTop, bboxRight - bboxLeft, bboxBottom -bboxTop)
    }
}
