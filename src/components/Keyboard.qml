// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
// Deliberately imported after QtQuick to avoid missing restoreMode property in Binding. Fix in Qt 6.
import QtQml
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Styles
import QtQuick.VirtualKeyboard.Settings
import QtQuick.VirtualKeyboard.Plugins
import Qt.labs.folderlistmodel

Item {
    id: keyboard
    objectName: "keyboard"

    property alias style: styleLoader.item
    property alias wordCandidateView: wordCandidateView
    property alias shadowInputControl: shadowInputControl
    property Item activeKey: null
    property TouchPoint activeTouchPoint
    property int localeIndex: -1
    property var availableLocaleIndices: []
    property var availableCustomLocaleIndices: []
    property string locale: localeIndex >= 0 && localeIndex < layoutsModel.count ? layoutsModel.get(localeIndex, "fileName") : ""
    property string inputLocale
    property int defaultLocaleIndex: -1
    readonly property bool latinOnly: InputContext.inputMethodHints & (Qt.ImhLatinOnly | Qt.ImhEmailCharactersOnly | Qt.ImhUrlCharactersOnly)
    readonly property bool preferNumbers: InputContext.inputMethodHints & Qt.ImhPreferNumbers
    readonly property bool dialableCharactersOnly: InputContext.inputMethodHints & Qt.ImhDialableCharactersOnly
    readonly property bool formattedNumbersOnly: InputContext.inputMethodHints & Qt.ImhFormattedNumbersOnly
    readonly property bool digitsOnly: InputContext.inputMethodHints & Qt.ImhDigitsOnly
    property string layout
    property string layoutType: {
        if (keyboard.handwritingMode) return "handwriting"
        if (keyboard.dialableCharactersOnly) return "dialpad"
        if (keyboard.formattedNumbersOnly) return "numbers"
        if (keyboard.digitsOnly) return "digits"
        if (keyboard.symbolMode) return "symbols"
        return "main"
    }
    property bool active: Qt.inputMethod.visible
    property bool handwritingMode
    property bool fullScreenHandwritingMode
    property bool symbolMode
    property bool fullScreenMode: VirtualKeyboardSettings.fullScreenMode
    property var defaultInputMethod: initDefaultInputMethod()
    property var plainInputMethod: PlainInputMethod {}
    property var customInputMethod: null
    property var customInputMethodSharedLayouts: []
    property int defaultInputMode: InputEngine.InputMode.Latin
    property bool inputMethodNeedsReset: true
    property bool inputModeNeedsReset: true
    property bool navigationModeActive: false
    readonly property bool languagePopupListActive: languagePopupList.enabled
    property alias soundEffect: soundEffect
    property alias keyboardLayoutLoader: keyboardLayoutLoader
    property real screenHeight: parent.parent ? parent.parent.height : Screen.height

    function initDefaultInputMethod() {
        try {
            return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; DefaultInputMethod {}', keyboard, "defaultInputMethod")
        } catch (e) { }
        return plainInputMethod
    }

    Component.onCompleted: InputContext.priv.registerInputPanel(parent)

    width: keyboardBackground.width
    height: keyboardBackground.height
    onActiveChanged: {
        hideLanguagePopup()
        if (active && symbolMode && !preferNumbers)
            symbolMode = false
        keyboardInputArea.reset()
        wordCandidateViewAutoHideTimer.stop()
    }
    onActiveKeyChanged: {
        if (InputContext.inputEngine.activeKey !== Qt.Key_unknown)
            InputContext.inputEngine.virtualKeyCancel()
    }
    Connections {
        target: VirtualKeyboardSettings
        function onLocaleChanged() {
            updateDefaultLocale()
            localeIndex = defaultLocaleIndex
        }
        function onActiveLocalesChanged() {
            updateDefaultLocale()
            if (!isValidLocale(localeIndex) || VirtualKeyboardSettings.locale)
                localeIndex = defaultLocaleIndex
        }
        function onDefaultInputMethodDisabledChanged() {
            updateInputMethod()
        }
    }
    onAvailableLocaleIndicesChanged: hideLanguagePopup()
    onAvailableCustomLocaleIndicesChanged: hideLanguagePopup()
    onLocaleChanged: {
        hideLanguagePopup()
        inputMethodNeedsReset = true
        inputModeNeedsReset = true
        updateLayout()
    }
    onInputLocaleChanged: {
        if (Qt.locale(inputLocale).name !== "C")
            InputContext.priv.locale = inputLocale
    }
    onLayoutChanged: hideLanguagePopup()
    onLayoutTypeChanged: {
        updateAvailableLocaleIndices()
        updateLayout()
    }
    onLatinOnlyChanged: inputModeNeedsReset = true
    onPreferNumbersChanged: {
        keyboard.symbolMode = !keyboard.handwritingMode && preferNumbers
        inputModeNeedsReset = true
    }
    onDialableCharactersOnlyChanged: inputModeNeedsReset = true
    onFormattedNumbersOnlyChanged: inputModeNeedsReset = true
    onDigitsOnlyChanged: inputModeNeedsReset = true
    onHandwritingModeChanged: if (!keyboard.handwritingMode) keyboard.fullScreenHandwritingMode = false
    onFullScreenHandwritingModeChanged: if (keyboard.fullScreenHandwritingMode) keyboard.handwritingMode = true
    onLanguagePopupListActiveChanged: {
        if (languagePopupListActive && navigationModeActive)
            keyboardInputArea.initialKey = null
    }

    Connections {
        target: InputContext
        function onInputMethodHintsChanged() {
            if (InputContext.priv.focus)
                updateInputMethod()
        }
    }
    Connections {
        target: InputContext.priv
        function onInputItemChanged() {
            keyboard.hideLanguagePopup()
            if (active && symbolMode && !preferNumbers)
                symbolMode = false
        }
        function onFocusChanged() {
            if (InputContext.priv.focus)
                updateInputMethod()
        }
        function onNavigationKeyPressed(key, isAutoRepeat) {
            var initialKey
            var direction = wordCandidateView.effectiveLayoutDirection == Qt.LeftToRight ? 1 : -1
            switch (key) {
            case Qt.Key_Left:
                if (keyboard.navigationModeActive && !keyboardInputArea.initialKey) {
                    if (languagePopupListActive) {
                        hideLanguagePopup()
                        keyboardInputArea.setActiveKey(null)
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                        break
                    }
                    if (alternativeKeys.active) {
                        if (alternativeKeys.listView.currentIndex > 0) {
                            alternativeKeys.listView.decrementCurrentIndex()
                        } else {
                            alternativeKeys.close()
                            keyboardInputArea.setActiveKey(null)
                            keyboardInputArea.navigateToNextKey(0, 0, false)
                        }
                        break
                    }
                    if (functionPopupList.active) {
                        if (functionPopupList.listView.currentIndex > 0) {
                            functionPopupList.listView.decrementCurrentIndex()
                        } else {
                            functionPopupList.close()
                            keyboardInputArea.setActiveKey(null)
                            keyboardInputArea.navigateToNextKey(0, 0, false)
                        }
                        break
                    }
                    if (wordCandidateContextMenu.active) {
                        hideWordCandidateContextMenu()
                        break
                    }
                    if (wordCandidateView.count) {
                        if (wordCandidateView.effectiveLayoutDirection == Qt.LeftToRight &&
                                wordCandidateView.currentIndex > 0) {
                            wordCandidateView.decrementCurrentIndex()
                        } else if (wordCandidateView.effectiveLayoutDirection == Qt.RightToLeft &&
                                   wordCandidateView.currentIndex + 1 < wordCandidateView.count) {
                            wordCandidateView.incrementCurrentIndex()
                        } else {
                            keyboardInputArea.navigateToNextKey(0, 0, false)
                            initialKey = keyboardInputArea.initialKey
                            while (keyboardInputArea.navigateToNextKey(0, 1 * direction, false))
                                initialKey = keyboardInputArea.initialKey
                            while (keyboardInputArea.navigateToNextKey(1, 0, false))
                                initialKey = keyboardInputArea.initialKey
                            keyboardInputArea.initialKey = initialKey
                            keyboardInputArea.navigateToNextKey(0, 0, false)
                        }
                        break
                    }
                }
                initialKey = keyboardInputArea.initialKey
                if (!keyboardInputArea.navigateToNextKey(-1, 0, false)) {
                    keyboardInputArea.initialKey = initialKey
                    if (!keyboardInputArea.navigateToNextKey(0, -1 * direction, false)) {
                        if (wordCandidateView.count) {
                            if (wordCandidateView.count) {
                                wordCandidateView.currentIndex =
                                        wordCandidateView.effectiveLayoutDirection == Qt.LeftToRight ?
                                            (wordCandidateView.count - 1) : 0
                                break
                            }
                            break
                        }
                        keyboardInputArea.initialKey = initialKey
                        keyboardInputArea.navigateToNextKey(0, -1 * direction, true)
                    }
                    keyboardInputArea.navigateToNextKey(-1, 0, true)
                }
                break
            case Qt.Key_Up:
                if (languagePopupListActive) {
                    if (languagePopupList.currentIndex > 0) {
                        languagePopupList.decrementCurrentIndex()
                    } else if (languagePopupList.keyNavigationWraps) {
                        languagePopupList.currentIndex = languagePopupList.count - 1
                    } else {
                        hideLanguagePopup()
                        keyboardInputArea.setActiveKey(null)
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                    }
                } else if (alternativeKeys.active) {
                    alternativeKeys.close()
                    keyboardInputArea.setActiveKey(null)
                    keyboardInputArea.navigateToNextKey(0, 0, false)
                } else if (functionPopupList.active) {
                    functionPopupList.close()
                    keyboardInputArea.setActiveKey(null)
                    keyboardInputArea.navigateToNextKey(0, 0, false)
                } else if (wordCandidateContextMenu.active) {
                    if (wordCandidateContextMenuList.currentIndex > 0) {
                        wordCandidateContextMenuList.decrementCurrentIndex()
                    } else if (wordCandidateContextMenuList.keyNavigationWraps && wordCandidateContextMenuList.count > 1) {
                        wordCandidateContextMenuList.currentIndex = wordCandidateContextMenuList.count - 1
                    } else {
                        hideWordCandidateContextMenu()
                    }
                } else if (keyboard.navigationModeActive && !keyboardInputArea.initialKey && wordCandidateView.count) {
                    keyboardInputArea.navigateToNextKey(0, 0, false)
                    initialKey = keyboardInputArea.initialKey
                    if (!keyboardInputArea.navigateToNextKey(0, -1, false)) {
                        keyboardInputArea.initialKey = initialKey
                        keyboardInputArea.navigateToNextKey(0, -1, true)
                    } else {
                        keyboardInputArea.navigateToNextKey(0, 1, false)
                    }
                } else if (!keyboardInputArea.navigateToNextKey(0, -1, !keyboard.navigationModeActive || !keyboardInputArea.initialKey || wordCandidateView.count == 0)) {
                    if (wordCandidateView.currentIndex === -1)
                        wordCandidateView.incrementCurrentIndex()
                }
                break
            case Qt.Key_Right:
                if (keyboard.navigationModeActive && !keyboardInputArea.initialKey) {
                    if (languagePopupListActive) {
                        hideLanguagePopup()
                        keyboardInputArea.setActiveKey(null)
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                        break
                    }
                    if (alternativeKeys.active) {
                        if (alternativeKeys.listView.currentIndex + 1 < alternativeKeys.listView.count) {
                            alternativeKeys.listView.incrementCurrentIndex()
                        } else {
                            alternativeKeys.close()
                            keyboardInputArea.setActiveKey(null)
                            keyboardInputArea.navigateToNextKey(0, 0, false)
                        }
                        break
                    }
                    if (functionPopupList.active) {
                        if (functionPopupList.listView.currentIndex + 1 < functionPopupList.listView.count) {
                            functionPopupList.listView.incrementCurrentIndex()
                        } else {
                            functionPopupList.close()
                            keyboardInputArea.setActiveKey(null)
                            keyboardInputArea.navigateToNextKey(0, 0, false)
                        }
                        break
                    }
                    if (wordCandidateContextMenu.active) {
                        hideWordCandidateContextMenu()
                        break
                    }
                    if (wordCandidateView.count) {
                        if (wordCandidateView.effectiveLayoutDirection == Qt.LeftToRight &&
                                wordCandidateView.currentIndex + 1 < wordCandidateView.count) {
                            wordCandidateView.incrementCurrentIndex()
                        } else if (wordCandidateView.effectiveLayoutDirection == Qt.RightToLeft &&
                                   wordCandidateView.currentIndex > 0) {
                            wordCandidateView.decrementCurrentIndex()
                        } else {
                            keyboardInputArea.navigateToNextKey(0, 0, false)
                            initialKey = keyboardInputArea.initialKey
                            while (keyboardInputArea.navigateToNextKey(0, -1 * direction, false))
                                initialKey = keyboardInputArea.initialKey;
                            while (keyboardInputArea.navigateToNextKey(-1, 0, false))
                                initialKey = keyboardInputArea.initialKey;
                            keyboardInputArea.initialKey = initialKey
                            keyboardInputArea.navigateToNextKey(0, 0, false)
                        }
                        break
                    }
                }
                initialKey = keyboardInputArea.initialKey
                if (!keyboardInputArea.navigateToNextKey(1, 0, false)) {
                    keyboardInputArea.initialKey = initialKey
                    if (!keyboardInputArea.navigateToNextKey(0, 1 * direction, false)) {
                        if (wordCandidateView.count) {
                            wordCandidateView.currentIndex =
                                    wordCandidateView.effectiveLayoutDirection == Qt.LeftToRight ?
                                        0 : (wordCandidateView.count - 1)
                            break
                        }
                        keyboardInputArea.initialKey = initialKey
                        keyboardInputArea.navigateToNextKey(0, 1 * direction, true)
                    }
                    keyboardInputArea.navigateToNextKey(1, 0, true)
                }
                break
            case Qt.Key_Down:
                if (languagePopupListActive) {
                    if (languagePopupList.currentIndex + 1 < languagePopupList.count) {
                        languagePopupList.incrementCurrentIndex()
                    } else if (languagePopupList.keyNavigationWraps) {
                        languagePopupList.currentIndex = 0
                    } else {
                        hideLanguagePopup()
                        keyboardInputArea.setActiveKey(null)
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                    }
                } else if (alternativeKeys.active) {
                    alternativeKeys.close()
                    keyboardInputArea.setActiveKey(null)
                    keyboardInputArea.navigateToNextKey(0, 0, false)
                } else if (functionPopupList.active) {
                    functionPopupList.close()
                    keyboardInputArea.setActiveKey(null)
                    keyboardInputArea.navigateToNextKey(0, 0, false)
                } else if (wordCandidateContextMenu.active) {
                    if (wordCandidateContextMenuList.currentIndex + 1 < wordCandidateContextMenuList.count) {
                        wordCandidateContextMenuList.incrementCurrentIndex()
                    } else if (wordCandidateContextMenuList.keyNavigationWraps && wordCandidateContextMenuList.count > 1) {
                        wordCandidateContextMenuList.currentIndex = 0
                    } else {
                        hideWordCandidateContextMenu()
                        keyboardInputArea.setActiveKey(null)
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                    }
                } else if (keyboard.navigationModeActive && !keyboardInputArea.initialKey && wordCandidateView.count) {
                    keyboardInputArea.navigateToNextKey(0, 0, false)
                    initialKey = keyboardInputArea.initialKey
                    if (!keyboardInputArea.navigateToNextKey(0, 1, false)) {
                        keyboardInputArea.initialKey = initialKey
                        keyboardInputArea.navigateToNextKey(0, 1, true)
                    } else {
                        keyboardInputArea.navigateToNextKey(0, -1, false)
                    }
                } else if (!keyboardInputArea.navigateToNextKey(0, 1, !keyboard.navigationModeActive || !keyboardInputArea.initialKey || wordCandidateView.count == 0)) {
                    if (wordCandidateView.currentIndex === -1)
                        wordCandidateView.incrementCurrentIndex()
                }
                break
            case Qt.Key_Return:
                if (!keyboard.navigationModeActive)
                    break
                if (languagePopupListActive) {
                    if (!isAutoRepeat) {
                        languagePopupList.model.selectItem(languagePopupList.currentIndex)
                        keyboardInputArea.reset()
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                    }
                } else if (keyboardInputArea.initialKey) {
                    if (!isAutoRepeat) {
                        pressAndHoldTimer.restart()
                        keyboardInputArea.setActiveKey(keyboardInputArea.initialKey)
                        keyboardInputArea.press(keyboardInputArea.initialKey, true)
                    }
                } else if (!wordCandidateContextMenu.active && wordCandidateView.count > 0) {
                    if (!isAutoRepeat) {
                        pressAndHoldTimer.restart()
                    }
                }
                break
            default:
                break
            }
        }
        function onNavigationKeyReleased(key, isAutoRepeat) {
            switch (key) {
            case Qt.Key_Return:
                if (!keyboard.navigationModeActive) {
                    if (languagePopupListActive)
                        languagePopupList.model.selectItem(languagePopupList.currentIndex)
                    break
                }
                if (isAutoRepeat)
                    break
                if (!languagePopupListActive && !alternativeKeys.active && !functionPopupList.active && !wordCandidateContextMenu.active && keyboard.activeKey) {
                    keyboardInputArea.release(keyboard.activeKey)
                    pressAndHoldTimer.stop()
                    alternativeKeys.close()
                    functionPopupList.close()
                    keyboardInputArea.setActiveKey(null)
                    if (!languagePopupListActive && keyboardInputArea.navigationCursor !== Qt.point(-1, -1))
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                } else if (wordCandidateContextMenu.active) {
                    if (!wordCandidateContextMenu.openedByNavigationKeyLongPress) {
                        wordCandidateContextMenu.selectCurrentItem()
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                    } else {
                        wordCandidateContextMenu.openedByNavigationKeyLongPress = false
                    }
                } else if (alternativeKeys.active) {
                    if (!alternativeKeys.openedByNavigationKeyLongPress) {
                        alternativeKeys.clicked()
                        alternativeKeys.close()
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                        keyboardInputArea.reset()
                    } else {
                        alternativeKeys.openedByNavigationKeyLongPress = false
                    }
                } else if (functionPopupList.active) {
                    if (!functionPopupList.openedByNavigationKeyLongPress) {
                        functionPopupList.clicked()
                        functionPopupList.close()
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                        keyboardInputArea.reset()
                    } else {
                        functionPopupList.openedByNavigationKeyLongPress = false
                    }
                } else if (!wordCandidateContextMenu.active && wordCandidateView.count > 0) {
                    wordCandidateView.model.selectItem(wordCandidateView.currentIndex)
                    if (!InputContext.preeditText.length)
                        keyboardInputArea.navigateToNextKey(0, 1, true)
                }
                break
            default:
                break
            }
        }
    }
    Connections {
        target: InputContext.inputEngine
        function onVirtualKeyClicked(key, text, modifiers, isAutoRepeat) {
            if (isAutoRepeat && keyboard.activeKey)
                soundEffect.play(keyboard.activeKey.soundEffect)
            if (key !== Qt.Key_unknown && keyboardInputArea.dragSymbolMode) {
                keyboardInputArea.dragSymbolMode = false
                keyboard.symbolMode = false
            } else if (key === Qt.Key_Space) {
                var surroundingText = InputContext.surroundingText.trim()
                if (InputContext.priv.shiftHandler.sentenceEndingCharacters.indexOf(surroundingText.charAt(surroundingText.length-1)) >= 0)
                    keyboard.symbolMode = false
            }
        }
    }
    FolderListModel {
        id: layoutsModel
        nameFilters: ["$"]
        folder: VirtualKeyboardSettings.layoutPath
    }
    Connections {
        target: layoutsModel
        function onCountChanged() {
            updateDefaultLocale()
            localeIndex = defaultLocaleIndex
        }
    }
    AlternativeKeys {
        id: alternativeKeys
        objectName: "alternativeKeys"
        // Add some extra margin for decoration
        property real horizontalMargin: style.alternateKeysListItemWidth
        property real verticalMargin: style.alternateKeysListItemHeight
        property rect previewRect: Qt.rect(keyboard.x + alternativeKeys.listView.x - horizontalMargin,
                                           keyboard.y + alternativeKeys.listView.y - verticalMargin,
                                           alternativeKeys.listView.width + horizontalMargin * 2,
                                           alternativeKeys.listView.height + verticalMargin * 2)
        property bool openedByNavigationKeyLongPress
        onVisibleChanged: {
            if (visible)
                InputContext.priv.previewRectangle = Qt.binding(function() {return previewRect})
            else
                openedByNavigationKeyLongPress = false
            InputContext.priv.previewVisible = visible
        }
    }
    FunctionPopupList {
        id: functionPopupList
        property bool openedByNavigationKeyLongPress
    }
    Timer {
        id: pressAndHoldTimer
        interval: 500
        onTriggered: {
            if (keyboard.activeKey && keyboard.activeKey === keyboardInputArea.initialKey) {
                var origin = keyboard.mapFromItem(activeKey, activeKey.width / 2, 0)
                if (keyboard.activeKey.smallText === "\u2699" &&
                        functionPopupList.open(keyboard.activeKey, origin.x, origin.y)) {
                    InputContext.inputEngine.virtualKeyCancel()
                    keyboardInputArea.initialKey = null
                    functionPopupList.openedByNavigationKeyLongPress = keyboard.navigationModeActive
                } else if (alternativeKeys.open(keyboard.activeKey, origin.x, origin.y)) {
                    InputContext.inputEngine.virtualKeyCancel()
                    keyboardInputArea.initialKey = null
                    alternativeKeys.openedByNavigationKeyLongPress = keyboard.navigationModeActive
                } else if (keyboard.activeKey.key === Qt.Key_Context1 && !keyboard.symbolMode) {
                    InputContext.inputEngine.virtualKeyCancel()
                    keyboardInputArea.dragSymbolMode = true
                    keyboard.symbolMode = true
                    keyboardInputArea.initialKey = null
                    if (keyboardInputArea.navigationCursor !== Qt.point(-1, -1))
                        keyboardInputArea.navigateToNextKey(0, 0, false)
                }
            } else if (keyboardInputArea.dragSymbolMode &&
                       keyboard.activeKey &&
                       keyboard.activeKey.functionKey &&
                       !keyboard.activeKey.repeat) {
                InputContext.inputEngine.virtualKeyCancel()
                keyboardInputArea.click(keyboard.activeKey)
                keyboardInputArea.initialKey = null
                if (keyboardInputArea.navigationCursor !== Qt.point(-1, -1))
                    keyboardInputArea.navigateToNextKey(0, 0, false)
            } else if (!wordCandidateContextMenu.active && keyboard.navigationModeActive) {
                wordCandidateContextMenu.show(wordCandidateView.currentIndex)
                wordCandidateContextMenu.openedByNavigationKeyLongPress = keyboard.navigationModeActive
            }
        }
    }
    Timer {
        id: releaseInaccuracyTimer
        interval: 500
        onTriggered: {
            if (keyboardInputArea.pressed && activeTouchPoint && !alternativeKeys.active && !keyboardInputArea.dragSymbolMode && !functionPopupList.active) {
                var key = keyboardInputArea.keyOnPoint(activeTouchPoint.x, activeTouchPoint.y)
                if (key !== keyboard.activeKey) {
                    InputContext.inputEngine.virtualKeyCancel()
                    keyboardInputArea.setActiveKey(key)
                    keyboardInputArea.press(key, false)
                }
            }
        }
    }
    CharacterPreviewBubble {
        id: characterPreview
        objectName: "characterPreviewBubble"
        active: keyboardInputArea.pressed && !alternativeKeys.active && !functionPopupList.active
        property rect previewRect: Qt.rect(keyboard.x + characterPreview.x,
                                           keyboard.y + characterPreview.y,
                                           characterPreview.width,
                                           characterPreview.height)
    }
    Binding {
        target: InputContext.priv
        property: "previewRectangle"
        value: characterPreview.previewRect
        when: characterPreview.visible
        restoreMode: Binding.RestoreBinding
    }
    Binding {
        target: InputContext.priv
        property: "previewRectangle"
        value: languagePopupList.previewRect
        when: languagePopupListActive
        restoreMode: Binding.RestoreBinding
    }
    Binding {
        target: InputContext.priv
        property: "previewVisible"
        value: characterPreview.visible || languagePopupListActive
        restoreMode: Binding.RestoreBinding
    }
    Loader {
        id: styleLoader
        source: VirtualKeyboardSettings.style
        Binding {
            target: styleLoader.item
            property: "keyboardHeight"
            value: keyboardInnerContainer.height
            restoreMode: Binding.RestoreBinding
        }
    }
    Loader {
        id: naviationHighlight
        objectName: "naviationHighlight"
        property var highlightItem: {
            if (keyboard.navigationModeActive) {
                if (languagePopupListActive) {
                    return languagePopupList.highlightItem
                } else if (keyboardInputArea.initialKey) {
                    return keyboardInputArea.initialKey
                } else if (alternativeKeys.listView.count > 0) {
                    return alternativeKeys.listView.highlightItem
                } else if (functionPopupList.listView.count > 0) {
                    return functionPopupList.listView.highlightItem
                } else if (wordCandidateContextMenu.active) {
                    return wordCandidateContextMenuList.highlightItem
                } else if (wordCandidateView.count > 0) {
                    return wordCandidateView.highlightItem
                }
            }
            return keyboard
        }
        // Note: without "highlightItem.x - highlightItem.x" the binding does not work for alternativeKeys
        property var highlightItemOffset: highlightItem ? keyboard.mapFromItem(highlightItem, highlightItem.x - highlightItem.x, highlightItem.y - highlightItem.y) : ({x:0, y:0})
        property int moveDuration: 200
        property int resizeDuration: 200
        property alias xAnimation: xAnimation
        property alias yAnimation: yAnimation
        property alias widthAnimation: widthAnimation
        property alias heightAnimation: heightAnimation
        z: 2
        x: highlightItemOffset.x
        y: highlightItemOffset.y
        width: highlightItem ? highlightItem.width : 0
        height: highlightItem ? highlightItem.height : 0
        visible: keyboard.navigationModeActive && highlightItem !== null && highlightItem !== keyboard
        sourceComponent: keyboard.style.navigationHighlight
        Behavior on x {
            NumberAnimation { id: xAnimation; duration: naviationHighlight.moveDuration; easing.type: Easing.OutCubic }
        }
        Behavior on y {
            NumberAnimation { id: yAnimation; duration: naviationHighlight.moveDuration; easing.type: Easing.OutCubic }
        }
        Behavior on width {
            NumberAnimation { id: widthAnimation; duration: naviationHighlight.resizeDuration; easing.type: Easing.OutCubic }
        }
        Behavior on height {
            NumberAnimation { id: heightAnimation; duration: naviationHighlight.resizeDuration; easing.type: Easing.OutCubic }
        }
    }

    ShadowInputControl {
        id: shadowInputControl
        objectName: "shadowInputControl"
        z: -3
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: wordCandidateView.top
        height: keyboard.screenHeight -
                keyboard.height -
                wordCandidateView.height
        visible: fullScreenMode && (shadowInputControlVisibleTimer.running || InputContext.animating)

        Connections {
            target: keyboard
            function onActiveChanged() {
                if (keyboard.active)
                    shadowInputControlVisibleTimer.start()
                else
                    shadowInputControlVisibleTimer.stop()
            }
        }

        Timer {
            id: shadowInputControlVisibleTimer
            interval: 2147483647
            repeat: true
        }

        MouseArea {
            onPressed: keyboard.hideLanguagePopup()
            anchors.fill: parent
            enabled: languagePopupList.enabled
        }
    }

    SelectionControl {
        objectName: "fullScreenModeSelectionControl"
        inputContext: InputContext.priv.shadow
        anchors.top: shadowInputControl.top
        anchors.left: shadowInputControl.left
        enabled: keyboard.enabled && fullScreenMode
    }

    ListView {
        id: wordCandidateView
        objectName: "wordCandidateView"
        clip: true
        z: -2
        property bool empty: true
        readonly property bool visibleCondition: (((!wordCandidateView.empty || wordCandidateViewAutoHideTimer.running) &&
                                                   InputContext.inputEngine.wordCandidateListVisibleHint) || VirtualKeyboardSettings.wordCandidateList.alwaysVisible) &&
                                                 keyboard.active
        readonly property real visibleYOffset: -height
        readonly property real currentYOffset: visibleCondition ? visibleYOffset : 0
        height: style ? style.selectionListHeight : 0
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 0
        orientation: ListView.Horizontal
        snapMode: ListView.SnapToItem
        delegate: style.selectionListDelegate
        highlight: style.selectionListHighlight ? style.selectionListHighlight : defaultHighlight
        highlightMoveDuration: 0
        highlightResizeDuration: 0
        add: style.selectionListAdd
        remove: style.selectionListRemove
        keyNavigationWraps: true
        model: InputContext.inputEngine.wordCandidateListModel
        onCurrentItemChanged: if (currentItem) soundEffect.register(currentItem.soundEffect)
        Connections {
            target: wordCandidateView.model ? wordCandidateView.model : null
            function onActiveItemChanged(index) { wordCandidateView.currentIndex = index }
            function onItemSelected() { if (wordCandidateView.currentItem) soundEffect.play(wordCandidateView.currentItem.soundEffect) }
            function onCountChanged() {
                var empty = wordCandidateView.model.count === 0
                if (empty)
                    wordCandidateViewAutoHideTimer.restart()
                else
                    wordCandidateViewAutoHideTimer.stop()
                wordCandidateView.empty = empty
                keyboard.hideWordCandidateContextMenu()
            }
        }
        Connections {
            target: InputContext.priv
            function onInputItemChanged() { wordCandidateViewAutoHideTimer.stop() }
        }
        Connections {
            target: InputContext.inputEngine
            function onWordCandidateListVisibleHintChanged() { wordCandidateViewAutoHideTimer.stop() }
        }
        Timer {
            id: wordCandidateViewAutoHideTimer
            interval: VirtualKeyboardSettings.wordCandidateList.autoHideDelay
        }
        Loader {
            sourceComponent: style.selectionListBackground
            anchors.fill: parent
            z: -1
        }
        Component {
            id: defaultHighlight
            Item {}
        }
        states: [
            State {
                name: "visible"
                when: wordCandidateView.visibleCondition
                PropertyChanges {
                    target: wordCandidateView
                    y: wordCandidateView.visibleYOffset
                }
            },
            State {
                name: "alwaysVisible"
                when: keyboard.fullScreenMode || VirtualKeyboardSettings.wordCandidateList.alwaysVisible
                PropertyChanges {
                    target: wordCandidateView
                    y: wordCandidateView.visibleYOffset
                }
            }
        ]
        transitions: Transition {
            id: wordCandidateViewTransition
            from: ""
            to: "visible"
            enabled: !InputContext.animating
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }

        function longPressItem(index) {
            return keyboard.showWordCandidateContextMenu(index)
        }
    }

    Item {
        id: soundEffect
        property var __sounds: ({})
        property bool available: false

        signal playingChanged(url source, bool playing)

        Connections {
            target: VirtualKeyboardSettings
            function onStyleNameChanged() {
                soundEffect.__sounds = {}
                soundEffect.available = false
            }
        }

        function play(sound) {
            if (enabled && sound != Qt.resolvedUrl("")) {
                var soundId = Qt.md5(sound)
                var multiSoundEffect = __sounds[soundId]
                if (!multiSoundEffect)
                    multiSoundEffect = register(sound)
                if (multiSoundEffect)
                    multiSoundEffect.play()
            }
        }

        function register(sound) {
            var multiSoundEffect = null
            if (enabled && sound != Qt.resolvedUrl("")) {
                var soundId = Qt.md5(sound)
                multiSoundEffect = __sounds[soundId]
                if (!multiSoundEffect) {
                    multiSoundEffect = Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard; MultiSoundEffect {}', soundEffect)
                    if (multiSoundEffect) {
                        multiSoundEffect.playingChanged.connect(soundEffect.playingChanged)
                        multiSoundEffect.source = sound
                        __sounds[soundId] = multiSoundEffect
                        available = true
                    }
                }
            }
            return multiSoundEffect
        }
    }

    Loader {
        id: keyboardBackground
        z: -1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: keyboardInnerContainer.height
        sourceComponent: style.keyboardBackground

        Item {
            id: keyboardInnerContainer
            z: 1
            width: Math.round(keyboardBackground.width)
            height: style ? Math.round(style.keyboardDesignHeight * width / style.keyboardDesignWidth) : 0
            anchors.horizontalCenter: parent.horizontalCenter
            LayoutMirroring.enabled: false
            LayoutMirroring.childrenInherit: true

            KeyboardObserver {
                id: keyboardObserver

                function scanLayout() {
                    if (keyboardLayoutLoader.item == null)
                        return null

                    return keyboardLayoutLoader.item.scanLayout()
                }
            }

            Component.onCompleted: InputContext.priv.setKeyboardObserver(keyboardObserver)

            onWidthChanged: notifyLayoutChanged()
            onHeightChanged: notifyLayoutChanged()

            Loader {
                id: keyboardLayoutLoader
                objectName: "keyboardLayoutLoader"

                anchors.fill: parent
                anchors.leftMargin: Math.round(style.keyboardRelativeLeftMargin * parent.width)
                anchors.rightMargin: Math.round(style.keyboardRelativeRightMargin * parent.width)
                anchors.topMargin: Math.round(style.keyboardRelativeTopMargin * parent.height)
                anchors.bottomMargin: Math.round(style.keyboardRelativeBottomMargin * parent.height)

                Binding {
                    target: keyboardLayoutLoader
                    property: "source"
                    value: keyboard.layout
                    when: keyboard.width > 0 && keyboard.layout.length > 0
                    restoreMode: Binding.RestoreNone
                }

                onItemChanged: {
                    if (!item)
                        return

                    // Reset input mode if the new layout wants to override it
                    if (item.inputMode !== -1)
                        inputModeNeedsReset = true

                    if (!InputContext.inputEngine.inputMethod)
                        updateInputMethod()

                    notifyLayoutChanged()
                }

                MultiPointTouchArea {
                    id: keyboardInputArea
                    objectName: "keyboardInputArea"

                    property Item initialKey: null
                    property bool dragSymbolMode
                    property real releaseMargin: initialKey !== null ? Math.min(initialKey.width / 3, initialKey.height / 3) : 0
                    property point navigationCursor: Qt.point(-1, -1)

                    anchors.fill: keyboardLayoutLoader

                    Connections {
                        target: keyboardLayoutLoader
                        function onLoaded() {
                            if (keyboard.navigationModeActive &&
                                    keyboardInputArea.navigationCursor !== Qt.point(-1, -1))
                                keyboard.navigationModeActive = keyboardInputArea.navigateToNextKey(0, 0, false)
                        }
                    }
                    Connections {
                        target: keyboard
                        function onNavigationModeActiveChanged() {
                            if (!keyboard.navigationModeActive) {
                                keyboardInputArea.navigationCursor = Qt.point(-1, -1)
                                keyboardInputArea.reset()
                            }
                        }
                    }

                    function press(key, isRealPress) {
                        if (key && key.enabled) {
                            if (!key.noKeyEvent)
                                InputContext.inputEngine.virtualKeyPress(key.key, key.uppercased ? key.text.toUpperCase() : key.text, key.uppercased ? Qt.ShiftModifier : 0, key.repeat && !dragSymbolMode)
                            if (isRealPress)
                                soundEffect.play(key.soundEffect)
                        }
                    }
                    function release(key) {
                        if (key && key.enabled) {
                            if (!key.noKeyEvent)
                                InputContext.inputEngine.virtualKeyRelease(key.key, key.uppercased ? key.text.toUpperCase() : key.text, key.uppercased ? Qt.ShiftModifier : 0)
                            key.clicked()
                        }
                    }
                    function click(key) {
                        if (key && key.enabled) {
                            if (!key.noKeyEvent)
                                InputContext.inputEngine.virtualKeyClick(key.key, InputContext.uppercase ? key.text.toUpperCase() : key.text, InputContext.uppercase ? Qt.ShiftModifier : 0)
                            key.clicked()
                        }
                    }
                    function setActiveKey(activeKey) {
                        if (keyboard.activeKey === activeKey)
                            return
                        if (keyboard.activeKey) {
                            if (keyboard.activeKey.keyType === QtVirtualKeyboard.KeyType.FlickKey)
                                keyboard.activeKey.onKeyChanged.disconnect(onFlickKeyKeyChanged)
                            keyboard.activeKey.active = false
                        }
                        keyboard.activeKey = activeKey
                        if (keyboard.activeKey) {
                            keyboard.activeKey.active = true
                        }
                    }
                    function keyOnPoint(px, py) {
                        var parentItem = keyboardLayoutLoader
                        var child = parentItem.childAt(px, py)
                        while (child !== null) {
                            var position = parentItem.mapToItem(child, px, py)
                            px = position.x; py = position.y
                            parentItem = child
                            child = parentItem.childAt(px, py)
                            if (child && child.key !== undefined)
                                return child
                        }
                        return null
                    }
                    function hitInitialKey(x, y, margin) {
                        if (!initialKey)
                            return false
                        var position = initialKey.mapFromItem(keyboardInputArea, x, y)
                        return (position.x > -margin
                                && position.y > -margin
                                && position.x < initialKey.width + margin
                                && position.y < initialKey.height + margin)
                    }
                    function containsPoint(touchPoints, point) {
                        if (!point)
                            return false
                        for (var i in touchPoints)
                            if (touchPoints[i].pointId == point.pointId)
                                return true
                        return false
                    }
                    function releaseActiveKey() {
                        if (alternativeKeys.active) {
                            alternativeKeys.clicked()
                        } else if (functionPopupList.active) {
                            functionPopupList.clicked()
                        } else if (keyboard.activeKey) {
                            release(keyboard.activeKey)
                        }
                        reset()
                    }
                    function reset() {
                        releaseInaccuracyTimer.stop()
                        pressAndHoldTimer.stop()
                        setActiveKey(null)
                        activeTouchPoint = null
                        alternativeKeys.close()
                        functionPopupList.close()
                        if (dragSymbolMode) {
                            keyboard.symbolMode = false
                            dragSymbolMode = false
                        }
                    }
                    function nextKeyInNavigation(dX, dY, wrapEnabled) {
                        var nextKey = null, x, y, itemOffset
                        if (dX !== 0 || dY !== 0) {
                            var offsetX, offsetY
                            for (offsetX = dX, offsetY = dY;
                                 Math.abs(offsetX) < width && Math.abs(offsetY) < height;
                                 offsetX += dX, offsetY += dY) {
                                x = navigationCursor.x + offsetX
                                if (x < 0) {
                                    if (!wrapEnabled)
                                        break
                                    x += width
                                } else if (x >= width) {
                                    if (!wrapEnabled)
                                        break
                                    x -= width
                                }
                                y = navigationCursor.y + offsetY
                                if (y < 0) {
                                    if (!wrapEnabled)
                                        break
                                    y += height
                                } else if (y >= height) {
                                    if (!wrapEnabled)
                                        break
                                    y -= height
                                }
                                nextKey = keyOnPoint(x, y)
                                if (nextKey) {
                                    // Check if key is visible. Only the visible keys have keyPanelDelegate set.
                                    if (nextKey != initialKey && nextKey.hasOwnProperty("keyPanelDelegate") && nextKey.keyPanelDelegate)
                                        break
                                    // Jump over the item to reduce the number of iterations in this loop
                                    itemOffset = mapToItem(nextKey, x, y)
                                    if (dX > 0)
                                        offsetX += nextKey.width - itemOffset.x
                                    else if (dX < 0)
                                        offsetX -= itemOffset.x
                                    else if (dY > 0)
                                        offsetY += nextKey.height - itemOffset.y
                                    else if (dY < 0)
                                        offsetY -= itemOffset.y
                                }
                                nextKey = null
                            }
                        } else {
                            nextKey = keyOnPoint(navigationCursor.x, navigationCursor.y)
                        }
                        if (nextKey) {
                            itemOffset = mapFromItem(nextKey, nextKey.width / 2, nextKey.height / 2)
                            if (dX) {
                                x = itemOffset.x
                            } else if (dY) {
                                y = itemOffset.y
                            } else {
                                x = itemOffset.x
                                y = itemOffset.y
                            }
                            navigationCursor = Qt.point(x, y)
                        }
                        return nextKey
                    }
                    function navigateToNextKey(dX, dY, wrapEnabled) {
                        // Resolve initial landing point of the navigation cursor
                        if (!keyboard.navigationModeActive || keyboard.navigationCursor === Qt.point(-1, -1)) {
                            if (dX > 0)
                                navigationCursor = Qt.point(0, height / 2)
                            else if (dX < 0)
                                navigationCursor = Qt.point(width, height / 2)
                            else if (dY > 0)
                                navigationCursor = Qt.point(width / 2, 0)
                            else if (dY < 0)
                                navigationCursor = Qt.point(width / 2, height)
                            else
                                navigationCursor = Qt.point(width / 2, height / 2)
                            keyboard.navigationModeActive = true
                        }
                        if (dX && dY) {
                            initialKey = nextKeyInNavigation(dX, 0, wrapEnabled)
                            if (initialKey || wrapEnabled)
                                initialKey = nextKeyInNavigation(0, dY, wrapEnabled)
                        } else {
                            initialKey = nextKeyInNavigation(dX, dY, wrapEnabled)
                        }
                        return initialKey !== null
                    }

                    function onFlickKeyKeyChanged() {
                        InputContext.inputEngine.virtualKeyCancel()
                        press(activeKey, false)
                    }

                    onPressed: (touchPoints) => {
                        keyboard.navigationModeActive = false

                        // Immediately release any pending key that the user might be
                        // holding (and about to release) when a second key is pressed.
                        if (activeTouchPoint)
                            releaseActiveKey();

                        for (var i in touchPoints) {
                            // Release any key pressed by a previous iteration of the loop.
                            if (containsPoint(touchPoints, activeTouchPoint))
                                releaseActiveKey();

                            initialKey = keyOnPoint(touchPoints[i].x, touchPoints[i].y)
                            if (!initialKey)
                                continue
                            activeTouchPoint = touchPoints[i]
                            if (initialKey.keyType === QtVirtualKeyboard.KeyType.FlickKey) {
                                initialKey.press(activeTouchPoint.x, activeTouchPoint.y)
                                initialKey.onKeyChanged.connect(onFlickKeyKeyChanged)
                            } else {
                                releaseInaccuracyTimer.start()
                                pressAndHoldTimer.start()
                            }
                            setActiveKey(initialKey)
                            press(initialKey, true)
                        }
                    }
                    onUpdated: (touchPoints) => {
                        if (!containsPoint(touchPoints, activeTouchPoint))
                            return

                        if (alternativeKeys.active) {
                            alternativeKeys.move(mapToItem(alternativeKeys, activeTouchPoint.x, 0).x)
                        } else if (functionPopupList.active) {
                            functionPopupList.move(mapToItem(functionPopupList, activeTouchPoint.x, activeTouchPoint.y))
                        } else if (activeKey && activeKey.keyType === QtVirtualKeyboard.KeyType.FlickKey) {
                            activeKey.update(activeTouchPoint.x, activeTouchPoint.y)
                        } else {
                            var key = null
                            if (releaseInaccuracyTimer.running) {
                                if (hitInitialKey(activeTouchPoint.x, activeTouchPoint.y, releaseMargin)) {
                                    key = initialKey
                                } else if (initialKey) {
                                    releaseInaccuracyTimer.stop()
                                    initialKey = null
                                }
                            }
                            if (key === null) {
                                key = keyOnPoint(activeTouchPoint.x, activeTouchPoint.y)
                            }
                            if (key !== keyboard.activeKey) {
                                InputContext.inputEngine.virtualKeyCancel()
                                setActiveKey(key)
                                press(key, false)
                                if (dragSymbolMode) {
                                    if (key && key.functionKey && key.key !== Qt.Key_Context1)
                                        pressAndHoldTimer.restart()
                                    else
                                        pressAndHoldTimer.stop()
                                }
                            }
                        }
                    }
                    onReleased: (touchPoints) => {
                        if (containsPoint(touchPoints, activeTouchPoint)) {
                            if (dragSymbolMode) {
                                var key = keyOnPoint(activeTouchPoint.x, activeTouchPoint.y)
                                if (key && key.key === Qt.Key_Context1) {
                                    dragSymbolMode = false
                                    InputContext.inputEngine.virtualKeyCancel()
                                    reset()
                                    return
                                }
                            }
                            releaseActiveKey();
                        }
                    }
                    onCanceled: (touchPoints) => {
                        if (containsPoint(touchPoints, activeTouchPoint))
                            reset()
                    }
                }
            }
        }
    }

    Item {
        id: languagePopup
        z: 1
        anchors.fill: parent
        LayoutMirroring.enabled: false
        LayoutMirroring.childrenInherit: true

        MouseArea {
            onPressed: keyboard.hideLanguagePopup()
            anchors.fill: parent
            enabled: languagePopupList.enabled
        }

        PopupList {
            id: languagePopupList
            objectName: "languagePopupList"
            z: 2
            anchors.left: parent.left
            anchors.top: parent.top
            enabled: false
            model: languageListModel
            delegate: keyboard.style ? keyboard.style.languageListDelegate : null
            highlight: keyboard.style ? keyboard.style.languageListHighlight : defaultHighlight
            add: keyboard.style ? keyboard.style.languageListAdd : null
            remove: keyboard.style ? keyboard.style.languageListRemove : null
            property rect previewRect: Qt.rect(keyboard.x + languagePopupList.x,
                                               keyboard.y + languagePopupList.y,
                                               languagePopupList.width,
                                               languagePopupList.height)
        }

        Loader {
            sourceComponent: keyboard.style.languageListBackground
            anchors.fill: languagePopupList
            z: -1
            visible: languagePopupList.visible
        }

        ListModel {
            id: languageListModel

            function selectItem(index) {
                languagePopupList.currentIndex = index
                keyboard.soundEffect.play(languagePopupList.currentItem.soundEffect)
                changeLanguageTimer.newLocaleIndex = languageListModel.get(index).localeIndex
                changeLanguageTimer.start()
            }
        }

        Timer {
            id: changeLanguageTimer
            interval: 1
            property int newLocaleIndex
            onTriggered: {
                if (languagePopupListActive) {
                    hideLanguagePopup()
                    start()
                } else {
                    localeIndex = newLocaleIndex
                }
            }
        }

        function show(locales, parentItem, customLayoutsOnly) {
            if (!languagePopupList.enabled) {
                languageListModel.clear()
                for (var i = 0; i < locales.length; i++) {
                    languageListModel.append({localeName: locales[i].name, displayName: locales[i].locale.nativeLanguageName, localeIndex: locales[i].index})
                    if (locales[i].index === keyboard.localeIndex)
                        languagePopupList.currentIndex = i
                }
                languagePopupList.positionViewAtIndex(languagePopupList.currentIndex, ListView.Center)
                if (parentItem) {
                    languagePopupList.anchors.leftMargin = Qt.binding(function() {
                        const newLeftMargin = Math.round(keyboard.mapFromItem(parentItem, (parentItem.width - languagePopupList.width) / 2, 0).x)
                        return Math.min(Math.max(0, newLeftMargin), keyboard.width - languagePopupList.width)
                    })
                    languagePopupList.anchors.topMargin = Qt.binding(function() {return Math.round(keyboard.mapFromItem(parentItem, 0, -languagePopupList.height).y)})
                } else {
                    languagePopupList.anchors.leftMargin = Qt.binding(function() {return Math.round((keyboard.width - languagePopupList.width) / 2)})
                    languagePopupList.anchors.topMargin = Qt.binding(function() {return Math.round((keyboard.height - languagePopupList.height) / 2)})
                }
            }
            languagePopupList.enabled = true
        }

        function hide() {
            if (languagePopupList.enabled) {
                languagePopupList.enabled = false
                languagePopupList.anchors.leftMargin = undefined
                languagePopupList.anchors.topMargin = undefined
                languageListModel.clear()
            }
        }
    }

    function showLanguagePopup(parentItem, customLayoutsOnly) {
        var locales = keyboard.listLocales(customLayoutsOnly, parent.externalLanguageSwitchEnabled)
        if (parent.externalLanguageSwitchEnabled) {
            var currentIndex = 0
            for (var i = 0; i < locales.length; i++) {
                if (locales[i] === keyboard.locale) {
                    currentIndex = i
                    break
                }
            }
            parent.externalLanguageSwitch(locales, currentIndex)
            return
        }
        languagePopup.show(locales, parentItem, customLayoutsOnly)
    }

    function hideLanguagePopup() {
        languagePopup.hide()
    }

    MouseArea {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: keyboard.screenHeight
        onPressed: keyboard.hideWordCandidateContextMenu()
        enabled: wordCandidateContextMenuList.enabled
    }

    Item {
        id: wordCandidateContextMenu
        objectName: "wordCandidateContextMenu"
        z: 1
        anchors.fill: parent
        LayoutMirroring.enabled: false
        LayoutMirroring.childrenInherit: true
        property int previousWordCandidateIndex: -1
        readonly property bool active: wordCandidateContextMenuList.visible
        property bool openedByNavigationKeyLongPress

        PopupList {
            id: wordCandidateContextMenuList
            objectName: "wordCandidateContextMenuList"
            z: 2
            anchors.left: parent.left
            anchors.top: parent.top
            enabled: false
            model: wordCandidateContextMenuListModel
            property rect previewRect: Qt.rect(keyboard.x + wordCandidateContextMenuList.x,
                                               keyboard.y + wordCandidateContextMenuList.y,
                                               wordCandidateContextMenuList.width,
                                               wordCandidateContextMenuList.height)
        }

        ListModel {
            id: wordCandidateContextMenuListModel

            function selectItem(index) {
                wordCandidateContextMenu.previousWordCandidateIndex = -1
                wordCandidateContextMenuList.currentIndex = index
                keyboard.soundEffect.play(wordCandidateContextMenuList.currentItem.soundEffect)
                switch (get(index).action) {
                case "remove":
                    wordCandidateView.model.removeItem(wordCandidateView.currentIndex)
                    break
                }
                keyboard.hideWordCandidateContextMenu()
            }
        }

        function show(wordCandidateIndex) {
            if (wordCandidateContextMenu.enabled)
                wordCandidateContextMenu.hide()

            wordCandidateContextMenuListModel.clear()

            var canRemoveSuggestion = wordCandidateView.model.dataAt(wordCandidateIndex, SelectionListModel.Role.CanRemoveSuggestion)
            if (canRemoveSuggestion) {
                var dictionaryType = wordCandidateView.model.dataAt(wordCandidateIndex, SelectionListModel.Role.Dictionary)
                var removeItemText;
                switch (dictionaryType) {
                case SelectionListModel.DictionaryType.User:
                    //~ VirtualKeyboard Context menu for word suggestion if it can be removed from the user dictionary.
                    removeItemText = qsTr("Remove from dictionary")
                    break
                case SelectionListModel.DictionaryType.Default:
                    // Fallthrough
                default:
                    //~ VirtualKeyboard Context menu for word suggestion if it can be removed from the default dictionary.
                    removeItemText = qsTr("Block word")
                    break
                }
                wordCandidateContextMenuListModel.append({action: "remove", display: removeItemText, wordCompletionLength: 0})
            }

            if (wordCandidateContextMenuListModel.count === 0)
                return

            previousWordCandidateIndex = wordCandidateView.currentIndex
            wordCandidateView.currentIndex = wordCandidateIndex

            wordCandidateContextMenuList.anchors.leftMargin = Qt.binding(function() {
                if (!wordCandidateView.currentItem)
                    return 0
                var leftBorder = Math.round(wordCandidateView.mapFromItem(wordCandidateView.currentItem, (wordCandidateView.currentItem.width - wordCandidateContextMenuList.width) / 2, 0).x)
                var rightBorder = Math.round(wordCandidateContextMenuList.parent.width - wordCandidateContextMenuList.width)
                return Math.max(0, Math.min(leftBorder, rightBorder))
            })

            wordCandidateContextMenuList.enabled = true
        }

        function hide() {
            if (wordCandidateContextMenuList.enabled) {
                if (previousWordCandidateIndex !== -1) {
                    wordCandidateView.currentIndex = previousWordCandidateIndex
                    previousWordCandidateIndex = -1
                }
                wordCandidateContextMenuList.enabled = false
                wordCandidateContextMenuList.anchors.leftMargin = undefined
                wordCandidateContextMenuListModel.clear()
            }
            openedByNavigationKeyLongPress = false
        }

        function selectCurrentItem() {
            if (active && wordCandidateContextMenuList.currentIndex !== -1)
                wordCandidateContextMenuListModel.selectItem(wordCandidateContextMenuList.currentIndex)
        }
    }

    function showWordCandidateContextMenu(wordCandidateIndex) {
        wordCandidateContextMenu.show(wordCandidateIndex)
    }

    function hideWordCandidateContextMenu() {
        wordCandidateContextMenu.hide()
    }

    function updateInputMethod() {
        if (!keyboardLayoutLoader.item)
            return
        if (!InputContext.priv.focus)
            return

        // Reset the custom input method if it is not included in the list of shared layouts
        if (customInputMethod && !inputMethodNeedsReset && customInputMethodSharedLayouts.indexOf(layoutType) === -1)
            inputMethodNeedsReset = true

        var customInputMethodToDestroy = null
        if (inputMethodNeedsReset) {
            if (customInputMethod) {
                // Postpones the destruction of the custom input method after creating a new one
                // and after assigning it to the input engine. This allows the input method to clear
                // its state before destroying.
                customInputMethodToDestroy = customInputMethod
                customInputMethod = null
            }
            customInputMethodSharedLayouts = []
            inputMethodNeedsReset = false
        }

        var inputMethod = null
        var inputMode = InputContext.inputEngine.inputMode

        // Use input method from keyboard layout
        if (keyboardLayoutLoader.item.inputMethod) {
            inputMethod = keyboardLayoutLoader.item.inputMethod
        } else if (!customInputMethod) {
            try {
                customInputMethod = keyboardLayoutLoader.item.createInputMethod()
                if (customInputMethod) {
                    // Pull the list of shared layouts from the keyboard layout
                    if (keyboardLayoutLoader.item.sharedLayouts)
                        customInputMethodSharedLayouts = customInputMethodSharedLayouts.concat(keyboardLayoutLoader.item.sharedLayouts)

                    // Make sure the current layout is included in the list
                    if (customInputMethodSharedLayouts.indexOf(layoutType) === -1)
                        customInputMethodSharedLayouts.push(layoutType)

                    // Reset input mode, since inputEngine.inputModes is updated
                    inputModeNeedsReset = true
                }
            } catch (e) {
                console.error(e.message)
            }
        }
        if (!inputMethod) {
            if (customInputMethod) {
                inputMethod = customInputMethod
            } else if (!VirtualKeyboardSettings.defaultInputMethodDisabled) {
                inputMethod = defaultInputMethod
            } else {
                inputMethod = plainInputMethod
            }
        }

        var inputMethodChanged = InputContext.inputEngine.inputMethod !== inputMethod
        if (inputMethodChanged) {
            InputContext.inputEngine.inputMethod = inputMethod
        }

        if (InputContext.inputEngine.inputMethod) {
            var inputModes = InputContext.inputEngine.inputModes
            if (inputModes.length > 0) {
                // Reset to default input mode if the input locale has changed
                if (inputModeNeedsReset) {
                    inputMode = inputModes[0]

                    // Check the current layout for input mode override
                    if (keyboardLayoutLoader.item.inputMode !== -1)
                        inputMode = keyboardLayoutLoader.item.inputMode

                    // Update input mode automatically in handwriting mode
                    if (keyboard.handwritingMode) {
                        if (keyboard.dialableCharactersOnly && inputModes.indexOf(InputEngine.InputMode.Dialable) !== -1)
                            inputMode = InputEngine.InputMode.Dialable
                        else if ((keyboard.formattedNumbersOnly || keyboard.digitsOnly) && inputModes.indexOf(InputEngine.InputMode.Numeric) !== -1)
                            inputMode = InputEngine.InputMode.Numeric
                        else if (keyboardLayoutLoader.item.inputMode === -1)
                            inputMode = inputModes[0]
                    }

                    // Check the input method hints for input mode overrides
                    if (latinOnly)
                        inputMode = InputEngine.InputMode.Latin
                    if (preferNumbers)
                        inputMode = InputEngine.InputMode.Numeric
                }

                // Make sure the input mode is supported by the current input method
                if (inputModes.indexOf(inputMode) === -1)
                    inputMode = inputModes[0]

                if (InputContext.inputEngine.inputMode !== inputMode || inputMethodChanged || inputModeNeedsReset) {
                    InputContext.priv.setKeyboardObserver(keyboardObserver)
                    InputContext.inputEngine.inputMode = inputMode
                }

                inputModeNeedsReset = false
            }
        }

        if (customInputMethodToDestroy !== null)
            customInputMethodToDestroy.destroy()

        // Clear the toggle shift timer
        InputContext.priv.shiftHandler.clearToggleShiftTimer()
    }

    function updateLayout() {
        var newLayout
        newLayout = findLayout(locale, layoutType)
        if (!newLayout.length) {
            newLayout = findLayout(locale, "main")
        }
        layout = newLayout
        inputLocale = locale
        updateInputMethod()
    }

    function updateDefaultLocale() {
        updateAvailableLocaleIndices()
        if (layoutsModel.count > 0) {
            var defaultLocales = []
            if (isValidLocale(VirtualKeyboardSettings.locale))
                defaultLocales.push(VirtualKeyboardSettings.locale)
            if (isValidLocale(InputContext.locale))
                defaultLocales.push(InputContext.locale)
            if (VirtualKeyboardSettings.activeLocales.length > 0 && isValidLocale(VirtualKeyboardSettings.activeLocales[0]))
                defaultLocales.push(VirtualKeyboardSettings.activeLocales[0])
            if (VirtualKeyboardSettings.availableLocales.indexOf("en_GB") !== -1)
                defaultLocales.push("en_GB")
            if (availableLocaleIndices.length > 0)
                defaultLocales.push(layoutsModel.get(availableLocaleIndices[0], "fileName"))
            var newDefaultLocaleIndex = -1
            for (var i = 0; i < defaultLocales.length; i++) {
                newDefaultLocaleIndex = findLocale(defaultLocales[i], -1)
                if (availableLocaleIndices.indexOf(newDefaultLocaleIndex) !== -1)
                    break;
                newDefaultLocaleIndex = -1
            }
            defaultLocaleIndex = newDefaultLocaleIndex
        } else {
            defaultLocaleIndex = -1
        }
    }

    function filterLocaleIndices(filterCb) {
        var localeIndices = []
        for (var i = 0; i < layoutsModel.count; i++) {
            if (localeIndices.indexOf(i) === -1) {
                var localeName = layoutsModel.get(i, "fileName")
                if (filterCb(localeName) && findLayout(localeName, "main"))
                    localeIndices.push(i)
            }
        }
        return localeIndices
    }

    function updateAvailableLocaleIndices() {
        // Update list of all available locales
        var fallbackIndex = findFallbackIndex()
        var newIndices = filterLocaleIndices(function(localeName) {
            return isValidLocale(localeName)
        })

        // Handle case where the VirtualKeyboardSettings.activeLocales contains no valid entries
        // Fetch all locales by ignoring active locales setting
        var ignoreActiveLocales = newIndices.length === 0
        if (ignoreActiveLocales) {
            newIndices = filterLocaleIndices(function(localeName) {
                return isValidLocale(localeName, ignoreActiveLocales)
            })
        }

        // Fetch matching locale names
        var newAvailableLocales = []
        for (var i = 0; i < newIndices.length; i++) {
            newAvailableLocales.push(layoutsModel.get(newIndices[i], "fileName"))
        }

        newAvailableLocales.sort()

        var sortOrder = !ignoreActiveLocales && VirtualKeyboardSettings.activeLocales.length > 0 ?
                    VirtualKeyboardSettings.activeLocales :
                    newAvailableLocales

        newIndices.sort(function(localeIndexA, localeIndexB) {
            var localeNameA = layoutsModel.get(localeIndexA, "fileName")
            var localeNameB = layoutsModel.get(localeIndexB, "fileName")
            var sortIndexA = sortOrder.indexOf(localeNameA)
            var sortIndexB = sortOrder.indexOf(localeNameB)
            return sortIndexA - sortIndexB
        })

        availableLocaleIndices = newIndices
        InputContext.priv.updateAvailableLocales(newAvailableLocales)

        // Update list of custom locale indices
        newIndices = []
        for (i = 0; i < availableLocaleIndices.length; i++) {
            if (availableLocaleIndices[i] === localeIndex ||
                    layoutExists(layoutsModel.get(availableLocaleIndices[i], "fileName"), layoutType))
                newIndices.push(availableLocaleIndices[i])
        }
        availableCustomLocaleIndices = newIndices
    }

    function listLocales(customLayoutsOnly, localeNameOnly) {
        var locales = []
        var localeIndices = customLayoutsOnly ? availableCustomLocaleIndices : availableLocaleIndices
        for (var i = 0; i < localeIndices.length; i++) {
            var layoutFolder = layoutsModel.get(localeIndices[i], "fileName")
            if (localeNameOnly)
                locales.push(layoutFolder)
            else
                locales.push({locale:Qt.locale(layoutFolder), index:localeIndices[i], name:layoutFolder})
        }
        return locales
    }

    function nextLocaleIndex(customLayoutsOnly) {
        var newLocaleIndex = localeIndex
        var localeIndices = customLayoutsOnly ? availableCustomLocaleIndices : availableLocaleIndices
        var i = localeIndices.indexOf(localeIndex)
        if (i !== -1) {
            i = (i + 1) % localeIndices.length
            newLocaleIndex = localeIndices[i]
        }
        return newLocaleIndex
    }

    function changeInputLanguage(customLayoutsOnly) {
        var newLocaleIndex = nextLocaleIndex(customLayoutsOnly)
        if (newLocaleIndex !== -1 && newLocaleIndex !== localeIndex)
            localeIndex = newLocaleIndex
    }

    function canChangeInputLanguage(customLayoutsOnly) {
        if (customLayoutsOnly)
            return availableCustomLocaleIndices.length > 1
        return availableLocaleIndices.length > 1
    }

    function findLocale(localeName, defaultValue) {
        var languageCode = localeName.substring(0, 3) // Including the '_' delimiter
        var languageMatch = -1
        for (var i = 0; i < layoutsModel.count; i++) {
            if (!layoutsModel.isFolder(i))
                continue
            var layoutFolder = layoutsModel.get(i, "fileName")
            if (layoutFolder === localeName)
                return i
            if (languageMatch == -1 && layoutFolder.substring(0, 3) === languageCode)
                languageMatch = i
        }
        return (languageMatch != -1) ? languageMatch : defaultValue
    }

    function findFallbackIndex() {
        for (var i = 0; i < layoutsModel.count; i++) {
            var layoutFolder = layoutsModel.get(i, "fileName")
            if (layoutFolder === "fallback")
                return i
        }
        return -1
    }

    function isValidLocale(localeNameOrIndex, ignoreActiveLocales) {
        var localeName
        if (typeof localeNameOrIndex == "number") {
            if (localeNameOrIndex < 0 || localeNameOrIndex >= layoutsModel.count)
                return false
            localeName = layoutsModel.get(localeNameOrIndex, "fileName")
        } else {
            localeName = localeNameOrIndex
        }

        if (!localeName)
            return false

        if (localeName === "fallback")
            return false

        if (Qt.locale(localeName).name === "C")
            return false

        if (ignoreActiveLocales !== true &&
                VirtualKeyboardSettings.activeLocales.length > 0 &&
                VirtualKeyboardSettings.activeLocales.indexOf(localeName) === -1)
            return false

        return true
    }

    function getLayoutFile(localeName, layoutType) {
        if (localeName === "" || layoutType === "")
            return ""
        return layoutsModel.folder + "/" + localeName + "/" + layoutType + ".qml"
    }

    function getFallbackFile(localeName, layoutType) {
        if (localeName === "" || layoutType === "")
            return ""
        return layoutsModel.folder + "/" + localeName + "/" + layoutType + ".fallback"
    }

    function layoutExists(localeName, layoutType) {
        var result = InputContext.priv.fileExists(getLayoutFile(localeName, layoutType))
        if (!result && layoutType === "handwriting")
            result = InputContext.priv.fileExists(getFallbackFile(localeName, layoutType))
        return result
    }

    function findLayout(localeName, layoutType) {
        var layoutFile = getLayoutFile(localeName, layoutType)
        if (InputContext.priv.fileExists(layoutFile))
            return layoutFile
        var fallbackFile = getFallbackFile(localeName, layoutType)
        if (InputContext.priv.fileExists(fallbackFile)) {
            layoutFile = getLayoutFile("fallback", layoutType)
            if (InputContext.priv.fileExists(layoutFile))
                return layoutFile
        }
        return ""
    }

    function isHandwritingAvailable() {
        if (VirtualKeyboardSettings.handwritingModeDisabled)
            return false
        return VirtualKeyboardFeatures.Handwriting && layoutExists(locale, "handwriting")
    }

    function setHandwritingMode(enabled, resetInputMode) {
        if (VirtualKeyboardSettings.handwritingModeDisabled)
            return
        if (enabled && resetInputMode)
            inputModeNeedsReset = true
        handwritingMode = enabled
    }

    function notifyLayoutChanged() {
        Qt.callLater(function() {
            if (keyboardLayoutLoader.item != null) keyboardObserver.layoutChanged()
        })
    }

    function doKeyboardFunction(keyboardFunction) {
        if (!isKeyboardFunctionAvailable(keyboardFunction))
            return
        switch (keyboardFunction) {
        case QtVirtualKeyboard.KeyboardFunction.HideInputPanel:
            InputContext.priv.hideInputPanel()
            break
        case QtVirtualKeyboard.KeyboardFunction.ChangeLanguage:
            if (style.languagePopupListEnabled) {
                if (!languagePopupListActive) {
                    showLanguagePopup(activeKey, false)
                } else {
                    hideLanguagePopup()
                }
            } else {
                const customLayoutsOnly = arguments.length == 2 && arguments[1]
                changeInputLanguage(customLayoutsOnly)
            }
            break
        case QtVirtualKeyboard.KeyboardFunction.ToggleHandwritingMode:
            setHandwritingMode(!handwritingMode)
            break
        default:
            console.warn("Unknown keyboard function '%1'".arg(keyboardFunction))
            break
        }
    }

    function isKeyboardFunctionAvailable(keyboardFunction) {
        switch (keyboardFunction) {
        case QtVirtualKeyboard.KeyboardFunction.HideInputPanel:
            return true
        case QtVirtualKeyboard.KeyboardFunction.ChangeLanguage:
            const customLayoutsOnly = arguments.length == 2 && arguments[1]
            return canChangeInputLanguage(customLayoutsOnly)
        case QtVirtualKeyboard.KeyboardFunction.ToggleHandwritingMode:
            return isHandwritingAvailable()
        default:
            return false
        }
    }

    function isFunctionPopupListAvailable() {
        const allFunctionKeys = QtVirtualKeyboard.KeyboardFunctionKeys.Hide |
                              QtVirtualKeyboard.KeyboardFunctionKeys.Language
        return (VirtualKeyboardSettings.visibleFunctionKeys & allFunctionKeys) !== allFunctionKeys ||
                isHandwritingAvailable()
    }
}
