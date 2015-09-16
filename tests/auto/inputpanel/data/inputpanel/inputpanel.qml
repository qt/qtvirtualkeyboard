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
import QtQuick.Enterprise.VirtualKeyboard 1.3
import QtQuick.Enterprise.VirtualKeyboard.Settings 1.2

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
    readonly property int inputMode: InputContext.inputEngine.inputMode
    readonly property var keyboard: findChildByProperty(inputPanel, "objectName", "keyboard", null)
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
        if (success === false) {
            // Check if the current layout contains multiple layouts
            if (keyboardLayoutLoader.item.hasOwnProperty("item")) {
                // If already in symbolMode, try the other page
                if (keyboard.symbolMode) {
                    if (keyboardLayoutLoader.item.hasOwnProperty("secondPage")) {
                        keyboardLayoutLoader.item.secondPage = !keyboardLayoutLoader.item.secondPage
                        testcase.waitForRendering(inputPanel)
                        success = keyActionOnCurrentLayoutCb(key)
                        keyboardLayoutLoader.item.secondPage = !keyboardLayoutLoader.item.secondPage
                    }
                } else {
                    // Some layouts (such as Arabic, Hindi) may have a second layout
                    InputContext.shiftHandler.toggleShift()
                    testcase.waitForRendering(inputPanel)
                    success = keyActionOnCurrentLayoutCb(key)
                    InputContext.shiftHandler.toggleShift()
                }
            } else if (!keyboard.symbolMode) {
                // Switch to symbol mode
                keyboard.symbolMode = true
                testcase.waitForRendering(inputPanel)
                success = keyActionOnCurrentLayoutCb(key)
                if (!success && keyboardLayoutLoader.item.hasOwnProperty("secondPage")) {
                    // Try the second page
                    keyboardLayoutLoader.item.secondPage = true
                    testcase.waitForRendering(inputPanel)
                    success = keyActionOnCurrentLayoutCb(key)
                }
                keyboard.symbolMode = false
            }
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
        testcase.mouseClick(inputPanel, itemPos.x, itemPos.y)
        testcase.waitForRendering(inputPanel)
        return true
    }
}
