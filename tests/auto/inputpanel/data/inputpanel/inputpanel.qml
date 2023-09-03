// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtTest
import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Settings
import "handwriting.js" as Handwriting
import "utils.js" as Utils

InputPanel {
    id: inputPanel
    z: 99
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    visible: active

    property var testcase
    property var virtualKeyPressPoint: null
    readonly property int cursorPosition: InputContext.cursorPosition
    readonly property string preeditText: InputContext.preeditText
    readonly property string surroundingText: InputContext.surroundingText
    readonly property bool autoCapitalizationEnabled: InputContext.priv.shiftHandler.autoCapitalizationEnabled
    readonly property bool toggleShiftEnabled: InputContext.priv.shiftHandler.toggleShiftEnabled
    readonly property string locale: keyboard.locale
    readonly property string defaultLocale: VirtualKeyboardSettings.locale
    readonly property var availableLocales: VirtualKeyboardSettings.availableLocales
    readonly property var activeLocales: VirtualKeyboardSettings.activeLocales
    readonly property int inputMode: InputContext.inputEngine.inputMode
    readonly property var inputMethod: InputContext.inputEngine.inputMethod
    readonly property bool handwritingMode: keyboard.handwritingMode
    readonly property Loader keyboardLayoutLoader: keyboard.keyboardLayoutLoader
    readonly property MultiPointTouchArea keyboardInputArea: keyboard.keyboardInputArea
    readonly property CharacterPreviewBubble characterPreviewBubble: keyboard.characterPreview
    readonly property AlternativeKeys alternativeKeys: keyboard.alternativeKeys
    readonly property Loader naviationHighlight: keyboard.naviationHighlight
    readonly property ListView wordCandidateView: keyboard.wordCandidateView
    readonly property Item wordCandidateContextMenu: keyboard.wordCandidateContextMenu
    readonly property ShadowInputControl shadowInputControl: keyboard.shadowInputControl
    readonly property TextInput shadowInput: keyboard.shadowInputControl.textEdit
    readonly property SelectionControl selectionControl: Utils.findChildByProperty(inputPanel, "objectName", "selectionControl", null)
    readonly property var anchorHandle: selectionControl.children[0]
    readonly property var cursorHandle: selectionControl.children[1]
    readonly property SelectionControl fullScreenModeSelectionControl: keyboard.fullScreenModeSelectionControl
    readonly property var fullScreenModeAnchorHandle: fullScreenModeSelectionControl.children[0]
    readonly property var fullScreenModeCursorHandle: fullScreenModeSelectionControl.children[1]
    readonly property bool wordCandidateListVisibleHint: InputContext.inputEngine.wordCandidateListVisibleHint
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
    property alias inputMethodResultSpy: inputMethodResultSpy
    property alias wordCandidateListChangedSpy: wordCandidateListChangedSpy
    property alias wordCandidateListItemSelectedSpy: wordCandidateListItemSelectedSpy
    property alias inputMethodSelectionListChangedSpy: inputMethodSelectionListChangedSpy
    property alias wordCandidateListVisibleSpy: wordCandidateListVisibleSpy
    property alias wordCandidateListCurrentIndexSpy: wordCandidateListCurrentIndexSpy
    property alias shiftStateSpy: shiftStateSpy
    property alias shadowInputControlVisibleSpy: shadowInputControlVisibleSpy
    property alias externalLanguageSwitchSpy: externalLanguageSwitchSpy

    signal inputMethodResult(var text)

    LayoutMirroring.childrenInherit: true

    Connections {
        target: InputContext
        function onPreeditTextChanged() {
            if (InputContext.preeditText.length > 0)
                inputMethodResult(InputContext.preeditText)
        }
    }

    Connections {
        target: InputContext.inputEngine
        function onVirtualKeyClicked(key, text, modifiers, isAutoRepeat) { inputMethodResult(text) }
    }

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

    SignalSpy {
        id: inputMethodResultSpy
        target: inputPanel
        signalName: "inputMethodResult"
    }

    SignalSpy {
        id: wordCandidateListChangedSpy
        target: wordCandidateView.model
        signalName: "dataChanged"
    }

    SignalSpy {
        id: wordCandidateListItemSelectedSpy
        target: wordCandidateView.model
        signalName: "itemSelected"
    }

    SignalSpy {
        id: inputMethodSelectionListChangedSpy
        target: InputContext.inputEngine.inputMethod
        signalName: "selectionListChanged"
    }

    SignalSpy {
        id: wordCandidateListVisibleSpy
        target: wordCandidateView
        signalName: "onVisibleConditionChanged"
    }

    SignalSpy {
        id: wordCandidateListCurrentIndexSpy
        target: wordCandidateView
        signalName: "onCurrentIndexChanged"
    }

    SignalSpy {
        id: wordCandidateContextMenuActiveSpy
        target: wordCandidateContextMenu
        signalName: "onActiveChanged"
    }

    SignalSpy {
        id: shiftStateSpy
        target: InputContext
        signalName: "onShiftActiveChanged"
    }

    SignalSpy {
        id: shadowInputControlVisibleSpy
        target: shadowInputControl
        signalName: "onVisibleChanged"
    }

    SignalSpy {
        id: externalLanguageSwitchSpy
        target: inputPanel
        signalName: "onExternalLanguageSwitch"
    }

    // Disable all animations during tests
    Binding {
        target: keyboard
        property: "noAnimations"
        value: true
    }

    // Reduce press and hold delay to avoid unnecessary wait during tests
    Binding {
        target: keyboard
        property: "pressAndHoldDelay"
        value: 50
    }

    function isLocaleSupported(inputLocale) {
        var localeIndex = VirtualKeyboardSettings.availableLocales.indexOf(inputLocale)
        return localeIndex !== -1
    }

    function setLocale(inputLocale) {
        VirtualKeyboardSettings.locale = inputLocale
        if (["ar", "fa"].indexOf(inputLocale.substring(0, 2)) !== -1)
            return inputPanel.keyboard.locale.substring(0, 2) === inputLocale.substring(0, 2)
        return inputPanel.keyboard.locale === inputLocale
    }

    function setActiveLocales(activeLocales) {
        VirtualKeyboardSettings.activeLocales = activeLocales
    }

    function mapKeyboardFunction(keyboardFunctionName) {
        if (keyboardFunctionName === "HideInputPanel")
            return QtVirtualKeyboard.KeyboardFunction.HideInputPanel
        if (keyboardFunctionName === "ChangeLanguage")
            return QtVirtualKeyboard.KeyboardFunction.ChangeLanguage
        if (keyboardFunctionName === "ToggleHandwritingMode")
            return QtVirtualKeyboard.KeyboardFunction.ToggleHandwritingMode
        return -1
    }

    function doKeyboardFunction(keyboardFunctionName) {
        const keyboardFunction = mapKeyboardFunction(keyboardFunctionName)
        testcase.verify(keyboardFunction !== -1)
        keyboard.doKeyboardFunction(keyboardFunction)
    }

    function mapKeyboardFunctionKey(functionKeyName) {
        if (functionKeyName === "None")
            return QtVirtualKeyboard.KeyboardFunctionKeys.None
        if (functionKeyName === "Hide")
            return QtVirtualKeyboard.KeyboardFunctionKeys.Hide
        if (functionKeyName === "Language")
            return QtVirtualKeyboard.KeyboardFunctionKeys.Language
        if (functionKeyName === "All")
            return QtVirtualKeyboard.KeyboardFunctionKeys.All
        testcase.fail("Invalid function key '%1'".arg(functionKeyName))
    }

    function setVisibleFunctionKeys(functionKeyNames) {
        let functionKeys = QtVirtualKeyboard.KeyboardFunctionKeys.None
        for (const functionKeyName of functionKeyNames) {
            functionKeys |= mapKeyboardFunctionKey(functionKeyName)
        }
        VirtualKeyboardSettings.visibleFunctionKeys = functionKeys
    }

    function setWclAutoHideDelay(wclAutoHideDelay) {
        VirtualKeyboardSettings.wordCandidateList.autoHideDelay = wclAutoHideDelay
    }

    function setWclAlwaysVisible(wclAlwaysVisible) {
        VirtualKeyboardSettings.wordCandidateList.alwaysVisible = wclAlwaysVisible
    }

    function setWclAutoCommitWord(wclAutoCommitWord) {
        VirtualKeyboardSettings.wordCandidateList.autoCommitWord = wclAutoCommitWord
    }

    function setFullScreenMode(fullScreenMode) {
        VirtualKeyboardSettings.fullScreenMode = fullScreenMode
    }

    function mapInputMode(inputModeName) {
        if (inputModeName === "Latin")
            return InputEngine.InputMode.Latin
        else if (inputModeName === "Numeric")
            return InputEngine.InputMode.Numeric
        else if (inputModeName === "Dialable")
            return InputEngine.InputMode.Dialable
        else if (inputModeName === "Pinyin")
            return InputEngine.InputMode.Pinyin
        else if (inputModeName === "Cangjie")
            return InputEngine.InputMode.Cangjie
        else if (inputModeName === "Zhuyin")
            return InputEngine.InputMode.Zhuyin
        else if (inputModeName === "Hangul")
            return InputEngine.InputMode.Hangul
        else if (inputModeName === "Hiragana")
            return InputEngine.InputMode.Hiragana
        else if (inputModeName === "Katakana")
            return InputEngine.InputMode.Katakana
        else if (inputModeName === "FullwidthLatin")
            return InputEngine.InputMode.FullwidthLatin
        else if (inputModeName === "Greek")
            return InputEngine.InputMode.Greek
        else if (inputModeName === "Cyrillic")
            return InputEngine.InputMode.Cyrillic
        else if (inputModeName === "Arabic")
            return InputEngine.InputMode.Arabic
        else if (inputModeName === "Hebrew")
            return InputEngine.InputMode.Hebrew
        else if (inputModeName === "ChineseHandwriting")
            return InputEngine.InputMode.ChineseHandwriting
        else if (inputModeName === "JapaneseHandwriting")
            return InputEngine.InputMode.JapaneseHandwriting
        else if (inputModeName === "KoreanHandwriting")
            return InputEngine.InputMode.KoreanHandwriting
        else if (inputModeName === "Thai")
            return InputEngine.InputMode.Thai
        else if (inputModeName === "Stroke")
            return InputEngine.InputMode.Stroke
        else if (inputModeName === "Romaji")
            return InputEngine.InputMode.Romaji
        else
            return -1
    }

    function isInputModeSupported(inputMode) {
        return InputContext.inputEngine.inputModes.indexOf(inputMode) !== -1
    }

    function setInputMode(inputMode) {
        if (!isInputModeSupported(inputMode))
            return false
        if (InputContext.inputEngine.inputMode !== inputMode)
            InputContext.inputEngine.inputMode = inputMode
        return true
    }

    function testPublicEnums() {
        // Scoped
        testcase.verify(InputEngine.TextCase.Lower !== undefined)
        testcase.verify(InputEngine.TextCase.Upper !== undefined)
        testcase.verify(InputEngine.InputMode.Latin !== undefined)
        testcase.verify(InputEngine.InputMode.Numeric !== undefined)
        testcase.verify(InputEngine.InputMode.Dialable !== undefined)
        testcase.verify(InputEngine.InputMode.Pinyin !== undefined)
        testcase.verify(InputEngine.InputMode.Cangjie !== undefined)
        testcase.verify(InputEngine.InputMode.Zhuyin !== undefined)
        testcase.verify(InputEngine.InputMode.Hangul !== undefined)
        testcase.verify(InputEngine.InputMode.Hiragana !== undefined)
        testcase.verify(InputEngine.InputMode.Katakana !== undefined)
        testcase.verify(InputEngine.InputMode.FullwidthLatin !== undefined)
        testcase.verify(InputEngine.InputMode.Greek !== undefined)
        testcase.verify(InputEngine.InputMode.Cyrillic !== undefined)
        testcase.verify(InputEngine.InputMode.Arabic !== undefined)
        testcase.verify(InputEngine.InputMode.Hebrew !== undefined)
        testcase.verify(InputEngine.InputMode.ChineseHandwriting !== undefined)
        testcase.verify(InputEngine.InputMode.JapaneseHandwriting !== undefined)
        testcase.verify(InputEngine.InputMode.KoreanHandwriting !== undefined)
        testcase.verify(InputEngine.InputMode.Thai !== undefined)
        testcase.verify(InputEngine.InputMode.Stroke !== undefined)
        testcase.verify(InputEngine.InputMode.Romaji !== undefined)
        testcase.verify(InputEngine.PatternRecognitionMode.None !== undefined)
        testcase.verify(InputEngine.PatternRecognitionMode.PatternRecognitionDisabled !== undefined)
        testcase.verify(InputEngine.PatternRecognitionMode.Handwriting !== undefined)
        testcase.verify(InputEngine.PatternRecognitionMode.HandwritingRecoginition !== undefined)
        testcase.verify(InputEngine.ReselectFlag.WordBeforeCursor !== undefined)
        testcase.verify(InputEngine.ReselectFlag.WordAfterCursor !== undefined)
        testcase.verify(InputEngine.ReselectFlag.WordAtCursor !== undefined)
        testcase.verify(SelectionListModel.Type.WordCandidateList !== undefined)
        testcase.verify(SelectionListModel.Role.Display !== undefined)
        testcase.verify(SelectionListModel.Role.WordCompletionLength !== undefined)
        testcase.verify(SelectionListModel.Role.Dictionary !== undefined)
        testcase.verify(SelectionListModel.DictionaryType.Default !== undefined)
        testcase.verify(SelectionListModel.DictionaryType.User !== undefined)
    }

    function setExternalLanguageSwitchEnabled(enabled) {
        externalLanguageSwitchEnabled = enabled
    }

    function setLayoutMirroring(enabled) {
        LayoutMirroring.enabled = enabled
    }

    function findVirtualKey(key) {
        return Utils.findChild(keyboardLayoutLoader, key, function(obj, param) {
            if (!obj.hasOwnProperty("key") || !obj.hasOwnProperty("text"))
                return false
            return (typeof param == "number") ? obj.key === param : obj.text.toUpperCase() === param.toUpperCase()
        })
    }

    function findVirtualKeyAlternative(key) {
        if (typeof key != "string")
            return null
        return Utils.findChildByProperty(keyboardLayoutLoader, "effectiveAlternativeKeys", key.toUpperCase(),
                 function(propertyValue, key) {
                     if (typeof propertyValue == "string")
                         return propertyValue.toUpperCase().indexOf(key) !== -1
                     return propertyValue.filter(function(value) {
                         return key === value.toUpperCase()
                     }).length > 0
                 })
    }

    function findObjectByName(objectName) {
        return Utils.findChildByProperty(keyboard, "objectName", objectName, null)
    }

    function mapKeyboardKeyType(keyTypeName) {
        if (keyTypeName === "ChangeLanguageKey")
            return QtVirtualKeyboard.KeyType.ChangeLanguageKey
        if (keyTypeName === "HideKeyboardKey")
            return QtVirtualKeyboard.KeyType.HideKeyboardKey
        testcase.fail("Invalid key type '%1'".arg(keyTypeName))
    }

    function findKeyByKeyType(keyTypeName) {
        const keyType = mapKeyboardKeyType(keyTypeName)
        return Utils.findChildByProperty(keyboard, "keyType", keyType, null)
    }

    function virtualKeyPressOnCurrentLayout(key) {
        var keyObj = typeof key == "object" && key.hasOwnProperty("key") ? key : findVirtualKey(key)
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
            testcase.wait(1)
            if (alternativeKey) {
                alternativeKeysSpy.wait()
                var keyIndex = keyObj.effectiveAlternativeKeys.indexOf(key.toLowerCase())
                var itemX = keyIndex * keyboard.style.alternateKeysListItemWidth + keyboard.style.alternateKeysListItemWidth / 2
                virtualKeyPressPoint.x = inputPanel.mapFromItem(alternativeKeys.listView, itemX, 0).x
                testcase.mouseMove(inputPanel, virtualKeyPressPoint.x, virtualKeyPressPoint.y)
                testcase.wait(1)
            }
            return true
        }
        return false
    }

    function multiLayoutKeyActionHelper(key, keyActionOnCurrentLayoutCb) {
        if (!keyboardLayoutLoader.item) {
            console.warn("Key not found \\u%1 (keyboard layout not loaded)".arg(typeof key == "string" ? key.charCodeAt(0).toString(16) : key.toString(16)))
            return false
        }
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
                } else if (typeof key != "number" || key !== Qt.Key_Shift) {
                    // Some layouts (such as Arabic, Hindi) may have a second layout
                    virtualKeyClick(Qt.Key_Shift)
                    InputContext.priv.shiftHandler.clearToggleShiftTimer()
                    testcase.waitForRendering(inputPanel)
                    success = keyActionOnCurrentLayoutCb(key)
                    if (!success) {
                        virtualKeyClick(Qt.Key_Shift)
                        InputContext.priv.shiftHandler.clearToggleShiftTimer()
                        testcase.waitForRendering(inputPanel)
                    }
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
            console.warn("Key not found \\u%1".arg(typeof key == "string" ? key.charCodeAt(0).toString(16) : key.toString(16)))
        return success
    }

    function virtualKeyPress(key) {
        if (!key)
            return false
        return multiLayoutKeyActionHelper(key, virtualKeyPressOnCurrentLayout)
    }

    function virtualKeyDrag(key) {
        if (virtualKeyPressPoint !== null) {
            var keyObj = Utils.findChildByProperty(keyboardLayoutLoader, (typeof key == "number") ? "key" : "text", key, null)
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
        testcase.wait(50)
    }

    function navigateToKeyOnPoint(point) {
        activateNavigationKeyMode()
        if (inputPanel.naviationHighlight.visible) {
            while (true) {
                var navigationPoint = inputPanel.mapToItem(inputPanel.naviationHighlight, point.x, point.y)
                if (inputPanel.naviationHighlight.contains(Qt.point(navigationPoint.x, navigationPoint.y)))
                    return true
                if (inputPanel.naviationHighlight.y > point.y)
                    emulateNavigationKeyClick(Qt.Key_Up)
                else if (inputPanel.naviationHighlight.y + inputPanel.naviationHighlight.height < point.y)
                    emulateNavigationKeyClick(Qt.Key_Down)
                else if (inputPanel.naviationHighlight.x > point.x)
                    emulateNavigationKeyClick(Qt.Key_Left)
                else if (inputPanel.naviationHighlight.x + inputPanel.naviationHighlight.width < point.x)
                    emulateNavigationKeyClick(Qt.Key_Right)
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
                var keyIndex = keyObj.effectiveAlternativeKeys.indexOf(key)
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
            if (inputPanel.naviationHighlight.visible) {
                testcase.wait(1)
            }
        }
        return inputPanel.naviationHighlight.visible
    }

    function toggleShift() {
        InputContext.priv.shiftHandler.toggleShift()
    }

    function setShiftActive(shiftActive) {
        InputContext.priv.shiftHandler.shiftActive = shiftActive
    }

    function setCapsLockActive(capsLockActive) {
        InputContext.priv.shiftHandler.capsLockActive = capsLockActive
    }

    function style() {
        return VirtualKeyboardSettings.styleName
    }

    function setStyle(style) {
        VirtualKeyboardSettings.styleName = style
    }

    function selectionListSearchSuggestion(suggestion) {
        if (wordCandidateListVisibleHint === false)
            return false

        if (inputPanel.wordCandidateView.count === 0)
            return false;

        var suggestionFound = false
        var origIndex = inputPanel.wordCandidateView.currentIndex
        if (origIndex === -1) {
            inputPanel.wordCandidateView.incrementCurrentIndex()
            origIndex = inputPanel.wordCandidateView.currentIndex
        }
        if (origIndex !== -1) {
            while (inputPanel.wordCandidateView.currentIndex > 0) {
                inputPanel.wordCandidateView.decrementCurrentIndex()
            }
            while (true) {
                if (inputPanel.wordCandidateView.model.dataAt(inputPanel.wordCandidateView.currentIndex) === suggestion) {
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
        }
        return suggestionFound
    }

    function selectionListSelectCurrentItem() {
        if (!inputPanel.wordCandidateView.currentItem)
            return false
        testcase.verify(inputPanel.wordCandidateView.currentItem,
            "Expected wordCandidateView to have a currentItem, but it's null."
            + " Its property values at the time of failure are:"
            + " x=" + inputPanel.wordCandidateView.x
            + " y=" + inputPanel.wordCandidateView.y
            + " width=" + inputPanel.wordCandidateView.width
            + " height=" + inputPanel.wordCandidateView.height
            + " count=" + inputPanel.wordCandidateView.count
            + " flicking=" + inputPanel.wordCandidateView.flicking
            + " moving=" + inputPanel.wordCandidateView.moving
            + " visible=" + inputPanel.wordCandidateView.visible)
        var itemPos = inputPanel.mapFromItem(inputPanel.wordCandidateView.currentItem,
                                             inputPanel.wordCandidateView.currentItem.width / 2,
                                             inputPanel.wordCandidateView.currentItem.height / 2)
        testcase.mouseClick(inputPanel, itemPos.x, itemPos.y, Qt.LeftButton, 0, 20)
        return true
    }

    function selectionListCurrentIndex() {
        return inputPanel.wordCandidateView.currentIndex
    }

    function selectionListSuggestionIsFromUserDictionary() {
        if (!inputPanel.wordCandidateView.currentItem)
            return false
        var dictionaryType = inputPanel.wordCandidateView.model.dataAt(inputPanel.wordCandidateView.currentIndex, SelectionListModel.Role.Dictionary)
        return dictionaryType !== undefined && dictionaryType === SelectionListModel.DictionaryType.User
    }

    function openWordCandidateContextMenu() {
        if (!inputPanel.wordCandidateView.currentItem)
            return false
        testcase.wait(200)
        wordCandidateContextMenuActiveSpy.clear()
        testcase.mousePress(inputPanel.wordCandidateView.currentItem)
        wordCandidateContextMenuActiveSpy.wait()
        testcase.mouseRelease(inputPanel.wordCandidateView.currentItem)
        return wordCandidateContextMenu.active
    }

    function selectItemFromWordCandidateContextMenu(index) {
        if (!inputPanel.wordCandidateView.currentItem)
            return false
        if (!wordCandidateContextMenu.active)
            return false
        var wordCandidateContextMenuList = Utils.findChildByProperty(keyboard, "objectName", "wordCandidateContextMenuList", null)
        if (wordCandidateContextMenuList.currentIndex !== index) {
            wordCandidateContextMenuList.currentIndex = index
        }
        if (!wordCandidateContextMenuList.currentItem)
            return false
        var itemPos = inputPanel.mapFromItem(wordCandidateContextMenuList.currentItem,
                                             wordCandidateContextMenuList.currentItem.width / 2,
                                             wordCandidateContextMenuList.currentItem.height / 2)
        testcase.mouseClick(inputPanel, itemPos.x, itemPos.y, Qt.LeftButton, 0, 20)
        return true
    }

    function isHandwritingFeatureAvailable() {
        return VirtualKeyboardFeatures.Handwriting
    }

    function setHandwritingMode(enabled) {
        if (inputPanel.keyboard.handwritingMode !== enabled) {
            if (!enabled || inputPanel.keyboard.isHandwritingAvailable())
                inputPanel.keyboard.setHandwritingMode(enabled, true)
        }
        return inputPanel.keyboard.handwritingMode === enabled
    }

    function emulateHandwriting(ch, instant) {
        if (!inputPanel.keyboard.handwritingMode)
            return false
        var hwrInputArea = Utils.findChildByProperty(keyboard, "objectName", "hwrInputArea", null)
        inputMethodResultSpy.clear()
        if (!Handwriting.emulate(testcase, hwrInputArea, ch, instant,
                                 VirtualKeyboardSettings.locale)) {
            if (virtualKeyClick(ch))
                return true
            console.warn("Cannot produce the symbol '%1' in handwriting mode".arg(ch))
            return false
        }
        if (isSuperimposedHandwriting())
            return true
        inputMethodResultSpy.wait(3000)
        return inputMethodResultSpy.count > 0
    }

    function isSuperimposedHandwriting() {
        if (!inputPanel.keyboard.handwritingMode)
            return false
        return inputMethod != null && inputMethod.hasOwnProperty("superimposed") && inputMethod.superimposed
    }
}
