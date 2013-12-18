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
import QtVkb 1.0
import QtVkb.Styles 1.0
import Qt.labs.folderlistmodel 2.0

Item {
    id: keyboard

    property alias style: styleLoader.item
    property var activeKey: undefined
    property int localeIndex: 1
    property string locale: layoutsModel.count > 0 ? layoutsModel.get(localeIndex, "fileBaseName") : "en_GB"
    property string layout: keyboard.symbolMode && !keyboard.numberMode ? "symbols_"+keyboard.locale : (keyboard.numberMode ? "numbers" : keyboard.locale)
    property bool active: Qt.inputMethod.visible
    property bool uppercased: uppercaseOnly ? true : (lowercaseOnly ? false : InputContext.shift || InputContext.capsLock)
    property bool uppercaseOnly: InputContext.inputMethodHints & Qt.ImhUppercaseOnly
    property bool lowercaseOnly: InputContext.inputMethodHints & Qt.ImhLowercaseOnly
    property bool numberMode: InputContext.inputMethodHints & (Qt.ImhDialableCharactersOnly | Qt.ImhFormattedNumbersOnly | Qt.ImhDigitsOnly)
    property bool symbolMode
    property bool shiftChanged: true
    property var defaultInputMethod: initDefaultInputMethod()
    property var plainInputMethod: PlainInputMethod {}
    property int defaultInputMode: InputEngine.Latin

    function initDefaultInputMethod() {
        try {
            return Qt.createQmlObject('import QtQuick 2.0; import QtVkb 1.0; HunspellInputMethod {}', keyboard, "defaultInputMethod")
        } catch (e) { }
        return plainInputMethod
    }

    width: keyboardBackground.width
    height: wordCandidateView.height + keyboardBackground.height
    onLocaleChanged: InputContext.locale = locale
    onUppercasedChanged: shiftChanged = true

    function changeInputLanguage() {
        localeIndex = (localeIndex+1) % layoutsModel.count
    }

    Connections {
        target: InputContext
        onFocusEditorChanged: {
            keyboard.symbolMode = false
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
        nameFilters: ["??_??.qml"]
    }
    AlternativeKeys { id: alternativeKeys }
    Timer {
        id: releaseInaccuracyTimer
        interval: 500
        onTriggered: {
            if (keyboardMouse.pressed && !alternativeKeys.active && !keyboardMouse.dragSymbolMode) {
                var key = keyboardMouse.keyOnMouse(keyboardMouse.mouseX, keyboardMouse.mouseY)
                if (key !== keyboard.activeKey) {
                    InputContext.inputEngine.virtualKeyCancel()
                    keyboardMouse.setActiveKey(key)
                    keyboardMouse.press(key)
                }
            }
        }
    }
    CharacterPreviewBubble { active: keyboardMouse.pressed && !alternativeKeys.active }
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
            when: keyboardLayoutLoader.item !== null
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

                source: layoutsModel.folder + "/" + keyboard.layout +".qml"
                onItemChanged: if (keyboardLayoutLoader.item) keyboard.updateInputMethod()

                MouseArea {
                    id: keyboardMouse

                    property var initialKey
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
                        if (keyboard.activeKey) {
                            keyboard.activeKey.active = false
                        }
                        keyboard.activeKey = activeKey
                        if (keyboard.activeKey) {
                            keyboard.activeKey.active = true
                        }
                    }
                    function keyOnMouse(mx, my) {
                        var parentItem = keyboardLayoutLoader
                        var child = parentItem.childAt(mx, my)
                        while (child !== null) {
                            var position = parentItem.mapToItem(child, mx, my)
                            mx = position.x; my = position.y
                            parentItem = child
                            child = parentItem.childAt(mx, my)
                            if (child && child.key !== undefined)
                                return child
                        }
                        return undefined
                    }
                    function hitInitialKey(mouseX, mouseY, margin) {
                        if (!initialKey)
                            return false
                        var position = initialKey.mapFromItem(keyboardMouse, mouseX, mouseY)
                        return (position.x > -margin
                                && position.y > -margin
                                && position.x < initialKey.width + margin
                                && position.y < initialKey.height + margin)
                    }
                    function reset() {
                        releaseInaccuracyTimer.stop()
                        alternativeKeys.close()
                        setActiveKey(undefined)
                        if (dragSymbolMode) {
                            keyboard.symbolMode = false
                            dragSymbolMode = false
                        }
                    }

                    onPressed: {
                        releaseInaccuracyTimer.start()
                        initialKey = keyOnMouse(mouseX, mouseY)
                        setActiveKey(initialKey)
                        press(initialKey)
                    }
                    onPositionChanged: {
                        if (alternativeKeys.active) {
                            alternativeKeys.move(mapToItem(alternativeKeys, mouseX, 0).x)
                        } else {
                            var key
                            if (releaseInaccuracyTimer.running) {
                                if (hitInitialKey(mouseX, mouseY, releaseMargin)) {
                                    key = initialKey
                                } else if (initialKey) {
                                    releaseInaccuracyTimer.stop()
                                    initialKey = undefined
                                }
                            }
                            if (key === undefined) {
                                key = keyOnMouse(mouseX, mouseY)
                            }
                            if (key !== keyboard.activeKey) {
                                InputContext.inputEngine.virtualKeyCancel()
                                setActiveKey(key)
                                press(key)
                            }
                        }
                    }
                    onPressAndHold: {
                        if (keyboard.activeKey && keyboard.activeKey === initialKey) {
                            var origin = keyboard.mapFromItem(activeKey, activeKey.width / 2, 0)
                            if (alternativeKeys.open(keyboard.activeKey, origin.x, origin.y)) {
                                InputContext.inputEngine.virtualKeyCancel()
                            } else if (keyboard.activeKey.key === Qt.Key_Context1) {
                                InputContext.inputEngine.virtualKeyCancel()
                                dragSymbolMode = true
                                keyboard.symbolMode = true
                            }
                        }
                    }
                    onClicked: {}
                    onReleased: {
                        if (alternativeKeys.active) {
                            alternativeKeys.clicked()
                        } else {
                            release(keyboard.activeKey)
                        }
                        reset()
                    }
                    onCanceled: reset()
                }
            }
        }
    }
    Connections {
        target: InputContext
        onInputMethodHintsChanged: updateInputMethod()
    }
    function updateInputMethod() {
        var inputMethod = keyboard.defaultInputMethod
        var inputMode = keyboard.defaultInputMode
        if (keyboardLayoutLoader.item) {
            if (keyboardLayoutLoader.item.inputMethod) {
                inputMethod = keyboardLayoutLoader.item.inputMethod
            }
            if (keyboardLayoutLoader.item.inputMode) {
                inputMode = keyboardLayoutLoader.item.inputMode
            }
        }
        if (InputContext.inputMethodHints & (Qt.ImhHiddenText | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText)) {
            inputMethod = keyboard.plainInputMethod
        }
        if (inputMethod !== undefined) {
            InputContext.inputEngine.inputMethod = inputMethod
            InputContext.inputEngine.inputMode = inputMode
        }
    }
}
