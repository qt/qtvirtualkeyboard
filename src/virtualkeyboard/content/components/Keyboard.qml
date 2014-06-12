/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Enterprise.VirtualKeyboard 1.0
import QtQuick.Enterprise.VirtualKeyboard.Styles 1.0
import Qt.labs.folderlistmodel 2.0

Item {
    id: keyboard

    property alias style: styleLoader.item
    property var activeKey: null
    property TouchPoint activeTouchPoint
    property int localeIndex: -1
    property var availableLocaleIndices: []
    property string locale: localeIndex >= 0 && localeIndex < layoutsModel.count ? layoutsModel.get(localeIndex, "fileName") : ""
    property string inputLocale
    property int defaultLocaleIndex: -1
    property string defaultLocale: defaultLocaleIndex >= 0 && defaultLocaleIndex < layoutsModel.count ? layoutsModel.get(defaultLocaleIndex, "fileName") : ""
    property string layout
    property string layoutType: {
        if (keyboard.dialpadMode) return "dialpad"
        if (keyboard.numberMode) return "numbers"
        if (keyboard.digitMode) return "digits"
        if (keyboard.symbolMode) return "symbols"
        return "main"
    }
    property bool active: Qt.inputMethod.visible
    property bool uppercased: uppercaseOnly ? true : (lowercaseOnly ? false : InputContext.shift || InputContext.capsLock)
    property bool uppercaseOnly: InputContext.inputMethodHints & Qt.ImhUppercaseOnly
    property bool lowercaseOnly: InputContext.inputMethodHints & Qt.ImhLowercaseOnly
    property bool dialpadMode: InputContext.inputMethodHints & Qt.ImhDialableCharactersOnly
    property bool numberMode: InputContext.inputMethodHints & Qt.ImhFormattedNumbersOnly
    property bool digitMode: InputContext.inputMethodHints & Qt.ImhDigitsOnly
    property bool latinOnly: InputContext.inputMethodHints & (Qt.ImhHiddenText | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText | Qt.ImhLatinOnly)
    property bool symbolMode
    property bool shiftChanged: true
    property var defaultInputMethod: initDefaultInputMethod()
    property var plainInputMethod: PlainInputMethod {}
    property int defaultInputMode: InputEngine.Latin
    property bool inputModeNeedsReset: true

    function initDefaultInputMethod() {
        try {
            return Qt.createQmlObject('import QtQuick 2.0; import QtQuick.Enterprise.VirtualKeyboard 1.0; HunspellInputMethod {}', keyboard, "defaultInputMethod")
        } catch (e) { }
        return plainInputMethod
    }

    width: keyboardBackground.width
    height: wordCandidateView.height + keyboardBackground.height
    onLocaleChanged: {
        inputModeNeedsReset = true
        updateLayout()
    }
    onInputLocaleChanged: {
        if (Qt.locale(inputLocale).name !== "C")
            InputContext.locale = inputLocale
    }
    onLayoutTypeChanged: {
        updateAvailableLocaleIndices()
        updateLayout()
    }
    onUppercasedChanged: shiftChanged = true
    onLatinOnlyChanged: {
        updateLayout()
        updateInputMethod()
    }

    Connections {
        target: InputContext
        onFocusEditorChanged: {
            keyboard.symbolMode = false
        }
        onInputMethodHintsChanged: {
            if (InputContext.inputMethodHints & Qt.ImhPreferNumbers) {
                symbolMode = true
            }
        }
        onInputItemChanged: {
            inputModeNeedsReset = true
        }
    }
    Connections {
        target: InputContext.inputEngine
        onVirtualKeyClicked: {
            if (key === Qt.Key_Space) {
                var surroundingText = InputContext.surroundingText.trim()
                if (InputContext.shiftHandler.sentenceEndingCharacters.indexOf(surroundingText.charAt(surroundingText.length-1)) >= 0)
                    keyboard.symbolMode = false
            }
        }
    }
    FolderListModel {
        id: layoutsModel
        folder: "../layouts"
        nameFilters: ["$"]
    }
    Connections {
        target: layoutsModel
        onCountChanged: {
            if (layoutsModel.count > 0) {
                defaultLocaleIndex = findLocale("en_GB", -1)
                if (localeIndex == -1) {
                    // Find an initial layout which matches the current input locale
                    localeIndex = findLocale(InputContext.locale, defaultLocaleIndex)
                } else {
                    // Make sure the index matches to current locale
                    localeIndex = findLocale(keyboard.locale, defaultLocaleIndex)
                }
            } else {
                defaultLocaleIndex = -1
                localeIndex = -1
            }
            updateAvailableLocaleIndices()
        }
    }
    AlternativeKeys { id: alternativeKeys }
    Timer {
        id: pressAndHoldTimer
        interval: 800
        onTriggered: {
            if (keyboard.activeKey && keyboard.activeKey === keyboardInputArea.initialKey) {
                var origin = keyboard.mapFromItem(activeKey, activeKey.width / 2, 0)
                if (alternativeKeys.open(keyboard.activeKey, origin.x, origin.y)) {
                    InputContext.inputEngine.virtualKeyCancel()
                } else if (keyboard.activeKey.key === Qt.Key_Context1) {
                    InputContext.inputEngine.virtualKeyCancel()
                    keyboardInputArea.dragSymbolMode = true
                    keyboard.symbolMode = true
                }
            }
        }
    }
    Timer {
        id: releaseInaccuracyTimer
        interval: 500
        onTriggered: {
            if (keyboardInputArea.pressed && !alternativeKeys.active && !keyboardInputArea.dragSymbolMode) {
                var key = keyboardInputArea.keyOnPoint(activeTouchPoint.x, activeTouchPoint.y)
                if (key !== keyboard.activeKey) {
                    InputContext.inputEngine.virtualKeyCancel()
                    keyboardInputArea.setActiveKey(key)
                    keyboardInputArea.press(key)
                }
            }
        }
    }
    CharacterPreviewBubble { active: keyboardInputArea.pressed && !alternativeKeys.active }
    Binding {
        target: InputContext
        property: "keyboardRectangle"
        value: Qt.rect(keyboard.x, keyboard.y, keyboard.width, keyboard.height)
        when: !InputContext.animating
    }
    Loader {
        id: styleLoader
        source: "qrc:/style.qml"
        Binding {
            target: styleLoader.item
            property: "keyboardHeight"
            value: keyboardInnerContainer.height
        }
    }
    ListView {
        id: wordCandidateView
        clip: true
        height: Math.round(style.selectionListHeight)
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        spacing: 0
        orientation: ListView.Horizontal
        delegate: style.selectionListDelegate
        highlight: style.selectionListHighlight
        highlightMoveDuration: 0
        model: InputContext.inputEngine.wordCandidateListModel
        Connections {
            target: wordCandidateView.model ? wordCandidateView.model : null
            onActiveItemChanged: wordCandidateView.currentIndex = index
        }
        Loader {
            sourceComponent: style.selectionListBackground
            anchors.fill: parent
            z: -1
        }
    }

    Loader {
        id: keyboardBackground
        z: -1
        anchors.left: parent.left
        anchors.top: wordCandidateView.bottom
        anchors.right: parent.right
        height: keyboardInnerContainer.height
        sourceComponent: style.keyboardBackground

        Item {
            id: keyboardInnerContainer
            z: 1
            width: Math.round(keyboardBackground.width)
            height: Math.round(style.keyboardDesignHeight * width / style.keyboardDesignWidth)
            anchors.horizontalCenter: parent.horizontalCenter

            Loader {
                id: keyboardLayoutLoader

                anchors.fill: parent
                anchors.leftMargin: Math.round(style.keyboardRelativeLeftMargin * parent.width)
                anchors.rightMargin: Math.round(style.keyboardRelativeRightMargin * parent.width)
                anchors.topMargin: Math.round(style.keyboardRelativeTopMargin * parent.height)
                anchors.bottomMargin: Math.round(style.keyboardRelativeBottomMargin * parent.height)

                Binding {
                    target: keyboardLayoutLoader
                    property: "source"
                    value: keyboard.layout
                    when: keyboard.layout.length > 0
                }
                onItemChanged: if (keyboardLayoutLoader.item) keyboard.updateInputMethod()

                MultiPointTouchArea {
                    id: keyboardInputArea

                    property var initialKey: null
                    property bool dragSymbolMode
                    property real releaseMargin: 18

                    anchors.fill: keyboardLayoutLoader

                    function press(key) {
                        if (key && key.enabled) {
                            if (key.key !== Qt.Key_unknown || key.text.length > 0)
                                InputContext.inputEngine.virtualKeyPress(key.key, keyboard.uppercased ? key.text.toUpperCase() : key.text, keyboard.uppercased ? Qt.ShiftModifier : 0, key.repeat)
                        }
                    }
                    function release(key) {
                        if (key && key.enabled) {
                            if (key.key !== Qt.Key_unknown || key.text.length > 0)
                                InputContext.inputEngine.virtualKeyRelease(key.key, keyboard.uppercased ? key.text.toUpperCase() : key.text, keyboard.uppercased ? Qt.ShiftModifier : 0)
                            key.clicked()
                        }
                    }
                    function click(key) {
                        if (key && key.enabled) {
                            if (key.key !== Qt.Key_unknown || key.text.length > 0)
                                InputContext.inputEngine.virtualKeyClick(key.key, keyboard.uppercased ? key.text.toUpperCase() : key.text, keyboard.uppercased ? Qt.ShiftModifier : 0)
                            key.clicked()
                        }
                    }
                    function setActiveKey(activeKey) {
                        if (keyboard.activeKey === activeKey)
                            return
                        if (keyboard.activeKey) {
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
                        } else if (keyboard.activeKey) {
                            release(keyboard.activeKey)
                        }
                        reset()
                    }
                    function reset() {
                        releaseInaccuracyTimer.stop()
                        pressAndHoldTimer.stop()
                        alternativeKeys.close()
                        setActiveKey(null)
                        activeTouchPoint = null
                        if (dragSymbolMode) {
                            keyboard.symbolMode = false
                            dragSymbolMode = false
                        }
                    }

                    onPressed: {
                        // Immediately release any pending key that the user might be
                        // holding (and about to release) when a second key is pressed.
                        if (activeTouchPoint)
                            releaseActiveKey();

                        for (var i in touchPoints) {
                            // Release any key pressed by a previous iteration of the loop.
                            if (containsPoint(touchPoints, activeTouchPoint))
                                releaseActiveKey();

                            releaseInaccuracyTimer.start()
                            pressAndHoldTimer.start()
                            initialKey = keyOnPoint(touchPoints[i].x, touchPoints[i].y)
                            activeTouchPoint = touchPoints[i]
                            setActiveKey(initialKey)
                            press(initialKey)
                        }
                    }
                    onUpdated: {
                        if (!containsPoint(touchPoints, activeTouchPoint))
                            return

                        if (alternativeKeys.active) {
                            alternativeKeys.move(mapToItem(alternativeKeys, activeTouchPoint.x, 0).x)
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
                                press(key)
                            }
                        }
                    }
                    onReleased: {
                        if (containsPoint(touchPoints, activeTouchPoint))
                            releaseActiveKey();
                    }
                    onCanceled: {
                        if (containsPoint(touchPoints, activeTouchPoint))
                            reset()
                    }
                }
            }
        }
    }

    function updateInputMethod() {
        var inputMethod = null
        var inputMode = InputContext.inputEngine.inputMode
        // Force plain input method in password mode
        if (latinOnly) {
            inputMethod = keyboard.plainInputMethod
            inputMode = InputEngine.Latin
        } else if (keyboardLayoutLoader.item) {
            // Use input method from keyboard layout
            if (keyboardLayoutLoader.item.inputMethod) {
                inputMethod = keyboardLayoutLoader.item.inputMethod
            } else {
                inputMethod = keyboard.defaultInputMethod
            }
            if (keyboardLayoutLoader.item.inputMode !== -1) {
                inputMode = keyboardLayoutLoader.item.inputMode
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
                if (inputModeNeedsReset || inputModes.indexOf(inputMode) === -1) {
                    inputMode = inputModes[0]
                }
                if (InputContext.inputEngine.inputMode !== inputMode || inputMethodChanged || inputModeNeedsReset) {
                    InputContext.inputEngine.inputMode = inputMode
                }
                inputModeNeedsReset = false
            }
        }
    }

    function updateLayout() {
        var newLayout
        newLayout = findLayout(latinOnly ? defaultLocale : locale, layoutType)
        if (!newLayout.length) {
            newLayout = findLayout(latinOnly ? defaultLocale : locale, "main")
        }
        inputLocale = !latinOnly && layoutExists(locale, layoutType) ? locale : defaultLocale
        layout = newLayout
    }

    function updateAvailableLocaleIndices() {
        var newIndices = []
        // Keep the current locale in the list of available locales
        if (localeIndex !== -1) {
            newIndices.push(localeIndex)
        }
        for (var i = 0; i < layoutsModel.count; i++) {
            if (isValidLocale(i)) {
                if (newIndices.indexOf(i) === -1) {
                    // Add other locales, which resolve into actual layout file, excluding the default layout
                    if (layoutExists(layoutsModel.get(i, "fileName"), layoutType) && i !== defaultLocaleIndex) {
                        newIndices.push(i)
                    }
                }
            }
        }
        // Add default layout if any of the available locales do not resolve into it
        var addDefault = true
        var defaultLayout = getLayoutFile(keyboard.defaultLocale, layoutType)
        for (i = 0; i < newIndices.length; i++) {
            if (newIndices[i] === defaultLocaleIndex || findLayout(layoutsModel.get(newIndices[i], "fileName"), layoutType) === defaultLayout) {
                addDefault = false
                break
            }
        }
        if (addDefault) {
            newIndices.push(defaultLocaleIndex)
        }
        newIndices.sort()
        availableLocaleIndices = newIndices
    }

    function nextLocaleIndex(customLayoutsOnly) {
        var newLocaleIndex = localeIndex
        var i = availableLocaleIndices.indexOf(localeIndex)
        if (i !== -1) {
            i = (i + 1) % availableLocaleIndices.length
            newLocaleIndex = availableLocaleIndices[i]
        }
        return newLocaleIndex
    }

    function changeInputLanguage(customLayoutsOnly) {
        var newLocaleIndex = nextLocaleIndex(customLayoutsOnly)
        if (newLocaleIndex !== -1 && newLocaleIndex !== localeIndex)
            localeIndex = newLocaleIndex
    }

    function canChangeInputLanguage(customLayoutsOnly) {
        return !latinOnly && availableLocaleIndices.length > 1
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

    function isValidLocale(index) {
        if (index < 0 || index >= layoutsModel.count)
            return false
        return Qt.locale(layoutsModel.get(index, "fileName")).name !== "C"
    }

    function getLayoutFile(localeName, layoutType) {
        return layoutsModel.folder + "/" + localeName + "/" + layoutType + ".qml"
    }

    function layoutExists(localeName, layoutType) {
        return InputContext.fileExists(getLayoutFile(localeName, layoutType))
    }

    function findLayout(localeName, layoutType) {
        var layoutFile = getLayoutFile(localeName, layoutType)
        if (InputContext.fileExists(layoutFile))
            return layoutFile
        layoutFile = getLayoutFile(keyboard.defaultLocale, layoutType)
        if (InputContext.fileExists(layoutFile))
            return layoutFile
        return ""
    }
}
