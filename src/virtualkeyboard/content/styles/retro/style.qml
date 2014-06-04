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
import QtQuick.Enterprise.VirtualKeyboard 1.0
import QtQuick.Enterprise.VirtualKeyboard.Styles 1.0

KeyboardStyle {
    readonly property bool pinyinMode: InputContext.inputEngine.inputMode === InputEngine.Pinyin
    readonly property string fontFamily: "Courier"
    readonly property real keyBackgroundMargin: Math.round(9 * scaleHint)
    readonly property real keyContentMargin: Math.round(50 * scaleHint)
    readonly property real keyIconMargin: Math.round(40 * scaleHint)

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
        soundEffect: "qrc:/sounds/key.wav"
        Image {
            id: keyBackground
            source: "qrc:/images/key154px_colorA.png"
            fillMode: Image.PreserveAspectFit
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
            states: [
                State {
                    name: "key154px_colorB"
                    when: ['q', 'r', 'y', 'p', 's', 'd', 'j', 'l', 'v', 'b', '\'',
                        '1', '4', '6', '0', '#', '%', '+', ')', '>',
                        '~', '·', '÷', '}', '€', '£', '§', ']', '«', '»'].indexOf(control.displayText.toLowerCase()) >= 0
                    PropertyChanges {
                        target: keyBackground
                        source: "qrc:/images/key154px_colorB.png"
                    }
                },
                State {
                    name: "key154px_black"
                    when: control.displayText.length > 2
                    PropertyChanges {
                        target: keyBackground
                        source: "qrc:/images/key154px_black.png"
                    }
                }
            ]
        }
        Text {
            id: keyText
            text: control.displayText
            color: "#110b05"
            anchors.centerIn: parent
            font {
                family: fontFamily
                weight: Font.Bold
                pixelSize: 82 * scaleHint
                capitalization: control.uppercased ? Font.AllUppercase : Font.MixedCase
            }
            states: [
                State {
                    name: "fontB"
                    when: control.displayText.length > 2
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
        soundEffect: "qrc:/sounds/backspace.wav"
        BorderImage {
            id: backspaceKeyBackground
            source: "qrc:/images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: parent
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
        }
        KeyIcon {
            id: backspaceKeyIcon
            source: "qrc:/images/backspace.png"
            color: "#c5a96f"
            anchors.fill: parent
            anchors.topMargin: keyIconMargin
            anchors.bottomMargin: keyIconMargin
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
        soundEffect: "qrc:/sounds/space.wav"
        Image {
            id: languageKeyBackground
            source: "qrc:/images/key154px_colorB.png"
            fillMode: Image.PreserveAspectFit
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
        }
        KeyIcon {
            id: languageKeyIcon
            source: "qrc:/images/globe.png"
            color: "#110b05"
            anchors.fill: parent
            anchors.topMargin: keyIconMargin
            anchors.bottomMargin: keyIconMargin
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
        soundEffect: "qrc:/sounds/return.wav"
        BorderImage {
            id: enterKeyBackground
            source: "qrc:/images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: parent
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
        }
        KeyIcon {
            id: enterKeyIcon
            visible: enterKeyText.text.length === 0
            source: {
                switch (control.actionId) {
                case EnterKeyAction.Go:
                case EnterKeyAction.Send:
                case EnterKeyAction.Next:
                case EnterKeyAction.Done:
                    return "qrc:/images/check.png"
                case EnterKeyAction.Search:
                    return "qrc:/images/search.png"
                default:
                    return "qrc:/images/enter.png"
                }
            }
            color: "#c5a96f"
            anchors.fill: parent
            anchors.topMargin: keyIconMargin
            anchors.bottomMargin: keyIconMargin
        }
        Text {
            id: enterKeyText
            visible: text.length !== 0
            text: control.actionId !== EnterKeyAction.None ? "" : control.displayText
            clip: true
            fontSizeMode: Text.HorizontalFit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
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
        soundEffect: "qrc:/sounds/space.wav"
        BorderImage {
            id: hideKeyBackground
            source: "qrc:/images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: parent
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
        }
        KeyIcon {
            id: hideKeyIcon
            source: "qrc:/images/hidekeyboard.png"
            color: "#c5a96f"
            anchors.fill: parent
            anchors.topMargin: keyIconMargin
            anchors.bottomMargin: keyIconMargin
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
        soundEffect: "qrc:/sounds/shift.wav"
        BorderImage {
            id: shiftKeyBackground
            source: "qrc:/images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: parent
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
            states: [
                State {
                    name: "capslock"
                    when: control.capsLock
                    PropertyChanges {
                        target: shiftKeyBackground
                        source: "qrc:/images/key154px_capslock.png"
                    }
                    PropertyChanges {
                        target: shiftKeyIcon
                        color: "#cd8865"
                    }
                },
                State {
                    name: "shift"
                    when: control.shift
                    PropertyChanges {
                        target: shiftKeyBackground
                        source: "qrc:/images/key154px_shiftcase.png"
                    }
                    PropertyChanges {
                        target: shiftKeyIcon
                        color: "#dc4f28"
                    }
                }
            ]
        }
        KeyIcon {
            id: shiftKeyIcon
            source: "qrc:/images/shift.png"
            color: "#c5a96f"
            anchors.fill: parent
            anchors.topMargin: keyIconMargin
            anchors.bottomMargin: keyIconMargin
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
        soundEffect: "qrc:/sounds/space.wav"
        BorderImage {
            id: spaceKeyBackground
            source: "qrc:/images/key154px_colorA.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: parent
            border.left: 76
            border.top: 76
            border.right: 76
            border.bottom: 76
            horizontalTileMode: BorderImage.Stretch
            scale: (parent.height - 2 * keyBackgroundMargin) / sourceSize.height
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
        soundEffect: "qrc:/sounds/space.wav"
        BorderImage {
            id: symbolKeyBackground
            source: "qrc:/images/key154px_black.png"
            width: (parent.width - 2 * keyBackgroundMargin) / scale
            height: sourceSize.height
            anchors.centerIn: parent
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
            anchors.centerIn: parent
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

    characterPreviewMargin: Math.round(20 * scaleHint)
    characterPreviewDelegate: Item {
        property string text
        id: characterPreview
        Image {
            id: characterPreviewBackground
            source: "qrc:/images/key_preview.png"
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
            source: "qrc:/images/key160px_black.png"
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
            source: currentItemHighlight ? "qrc:/images/triangle_highlight.png" : "qrc:/images/triangle_black.png"
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
        soundEffect: "qrc:/sounds/return.wav"
        id: selectionListItem
        width: Math.round(selectionListLabel.width + selectionListLabel.anchors.leftMargin * 2)
        Text {
            id: selectionListLabel
            anchors.left: parent.left
            anchors.leftMargin: Math.round((pinyinMode ? 50 : 140) * scaleHint)
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

    navigationHighlight: Rectangle {
        color: "transparent"
        border.color: "yellow"
        border.width: 5
    }
}
