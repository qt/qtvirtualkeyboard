// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Styles

KeyboardStyle {
    id: currentStyle
    readonly property bool compactSelectionList: [InputEngine.InputMode.Pinyin, InputEngine.InputMode.Cangjie, InputEngine.InputMode.Zhuyin].indexOf(InputContext.inputEngine.inputMode) !== -1
    readonly property string fontFamily: "Courier"
    readonly property real keyBackgroundMargin: Math.round(9 * scaleHint)
    readonly property real keyContentMargin: Math.round(30 * scaleHint)
    readonly property real keyIconScale: scaleHint * 0.6
    readonly property string resourcePath: "qt-project.org/imports/QtQuick/VirtualKeyboard/Styles/Builtin/retro/"
    readonly property string resourcePrefix: "qrc:/" + resourcePath

    readonly property string inputLocale: InputContext.locale
    property real inputLocaleIndicatorOpacity: 1.0
    property Timer inputLocaleIndicatorHighlightTimer: Timer {
        interval: 1000
        onTriggered: inputLocaleIndicatorOpacity = 0.8
    }
    onInputLocaleChanged: {
        inputLocaleIndicatorOpacity = 1.0
        inputLocaleIndicatorHighlightTimer.restart()
    }

    keyboardDesignWidth: 2560
    keyboardDesignHeight: 800
    keyboardRelativeLeftMargin: 114 / keyboardDesignWidth
    keyboardRelativeRightMargin: 114 / keyboardDesignWidth
    keyboardRelativeTopMargin: 9 / keyboardDesignHeight
    keyboardRelativeBottomMargin: 88 / keyboardDesignHeight

    keyboardBackground: Rectangle {
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#272727" }
            GradientStop { position: 1.0; color: "black" }
        }
    }

    keyPanel: KeyPanel {
        id: keyPanel
        Image {
            id: keyBackground
            source: resourcePrefix + "images/key154px_colorA.png"
            fillMode: Image.PreserveAspectFit
            anchors.fill: keyPanel
            anchors.margins: keyBackgroundMargin
            states: [
                State {
                    name: "key154px_colorB"
                    when: ['q', 'r', 'y', 'p', 's', 'd', 'j', 'l', 'v', 'b', '\'',
                        '1', '4', '6', '0', '#', '%', '+', ')', '>',
                        '~', '·', '÷', '}', '€', '£', '§', ']', '«', '»'].indexOf(control.displayText.toLowerCase()) >= 0
                    PropertyChanges {
                        target: keyBackground
                        source: resourcePrefix + "images/key154px_colorB.png"
                    }
                },
                State {
                    name: "key154px_black"
                    when: control.highlighted
                    PropertyChanges {
                        target: keyBackground
                        source: resourcePrefix + "images/key154px_black.png"
                    }
                }
            ]
        }
        Text {
            id: keyText
            text: control.displayText
            color: "#110b05"
            anchors.fill: keyPanel
            anchors.margins: keyContentMargin
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font {
                family: fontFamily
                weight: Font.Bold
                pixelSize: 82 * scaleHint
                capitalization: control.uppercased ? Font.AllUppercase : Font.MixedCase
            }
            states: [
                State {
                    name: "fontB"
                    when: control.highlighted
                    PropertyChanges {
                        target: keyText
                        color: "#c5a96f"
                        font.pixelSize: 74 * scaleHint
                        font.letterSpacing: -5 * scaleHint
                    }
                }
            ]
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: keyBackground
                    opacity: 0.70
                }
                PropertyChanges {
                    target: keyText
                    opacity: 0.75
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: keyBackground
                    opacity: 0.30
                }
                PropertyChanges {
                    target: keyText
                    opacity: 0.50
                }
            }
        ]
    }

    backspaceKeyPanel: KeyPanel {
        id: backspaceKeyPanel
        BorderImage {
            id: backspaceKeyBackground
            source: resourcePrefix + "images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: backspaceKeyPanel
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
        }
        Image {
            id: backspaceKeyIcon
            anchors.centerIn: backspaceKeyPanel
            sourceSize.width: 159 * keyIconScale
            sourceSize.height: 88 * keyIconScale
            smooth: false
            source: resourcePrefix + "images/backspace-c5a96f.svg"
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: backspaceKeyBackground
                    opacity: 0.70
                }
                PropertyChanges {
                    target: backspaceKeyIcon
                    opacity: 0.70
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: backspaceKeyBackground
                    opacity: 0.20
                }
                PropertyChanges {
                    target: backspaceKeyIcon
                    opacity: 0.20
                }
            }
        ]
    }

    languageKeyPanel: KeyPanel {
        id: languageKeyPanel
        Image {
            id: languageKeyBackground
            source: resourcePrefix + "images/key154px_colorB.png"
            fillMode: Image.PreserveAspectFit
            anchors.fill: languageKeyPanel
            anchors.margins: keyBackgroundMargin
        }
        Image {
            id: languageKeyIcon
            anchors.centerIn: languageKeyPanel
            sourceSize.width: 127 * keyIconScale
            sourceSize.height: 127 * keyIconScale
            smooth: false
            source: resourcePrefix + "images/globe-110b05.svg"
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: languageKeyBackground
                    opacity: 0.70
                }
                PropertyChanges {
                    target: languageKeyIcon
                    opacity: 0.30
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: languageKeyBackground
                    opacity: 0.75
                }
                PropertyChanges {
                    target: languageKeyIcon
                    opacity: 0.50
                }
            }
        ]
    }

    enterKeyPanel: KeyPanel {
        id: enterKeyPanel
        BorderImage {
            id: enterKeyBackground
            source: resourcePrefix + "images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: enterKeyPanel
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
        }
        Image {
            id: enterKeyIcon
            visible: enterKeyText.text.length === 0
            anchors.centerIn: enterKeyPanel
            readonly property size enterKeyIconSize: {
                switch (control.actionId) {
                case EnterKeyAction.Go:
                case EnterKeyAction.Send:
                case EnterKeyAction.Next:
                case EnterKeyAction.Done:
                    return Qt.size(170, 119)
                case EnterKeyAction.Search:
                    return Qt.size(148, 148)
                default:
                    return Qt.size(211, 80)
                }
            }
            sourceSize.width: enterKeyIconSize.width * keyIconScale
            sourceSize.height: enterKeyIconSize.height * keyIconScale
            smooth: false
            source: {
                switch (control.actionId) {
                case EnterKeyAction.Go:
                case EnterKeyAction.Send:
                case EnterKeyAction.Next:
                case EnterKeyAction.Done:
                    return resourcePrefix + "images/check-c5a96f.svg"
                case EnterKeyAction.Search:
                    return resourcePrefix + "images/search-c5a96f.svg"
                default:
                    return resourcePrefix + "images/enter-c5a96f.svg"
                }
            }
        }
        Text {
            id: enterKeyText
            visible: text.length !== 0
            text: control.actionId !== EnterKeyAction.None ? control.displayText : ""
            clip: true
            fontSizeMode: Text.HorizontalFit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: enterKeyPanel
            anchors.leftMargin: keyContentMargin
            anchors.topMargin: Math.round(50 * scaleHint)
            anchors.rightMargin: keyContentMargin
            anchors.bottomMargin: Math.round(30 * scaleHint)
            color: "#c5a96f"
            font {
                family: fontFamily
                weight: Font.Bold
                pixelSize: 74 * scaleHint
                capitalization: Font.AllUppercase
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: enterKeyBackground
                    opacity: 0.70
                }
                PropertyChanges {
                    target: enterKeyIcon
                    opacity: 0.70
                }
                PropertyChanges {
                    target: enterKeyText
                    opacity: 0.70
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: enterKeyBackground
                    opacity: 0.20
                }
                PropertyChanges {
                    target: enterKeyIcon
                    opacity: 0.20
                }
                PropertyChanges {
                    target: enterKeyText
                    opacity: 0.20
                }
            }
        ]
    }

    hideKeyPanel: KeyPanel {
        id: hideKeyPanel
        BorderImage {
            id: hideKeyBackground
            source: resourcePrefix + "images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: hideKeyPanel
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
        }
        Image {
            id: hideKeyIcon
            anchors.centerIn: hideKeyPanel
            sourceSize.width: 127 * keyIconScale
            sourceSize.height: 127 * keyIconScale
            smooth: false
            source: resourcePrefix + "images/hidekeyboard-c5a96f.svg"
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: hideKeyBackground
                    opacity: 0.70
                }
                PropertyChanges {
                    target: hideKeyIcon
                    opacity: 0.70
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: hideKeyBackground
                    opacity: 0.20
                }
                PropertyChanges {
                    target: hideKeyIcon
                    opacity: 0.20
                }
            }
        ]
    }

    shiftKeyPanel: KeyPanel {
        id: shiftKeyPanel
        BorderImage {
            id: shiftKeyBackground
            source: resourcePrefix + "images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: shiftKeyPanel
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
            states: [
                State {
                    name: "capsLockActive"
                    when: InputContext.capsLockActive
                    PropertyChanges {
                        target: shiftKeyBackground
                        source: resourcePrefix + "images/key154px_capslock.png"
                    }
                    PropertyChanges {
                        target: shiftKeyIcon
                        source: resourcePrefix + "images/shift-cd8865.svg"
                    }
                },
                State {
                    name: "shiftActive"
                    when: InputContext.shiftActive
                    PropertyChanges {
                        target: shiftKeyBackground
                        source: resourcePrefix + "images/key154px_shiftcase.png"
                    }
                    PropertyChanges {
                        target: shiftKeyIcon
                        source: resourcePrefix + "images/shift-dc4f28.svg"
                    }
                }
            ]
        }
        Image {
            id: shiftKeyIcon
            anchors.centerIn: shiftKeyPanel
            sourceSize.width: 144 * keyIconScale
            sourceSize.height: 134 * keyIconScale
            smooth: false
            source: resourcePrefix + "images/shift-c5a96f.svg"
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: shiftKeyBackground
                    opacity: 0.70
                }
                PropertyChanges {
                    target: shiftKeyIcon
                    opacity: 0.70
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: shiftKeyBackground
                    opacity: 0.20
                }
                PropertyChanges {
                    target: shiftKeyIcon
                    opacity: 0.20
                }
            }
        ]
    }

    spaceKeyPanel: KeyPanel {
        id: spaceKeyPanel
        BorderImage {
            id: spaceKeyBackground
            source: resourcePrefix + "images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: spaceKeyPanel
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
        }
        Text {
            id: spaceKeyText
            text: Qt.locale(InputContext.locale).nativeLanguageName
            color: "#c5a96f"
            opacity: inputLocaleIndicatorOpacity
            Behavior on opacity { PropertyAnimation { duration: 250 } }
            anchors.centerIn: spaceKeyPanel
            font {
                family: fontFamily
                weight: Font.Bold
                pixelSize: 72 * scaleHint
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: spaceKeyBackground
                    opacity: 0.70
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: spaceKeyBackground
                    opacity: 0.30
                }
            }
        ]
    }

    symbolKeyPanel: KeyPanel {
        id: symbolKeyPanel
        BorderImage {
            id: symbolKeyBackground
            source: resourcePrefix + "images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: symbolKeyPanel
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
        }
        Text {
            id: symbolKeyText
            text: control.displayText
            color: "#c5a96f"
            anchors.centerIn: symbolKeyPanel
            font {
                family: fontFamily
                weight: Font.DemiBold
                pixelSize: 74 * scaleHint
                letterSpacing: -5 * scaleHint
                capitalization: Font.AllUppercase
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: symbolKeyBackground
                    opacity: 0.70
                }
                PropertyChanges {
                    target: symbolKeyText
                    opacity: 0.70
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: symbolKeyBackground
                    opacity: 0.20
                }
                PropertyChanges {
                    target: symbolKeyText
                    opacity: 0.20
                }
            }
        ]
    }

    modeKeyPanel: KeyPanel {
        id: modeKeyPanel
        BorderImage {
            id: modeKeyBackground
            source: resourcePrefix + "images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: modeKeyPanel
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
            states: [
                State {
                    name: "mode"
                    when: control.mode
                    PropertyChanges {
                        target: modeKeyBackground
                        source: resourcePrefix + "images/key154px_capslock.png"
                    }
                }
            ]
        }
        Text {
            id: modeKeyText
            text: control.displayText
            color: "#c5a96f"
            anchors.fill: modeKeyPanel
            anchors.margins: keyContentMargin
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font {
                family: fontFamily
                weight: Font.DemiBold
                pixelSize: 74 * scaleHint
                letterSpacing: -5 * scaleHint
                capitalization: Font.AllUppercase
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: modeKeyBackground
                    opacity: 0.70
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: modeKeyBackground
                    opacity: 0.20
                }
            }
        ]
    }

    handwritingKeyPanel: KeyPanel {
        id: handwritingKeyPanel
        BorderImage {
            id: hwrKeyBackground
            source: resourcePrefix + "images/key154px_black.png"
            width: (parent.width - 2 * hwrKeyBackground) / scale
            height: sourceSize.height
            anchors.centerIn: handwritingKeyPanel
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
        }
        Image {
            id: hwrKeyIcon
            anchors.centerIn: handwritingKeyPanel
            sourceSize.width: 127 * keyIconScale
            sourceSize.height: 127 * keyIconScale
            smooth: false
            source: resourcePrefix + (keyboard.handwritingMode ? "images/textmode-c5a96f.svg" : "images/handwriting-c5a96f.svg")
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: hwrKeyBackground
                    opacity: 0.70
                }
                PropertyChanges {
                    target: hwrKeyIcon
                    opacity: 0.70
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: hwrKeyBackground
                    opacity: 0.20
                }
                PropertyChanges {
                    target: hwrKeyIcon
                    opacity: 0.20
                }
            }
        ]
    }

    characterPreviewMargin: Math.round(20 * scaleHint)
    characterPreviewDelegate: Item {
        property string text
        id: characterPreview
        Image {
            id: characterPreviewBackground
            source: resourcePrefix + "images/key_preview.png"
            fillMode: Image.PreserveAspectFit
            anchors.fill: parent
        }
        Text {
            id: characterPreviewText
            color: "#c5a96f"
            text: characterPreview.text
            anchors.centerIn: characterPreviewBackground
            font {
                family: fontFamily
                weight: Font.Bold
                pixelSize: 85 * scaleHint
            }
            states: [
                State {
                    name: "fit"
                    when: text.length > 1
                    PropertyChanges {
                        target: characterPreviewText
                        font.letterSpacing: -5 * scaleHint
                    }
                }
            ]
        }
    }

    alternateKeysListItemWidth: Math.round(111 * scaleHint)
    alternateKeysListItemHeight: Math.round(154 * scaleHint)
    alternateKeysListBottomMargin: Math.round(15 * scaleHint)
    alternateKeysListLeftMargin: Math.round(79 * scaleHint)
    alternateKeysListRightMargin: Math.round(79 * scaleHint)
    alternateKeysListDelegate: Item {
        id: alternateKeysListItem
        width: alternateKeysListItemWidth
        height: alternateKeysListItemHeight
        Text {
            id: listItemText
            text: model.text
            color: "#868482"
            font {
                family: fontFamily
                weight: Font.DemiBold
                pixelSize: 52 * scaleHint
                letterSpacing: -6 * scaleHint
            }
            anchors.centerIn: parent
        }
        states: State {
            name: "current"
            when: alternateKeysListItem.ListView.isCurrentItem
            PropertyChanges {
                target: listItemText
                color: "white"
            }
        }
    }
    alternateKeysListHighlight: Item {
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: Math.round(8 * scaleHint)
            anchors.bottomMargin: Math.round(8 * scaleHint)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#64462a" }
                GradientStop { position: 0.18; color: "#a37648" }
                GradientStop { position: 0.5; color: "#c4a47c" }
                GradientStop { position: 0.82; color: "#a37648" }
                GradientStop { position: 1.0; color: "#64462a" }
            }
        }
    }
    alternateKeysListBackground: Item {
        property real currentItemOffset
        property bool currentItemHighlight: false
        BorderImage {
            cache: false
            source: resourcePrefix + "images/key160px_black.png"
            width: sourceSize.width + parent.width / scale
            height: sourceSize.height
            anchors.centerIn: parent
            border.left: 79
            border.top: 79
            border.right: 79
            border.bottom: 79
            horizontalTileMode: BorderImage.Stretch
            scale: parent.height / sourceSize.height
        }
        Image {
            visible: currentItemOffset !== undefined
            source: currentItemHighlight ? resourcePrefix + "images/triangle_highlight.png" : resourcePrefix + "images/triangle_black.png"
            fillMode: Image.PreserveAspectFit
            width: sourceSize.width * scaleHint
            height: sourceSize.height * scaleHint
            anchors.top: parent.bottom
            anchors.topMargin: Math.round(-8 * scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(currentItemOffset - width / 2)
        }
    }

    selectionListHeight: 85 * scaleHint
    selectionListDelegate: SelectionListItem {
        id: selectionListItem
        width: Math.round(selectionListLabel.width + selectionListLabel.anchors.leftMargin * 2)
        Text {
            id: selectionListLabel
            anchors.left: parent.left
            anchors.leftMargin: Math.round((compactSelectionList ? 50 : 140) * scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            text: decorateText(display, wordCompletionLength)
            color: "white"
            font {
                family: fontFamily
                weight: Font.Bold
                pixelSize: 44 * scaleHint
            }
            function decorateText(text, wordCompletionLength) {
                if (wordCompletionLength > 0) {
                    return text.slice(0, -wordCompletionLength) + '<u>' + text.slice(-wordCompletionLength) + '</u>'
                }
                return text
            }
        }
        Rectangle {
            id: selectionListSeparator
            width: 4 * scaleHint
            height: 36 * scaleHint
            color: "#35322f"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.left
        }
        states: State {
            name: "current"
            when: selectionListItem.ListView.isCurrentItem
            PropertyChanges {
                target: selectionListLabel
                color: "#c5a96f"
            }
        }
    }
    selectionListBackground: Rectangle {
        color: "#222222"
    }
    selectionListAdd: Transition {
        NumberAnimation { property: "y"; from: wordCandidateView.height; duration: 200 }
        NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 200 }
    }
    selectionListRemove: Transition {
        NumberAnimation { property: "y"; to: -wordCandidateView.height; duration: 200 }
        NumberAnimation { property: "opacity"; to: 0; duration: 200 }
    }

    navigationHighlight: Rectangle {
        color: "transparent"
        border.color: "yellow"
        border.width: 5
    }

    traceInputKeyPanelDelegate: TraceInputKeyPanel {
        traceMargins: keyBackgroundMargin
        BorderImage {
            id: traceInputKeyPanelBackground
            readonly property int traceInputKeyPanelSvgImageHeight: Math.round(height / 12)
            readonly property real traceInputKeyPanelSvgImageScale: traceInputKeyPanelSvgImageHeight / 154
            source: "image://qtvkbsvg/%1/images/key154px_colorA.svg?height=%2".arg(resourcePath).arg(traceInputKeyPanelSvgImageHeight)
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
            border.left: 76 * traceInputKeyPanelSvgImageScale
            border.top: 76 * traceInputKeyPanelSvgImageScale
            border.right: 78 * traceInputKeyPanelSvgImageScale
            border.bottom: 78 * traceInputKeyPanelSvgImageScale
            horizontalTileMode: BorderImage.Stretch
            verticalTileMode: BorderImage.Stretch
        }
        Text {
            id: hwrInputModeIndicator
            visible: control.patternRecognitionMode === InputEngine.PatternRecognitionMode.Handwriting
            text: {
                switch (InputContext.inputEngine.inputMode) {
                case InputEngine.InputMode.Numeric:
                    if (["ar", "fa"].indexOf(InputContext.locale.substring(0, 2)) !== -1)
                        return "\u0660\u0661\u0662"
                    // Fallthrough
                case InputEngine.InputMode.Dialable:
                    return "123"
                case InputEngine.InputMode.Greek:
                    return "ΑΒΓ"
                case InputEngine.InputMode.Cyrillic:
                    return "АБВ"
                case InputEngine.InputMode.Arabic:
                    if (InputContext.locale.substring(0, 2) === "fa")
                        return "\u0627\u200C\u0628\u200C\u067E"
                    return "\u0623\u200C\u0628\u200C\u062C"
                case InputEngine.InputMode.Hebrew:
                    return "\u05D0\u05D1\u05D2"
                case InputEngine.InputMode.ChineseHandwriting:
                    return "中文"
                case InputEngine.InputMode.JapaneseHandwriting:
                    return "日本語"
                case InputEngine.InputMode.KoreanHandwriting:
                    return "한국어"
                case InputEngine.InputMode.Thai:
                    return "กขค"
                default:
                    return "Abc"
                }
            }
            color: "black"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: keyContentMargin * 1.5
            font {
                family: fontFamily
                weight: Font.Bold
                pixelSize: 72 * scaleHint
                capitalization: {
                    if (InputContext.capsLockActive)
                        return Font.AllUppercase
                    if (InputContext.shiftActive)
                        return Font.MixedCase
                    return Font.AllLowercase
                }
            }
        }
        Canvas {
            id: traceInputKeyGuideLines
            anchors.fill: traceInputKeyPanelBackground
            opacity: 0.4
            onPaint: {
                var ctx = getContext("2d")
                ctx.lineWidth = 1
                ctx.strokeStyle = Qt.rgba(0, 0, 0)
                ctx.clearRect(0, 0, width, height)
                var i
                var margin = Math.round(30 * scaleHint)
                if (control.horizontalRulers) {
                    for (i = 0; i < control.horizontalRulers.length; i++) {
                        ctx.beginPath()
                        var y = Math.round(control.horizontalRulers[i])
                        var rightMargin = Math.round(width - margin)
                        if (i + 1 === control.horizontalRulers.length) {
                            ctx.moveTo(margin, y)
                            ctx.lineTo(rightMargin, y)
                        } else {
                            var dashLen = Math.round(20 * scaleHint)
                            for (var dash = margin, dashCount = 0;
                                 dash < rightMargin; dash += dashLen, dashCount++) {
                                if ((dashCount & 1) === 0) {
                                    ctx.moveTo(dash, y)
                                    ctx.lineTo(Math.min(dash + dashLen, rightMargin), y)
                                }
                            }
                        }
                        ctx.stroke()
                    }
                }
                if (control.verticalRulers) {
                    for (i = 0; i < control.verticalRulers.length; i++) {
                        ctx.beginPath()
                        ctx.moveTo(control.verticalRulers[i], 0)
                        ctx.lineTo(control.verticalRulers[i], height)
                        ctx.stroke()
                    }
                }
            }
            Connections {
                target: control
                function onHorizontalRulersChanged() { traceInputKeyGuideLines.requestPaint() }
                function onVerticalRulersChanged() { traceInputKeyGuideLines.requestPaint() }
            }
        }
    }

    traceCanvasDelegate: TraceCanvas {
        id: traceCanvas
        onAvailableChanged: {
            if (!available)
                return
            var ctx = getContext("2d")
            ctx.lineWidth = parent.canvasType === "fullscreen" ? 10 : 10 * scaleHint
            ctx.lineCap = "round"
            ctx.strokeStyle = Qt.rgba(0, 0, 0)
            ctx.fillStyle = ctx.strokeStyle
        }
        autoDestroyDelay: 800
        onTraceChanged: if (trace === null) opacity = 0
        Behavior on opacity { PropertyAnimation { easing.type: Easing.OutCubic; duration: 150 } }
    }

    popupListDelegate: SelectionListItem {
        property real cursorAnchor: popupListLabel.x + popupListLabel.width
        id: popupListItem
        width: popupListLabel.width + popupListLabel.anchors.leftMargin * 2
        height: popupListLabel.height + popupListLabel.anchors.topMargin * 2
        Text {
            id: popupListLabel
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: popupListLabel.height / 2
            anchors.topMargin: popupListLabel.height / 3
            text: decorateText(display, wordCompletionLength)
            color: "#110b05"
            font {
                family: fontFamily
                weight: Font.Normal
                pixelSize: Qt.inputMethod.cursorRectangle.height * 0.8
            }
            function decorateText(text, wordCompletionLength) {
                if (wordCompletionLength > 0) {
                    return text.slice(0, -wordCompletionLength) + '<u>' + text.slice(-wordCompletionLength) + '</u>'
                }
                return text
            }
        }
        states: State {
            name: "current"
            when: popupListItem.ListView.isCurrentItem
            PropertyChanges {
                target: popupListLabel
                color: "black"
            }
        }
    }

    popupListBackground: Item {
        BorderImage {
            readonly property int popupListBackgroundSvgImageHeight: Math.round(height / 8)
            readonly property real popupListBackgroundSvgImageScale: popupListBackgroundSvgImageHeight / 154
            readonly property real backgroundMargin: 0 * scaleHint
            x: -backgroundMargin
            y: -backgroundMargin
            width: parent.width + 2 * backgroundMargin
            height: parent.height + 2 * backgroundMargin
            source: "image://qtvkbsvg/%1/images/key154px_colorA.svg?height=%2".arg(resourcePath).arg(popupListBackgroundSvgImageHeight)
            border.left: 76 * popupListBackgroundSvgImageScale
            border.top: 76 * popupListBackgroundSvgImageScale
            border.right: 76 * popupListBackgroundSvgImageScale
            border.bottom: 76 * popupListBackgroundSvgImageScale
            horizontalTileMode: BorderImage.Stretch
            verticalTileMode: BorderImage.Stretch
        }
    }

    popupListAdd: Transition {
        NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 200 }
    }

    popupListRemove: Transition {
        NumberAnimation { property: "opacity"; to: 0; duration: 200 }
    }

    languagePopupListEnabled: true

    languageListDelegate: SelectionListItem {
        id: languageListItem
        width: languageNameTextMetrics.width * 20
        height: languageNameTextMetrics.height + languageListLabel.anchors.topMargin + languageListLabel.anchors.bottomMargin
        Text {
            id: languageListLabel
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: languageNameTextMetrics.height / 2
            anchors.rightMargin: anchors.leftMargin
            anchors.topMargin: languageNameTextMetrics.height / 3
            anchors.bottomMargin: anchors.topMargin
            text: languageNameFormatter.elidedText
            color: "#c5a96f"
            opacity: 0.8
            font {
                family: fontFamily
                weight: Font.Normal
                pixelSize: 44 * scaleHint
            }
        }
        TextMetrics {
            id: languageNameTextMetrics
            font {
                family: fontFamily
                weight: Font.Normal
                pixelSize: 44 * scaleHint
            }
            text: "X"
        }
        TextMetrics {
            id: languageNameFormatter
            font {
                family: fontFamily
                weight: Font.Normal
                pixelSize: 44 * scaleHint
            }
            elide: Text.ElideRight
            elideWidth: languageListItem.width - languageListLabel.anchors.leftMargin - languageListLabel.anchors.rightMargin
            text: displayName
        }
        states: State {
            name: "current"
            when: languageListItem.ListView.isCurrentItem
            PropertyChanges {
                target: languageListLabel
                color: "white"
            }
        }
    }

    languageListHighlight: Item {
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: Math.round(8 * scaleHint)
            anchors.bottomMargin: Math.round(8 * scaleHint)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#64462a" }
                GradientStop { position: 0.18; color: "#a37648" }
                GradientStop { position: 0.5; color: "#c4a47c" }
                GradientStop { position: 0.82; color: "#a37648" }
                GradientStop { position: 1.0; color: "#64462a" }
            }
        }
    }

    languageListBackground: Item {
        BorderImage {
            readonly property int languageListBackgroundSvgImageHeight: Math.round(height / 3)
            readonly property real languageListBackgroundSvgImageScale: languageListBackgroundSvgImageHeight / 154
            readonly property real backgroundMargin: 40 * scaleHint
            x: -backgroundMargin
            y: -backgroundMargin
            width: parent.width + 2 * backgroundMargin
            height: parent.height + 2 * backgroundMargin
            source: "image://qtvkbsvg/%1/images/key154px_black.svg?height=%2".arg(resourcePath).arg(languageListBackgroundSvgImageHeight)
            border.left: 76 * languageListBackgroundSvgImageScale
            border.top: 76 * languageListBackgroundSvgImageScale
            border.right: 78 * languageListBackgroundSvgImageScale
            border.bottom: 78 * languageListBackgroundSvgImageScale
            horizontalTileMode: BorderImage.Stretch
            verticalTileMode: BorderImage.Stretch
        }
    }

    languageListAdd: Transition {
        NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 200 }
    }

    languageListRemove: Transition {
        NumberAnimation { property: "opacity"; to: 0; duration: 200 }
    }

    selectionHandle: Image {
        sourceSize.width: 20
        source: resourcePrefix + "images/selectionhandle-bottom.svg"
    }

    fullScreenInputContainerBackground: Rectangle {
        color: "#FFF"
    }

    fullScreenInputBackground: Rectangle {
        color: "#FFF"
    }

    fullScreenInputMargins: Math.round(15 * scaleHint)

    fullScreenInputPadding: Math.round(30 * scaleHint)

    fullScreenInputCursor: Rectangle {
        width: 1
        color: "#000"
        visible: parent.blinkStatus
    }

    fullScreenInputFont.pixelSize: 58 * scaleHint

    fullScreenInputPasswordCharacter: "*"

    fullScreenInputSelectionColor: "#B57C47"

    functionPopupListDelegate: Item {
        id: functionPopupListItem
        readonly property real iconMargin: 40 * scaleHint
        readonly property real iconWidth: 144 * keyIconScale
        readonly property real iconHeight: 144 * keyIconScale
        width: iconWidth + 2 * iconMargin
        height: iconHeight + 2 * iconMargin
        Image {
            id: functionIcon
            anchors.centerIn: parent
            sourceSize.width: iconWidth
            sourceSize.height: iconHeight
            smooth: false
            source: {
                switch (keyboardFunction) {
                case QtVirtualKeyboard.KeyboardFunction.HideInputPanel:
                    return resourcePrefix + "images/hidekeyboard-c5a96f.svg"
                case QtVirtualKeyboard.KeyboardFunction.ChangeLanguage:
                    return resourcePrefix + "images/globe-c5a96f.svg"
                case QtVirtualKeyboard.KeyboardFunction.ToggleHandwritingMode:
                    return resourcePrefix + (keyboard.handwritingMode ? "images/textmode-c5a96f.svg" : "images/handwriting-c5a96f.svg")
                }
            }
            states: State {
                when: functionPopupListItem.ListView.isCurrentItem
                PropertyChanges {
                    target: functionIcon
                    source: {
                        switch (keyboardFunction) {
                        case QtVirtualKeyboard.KeyboardFunction.HideInputPanel:
                            return resourcePrefix + "images/hidekeyboard-fff.svg"
                        case QtVirtualKeyboard.KeyboardFunction.ChangeLanguage:
                            return resourcePrefix + "images/globe-fff.svg"
                        case QtVirtualKeyboard.KeyboardFunction.ToggleHandwritingMode:
                            return resourcePrefix + (keyboard.handwritingMode ? "images/textmode-fff.svg" : "images/handwriting-fff.svg")
                        }
                    }
                }
            }
        }
    }

    functionPopupListBackground: Item {
        property ListView view
        property real currentItemOffset: {
            if (view.count > 0) {
                var highlightItem = view.itemAtIndex(0)
                return view.mapFromItem(highlightItem, highlightItem.width / 2, 0).x
            }
            return 0
        }
        property bool currentItemHighlight: view.currentIndex === 0
        BorderImage {
            cache: false
            source: resourcePrefix + "images/key160px_black.png"
            width: sourceSize.width + parent.width / scale
            height: sourceSize.height
            anchors.centerIn: parent
            border.left: 79
            border.top: 79
            border.right: 79
            border.bottom: 79
            horizontalTileMode: BorderImage.Stretch
            scale: parent.height / sourceSize.height
        }
        Image {
            visible: currentItemOffset !== undefined
            source: currentItemHighlight ? resourcePrefix + "images/triangle_highlight.png" : resourcePrefix + "images/triangle_black.png"
            fillMode: Image.PreserveAspectFit
            width: sourceSize.width * scaleHint
            height: sourceSize.height * scaleHint
            anchors.top: parent.bottom
            anchors.topMargin: Math.round(-8 * scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(currentItemOffset - width / 2)
        }
    }

    functionPopupListHighlight: Item {
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: Math.round(8 * scaleHint)
            anchors.bottomMargin: Math.round(8 * scaleHint)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#64462a" }
                GradientStop { position: 0.18; color: "#a37648" }
                GradientStop { position: 0.5; color: "#c4a47c" }
                GradientStop { position: 0.82; color: "#a37648" }
                GradientStop { position: 1.0; color: "#64462a" }
            }
        }
    }
}
