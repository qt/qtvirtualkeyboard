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

import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 1.3
import QtQuick.Enterprise.VirtualKeyboard.Styles 1.3

KeyboardStyle {
    id: currentStyle
    readonly property bool pinyinMode: InputContext.inputEngine.inputMode === InputEngine.Pinyin
    readonly property string fontFamily: "Sans"
    readonly property real keyBackgroundMargin: Math.round(13 * scaleHint)
    readonly property real keyContentMargin: Math.round(45 * scaleHint)
    readonly property real keyIconScale: scaleHint * 0.6
    readonly property string resourcePrefix: "qrc:/content/styles/default/"

    readonly property string inputLocale: InputContext.locale
    property color inputLocaleIndicatorColor: "white"
    property Timer inputLocaleIndicatorHighlightTimer: Timer {
        interval: 1000
        onTriggered: inputLocaleIndicatorColor = "gray"
    }
    onInputLocaleChanged: {
        inputLocaleIndicatorColor = "white"
        inputLocaleIndicatorHighlightTimer.restart()
    }

    keyboardDesignWidth: 2560
    keyboardDesignHeight: 800
    keyboardRelativeLeftMargin: 114 / keyboardDesignWidth
    keyboardRelativeRightMargin: 114 / keyboardDesignWidth
    keyboardRelativeTopMargin: 13 / keyboardDesignHeight
    keyboardRelativeBottomMargin: 86 / keyboardDesignHeight

    keyboardBackground: Rectangle {
        color: "black"
    }

    keyPanel: KeyPanel {
        Rectangle {
            id: keyBackground
            radius: 5
            color: "#35322f"
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
            Text {
                id: keyText
                text: control.displayText
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                anchors.margins: keyContentMargin
                font {
                    family: fontFamily
                    weight: Font.Normal
                    pixelSize: 52 * scaleHint
                    capitalization: control.uppercased ? Font.AllUppercase : Font.MixedCase
                }
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: keyBackground
                    opacity: 0.75
                }
                PropertyChanges {
                    target: keyText
                    opacity: 0.5
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: keyBackground
                    opacity: 0.75
                }
                PropertyChanges {
                    target: keyText
                    opacity: 0.05
                }
            }
        ]
    }

    backspaceKeyPanel: KeyPanel {
        Rectangle {
            id: backspaceKeyBackground
            radius: 5
            color: "#1e1b18"
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
            Image {
                id: backspaceKeyIcon
                anchors.centerIn: parent
                scale: keyIconScale
                source: resourcePrefix + "images/backspace-868482.png"
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: backspaceKeyBackground
                    opacity: 0.80
                }
                PropertyChanges {
                    target: backspaceKeyIcon
                    opacity: 0.6
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: backspaceKeyBackground
                    opacity: 0.8
                }
                PropertyChanges {
                    target: backspaceKeyIcon
                    opacity: 0.2
                }
            }
        ]
    }

    languageKeyPanel: KeyPanel {
        Rectangle {
            id: languageKeyBackground
            radius: 5
            color: "#35322f"
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
            Image {
                id: languageKeyIcon
                anchors.centerIn: parent
                scale: keyIconScale
                source: resourcePrefix + "images/globe-868482.png"
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: languageKeyBackground
                    opacity: 0.80
                }
                PropertyChanges {
                    target: languageKeyIcon
                    opacity: 0.75
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: languageKeyBackground
                    opacity: 0.8
                }
                PropertyChanges {
                    target: languageKeyIcon
                    opacity: 0.2
                }
            }
        ]
    }

    enterKeyPanel: KeyPanel {
        Rectangle {
            id: enterKeyBackground
            radius: 5
            color: "#1e1b18"
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
            Image {
                id: enterKeyIcon
                visible: enterKeyText.text.length === 0
                anchors.centerIn: parent
                scale: keyIconScale
                source: {
                    switch (control.actionId) {
                    case EnterKeyAction.Go:
                    case EnterKeyAction.Send:
                    case EnterKeyAction.Next:
                    case EnterKeyAction.Done:
                        return resourcePrefix + "images/check-868482.png"
                    case EnterKeyAction.Search:
                        return resourcePrefix + "images/search-868482.png"
                    default:
                        return resourcePrefix + "images/enter-868482.png"
                    }
                }
            }
            Text {
                id: enterKeyText
                visible: text.length !== 0
                text: control.actionId !== EnterKeyAction.None ? "" : control.displayText
                clip: true
                fontSizeMode: Text.HorizontalFit
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "#80c342"
                font {
                    family: fontFamily
                    weight: Font.Normal
                    pixelSize: 44 * scaleHint
                    capitalization: Font.AllUppercase
                }
                anchors.fill: parent
                anchors.margins: Math.round(42 * scaleHint)
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: enterKeyBackground
                    opacity: 0.80
                }
                PropertyChanges {
                    target: enterKeyIcon
                    opacity: 0.6
                }
                PropertyChanges {
                    target: enterKeyText
                    opacity: 0.6
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: enterKeyBackground
                    opacity: 0.8
                }
                PropertyChanges {
                    target: enterKeyIcon
                    opacity: 0.2
                }
                PropertyChanges {
                    target: enterKeyText
                    opacity: 0.05
                }
            }
        ]
    }

    hideKeyPanel: KeyPanel {
        Rectangle {
            id: hideKeyBackground
            radius: 5
            color: "#1e1b18"
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
            Image {
                id: hideKeyIcon
                anchors.centerIn: parent
                scale: keyIconScale
                source: resourcePrefix + "images/hidekeyboard-868482.png"
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: hideKeyBackground
                    opacity: 0.80
                }
                PropertyChanges {
                    target: hideKeyIcon
                    opacity: 0.6
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: hideKeyBackground
                    opacity: 0.8
                }
                PropertyChanges {
                    target: hideKeyIcon
                    opacity: 0.2
                }
            }
        ]
    }

    shiftKeyPanel: KeyPanel {
        Rectangle {
            id: shiftKeyBackground
            radius: 5
            color: "#1e1b18"
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
            Image {
                id: shiftKeyIcon
                anchors.centerIn: parent
                scale: keyIconScale
                source: resourcePrefix + "images/shift-868482.png"
            }
            states: [
                State {
                    name: "capslock"
                    when: InputContext.capsLock
                    PropertyChanges {
                        target: shiftKeyBackground
                        color: "#5a892e"
                    }
                    PropertyChanges {
                        target: shiftKeyIcon
                        source: resourcePrefix + "images/shift-c5d6b6.png"
                    }
                },
                State {
                    name: "shift"
                    when: InputContext.shift
                    PropertyChanges {
                        target: shiftKeyIcon
                        source: resourcePrefix + "images/shift-80c342.png"
                    }
                }
            ]
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: shiftKeyBackground
                    opacity: 0.80
                }
                PropertyChanges {
                    target: shiftKeyIcon
                    opacity: 0.6
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: shiftKeyBackground
                    opacity: 0.8
                }
                PropertyChanges {
                    target: shiftKeyIcon
                    opacity: 0.2
                }
            }
        ]
    }

    spaceKeyPanel: KeyPanel {
        Rectangle {
            id: spaceKeyBackground
            radius: 5
            color: "#35322f"
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
            Text {
                id: spaceKeyText
                text: Qt.locale(InputContext.locale).nativeLanguageName
                color: currentStyle.inputLocaleIndicatorColor
                Behavior on color { PropertyAnimation { duration: 250 } }
                anchors.centerIn: parent
                font {
                    family: fontFamily
                    weight: Font.Normal
                    pixelSize: 48 * scaleHint
                }
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: spaceKeyBackground
                    opacity: 0.80
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: spaceKeyBackground
                    opacity: 0.8
                }
            }
        ]
    }

    symbolKeyPanel: KeyPanel {
        Rectangle {
            id: symbolKeyBackground
            radius: 5
            color: "#1e1b18"
            anchors.fill: parent
            anchors.margins: keyBackgroundMargin
            Text {
                id: symbolKeyText
                text: control.displayText
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                anchors.margins: keyContentMargin
                font {
                    family: fontFamily
                    weight: Font.Normal
                    pixelSize: 44 * scaleHint
                    capitalization: Font.AllUppercase
                }
            }
        }
        states: [
            State {
                name: "pressed"
                when: control.pressed
                PropertyChanges {
                    target: symbolKeyBackground
                    opacity: 0.80
                }
                PropertyChanges {
                    target: symbolKeyText
                    opacity: 0.6
                }
            },
            State {
                name: "disabled"
                when: !control.enabled
                PropertyChanges {
                    target: symbolKeyBackground
                    opacity: 0.8
                }
                PropertyChanges {
                    target: symbolKeyText
                    opacity: 0.2
                }
            }
        ]
    }

    characterPreviewMargin: 0
    characterPreviewDelegate: Item {
        property string text
        id: characterPreview
        Rectangle {
            id: characterPreviewBackground
            anchors.fill: parent
            color: "#5d5b59"
            radius: 5
            Text {
                id: characterPreviewText
                color: "white"
                text: characterPreview.text
                fontSizeMode: Text.HorizontalFit
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                anchors.margins: Math.round(48 * scaleHint)
                font {
                    family: fontFamily
                    weight: Font.Normal
                    pixelSize: 82 * scaleHint
                }
            }
        }
    }

    alternateKeysListItemWidth: 99 * scaleHint
    alternateKeysListItemHeight: 150 * scaleHint
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
                weight: Font.Normal
                pixelSize: 52 * scaleHint
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
    alternateKeysListHighlight: Rectangle {
        color: "#5d5b59"
        radius: 5
    }
    alternateKeysListBackground: Rectangle {
        color: "#1e1b18"
        radius: 5
    }

    selectionListHeight: 85 * scaleHint
    selectionListDelegate: SelectionListItem {
        id: selectionListItem
        width: Math.round(selectionListLabel.width + selectionListLabel.anchors.leftMargin * 2)
        Text {
            id: selectionListLabel
            anchors.left: parent.left
            anchors.leftMargin: Math.round((pinyinMode ? 50 : 140) * scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            text: decorateText(display, wordCompletionLength)
            color: "#80c342"
            font {
                family: fontFamily
                weight: Font.Normal
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
            radius: 2
            color: "#35322f"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.left
        }
        states: State {
            name: "current"
            when: selectionListItem.ListView.isCurrentItem
            PropertyChanges {
                target: selectionListLabel
                color: "white"
            }
        }
    }
    selectionListBackground: Rectangle {
        color: "#1e1b18"
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
}
