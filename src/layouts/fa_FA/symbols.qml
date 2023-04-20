// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components

KeyboardLayoutLoader {
    property bool secondPage
    onVisibleChanged: if (!visible) secondPage = false
    sourceComponent: secondPage ? page2 : page1
    Component {
        id: page1
        KeyboardLayout {
            keyWeight: 160
            smallTextVisible: true
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    text: "\u06F1"
                    alternativeKeys: "\u06F11"
                }
                Key {
                    id: normalKey
                    text: "\u06F2"
                    alternativeKeys: "\u06F22"
                }
                Key {
                    text: "\u06F3"
                    alternativeKeys: "\u06F33"
                }
                Key {
                    text: "\u06F4"
                    alternativeKeys: "\u06F44"
                }
                Key {
                    text: "\u06F5"
                    alternativeKeys: "\u06F55"
                }
                Key {
                    text: "\u06F6"
                    alternativeKeys: "\u06F66"
                }
                Key {
                    text: "\u06F7"
                    alternativeKeys: "\u06F77"
                }
                Key {
                    text: "\u06F8"
                    alternativeKeys: "\u06F88"
                }
                Key {
                    text: "\u06F9"
                    alternativeKeys: "\u06F99"
                }
                Key {
                    text: "\u06F0"
                    alternativeKeys: "\u06F00"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_At
                    text: "@"
                }
                Key {
                    key: Qt.Key_NumberSign
                    text: "#"
                }
                Key {
                    key:  Qt.Key_Percent
                    text: "%"
                }
                Key {
                    key: Qt.Key_Ampersand
                    text: "&"
                }
                Key {
                    key: Qt.Key_Asterisk
                    text: "*"
                }
                Key {
                    key: Qt.Key_Underscore
                    text: "_"
                }
                Key {
                    key: Qt.Key_Minus
                    text: "-"
                }
                Key {
                    key: Qt.Key_Plus
                    text: "+"
                }
                Key {
                    key: Qt.Key_ParenLeft
                    text: "("
                }
                Key {
                    key: Qt.Key_ParenRight
                    text: ")"
                }
            }
            KeyboardRow {
                Key {
                    displayText: "1/2"
                    functionKey: true
                    onClicked: secondPage = !secondPage
                    highlighted: true
                }
                Key {
                    key:  Qt.Key_QuoteDbl
                    text: '"'
                }
                Key {
                    key: Qt.Key_Less
                    text: "<"
                }
                Key {
                    key: Qt.Key_Greater
                    text: ">"
                }
                Key {
                    key: Qt.Key_Apostrophe
                    text: "'"
                }
                Key {
                    key: Qt.Key_Semicolon
                    text: "\u061B"
                    alternativeKeys: "\u061B;"
                }
                Key {
                    key: Qt.Key_Slash
                    text: "/"
                }
                Key {
                    key: Qt.Key_Exclam
                    text: "!"
                }
                Key {
                    key: Qt.Key_Question
                    text: "\u061F"
                    alternativeKeys: "\u061F?"
                }
                BackspaceKey {
                }
            }
            KeyboardRow {
                SymbolModeKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                    displayText: "\u0627\u200C\u0628\u200C\u067E"
                }
                ChangeLanguageKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                }
                Key {
                    key: Qt.Key_Comma
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "\u060C"
                    smallText: "\u2699"
                    smallTextVisible: keyboard.isFunctionPopupListAvailable()
                    highlighted: true
                }
                SpaceKey {
                }
                Key {
                    key: Qt.Key_Period
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "."
                    alternativeKeys: "!,\u060C."
                    highlighted: true
                }
                HideKeyboardKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                }
                EnterKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
        }
    }
    Component {
        id: page2
        KeyboardLayout {
            keyWeight: 160
            smallTextVisible: true
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    key: Qt.Key_AsciiTilde
                    text: "~"
                }
                Key {
                    id: normalKey
                    key: Qt.Key_Agrave
                    text: "`"
                }
                Key {
                    key: Qt.Key_Bar
                    text: "|"
                }
                Key {
                    key: 0x7B
                    text: "·"
                }
                Key {
                    key: 0x221A
                    text: "√"
                }
                Key {
                    key: Qt.Key_division
                    text: "÷"
                }
                Key {
                    key: Qt.Key_multiply
                    text: "×"
                }
                Key {
                    key: Qt.Key_onehalf
                    text: "½"
                    alternativeKeys: "¼⅓½¾⅞"
                }
                Key {
                    key: Qt.Key_BraceLeft
                    text: "{"
                }
                Key {
                    key: Qt.Key_BraceRight
                    text: "}"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_Dollar
                    text: "$"
                }
                Key {
                    key: 0x20AC
                    text: "€"
                }
                Key {
                    key: 0xC2
                    text: "£"
                }
                Key {
                    key: 0xA2
                    text: "¢"
                }
                Key {
                    key: 0xFDFC
                    text: "\uFDFC"
                }
                Key {
                    key: Qt.Key_AsciiCircum
                    text: "^"
                }
                Key {
                    key: Qt.Key_Equal
                    text: "="
                }
                Key {
                    key: Qt.Key_section
                    text: "§"
                }
                Key {
                    key: Qt.Key_BracketLeft
                    text: "["
                }
                Key {
                    key: Qt.Key_BracketRight
                    text: "]"
                }
            }
            KeyboardRow {
                Key {
                    displayText: "2/2"
                    functionKey: true
                    onClicked: secondPage = !secondPage
                    highlighted: true
                }
                Key {
                    key: 0x2122
                    text: '™'
                }
                Key {
                    key: 0x00AE
                    text: '®'
                }
                Key {
                    key: Qt.Key_guillemotleft
                    text: '«'
                }
                Key {
                    key: Qt.Key_guillemotright
                    text: '»'
                }
                Key {
                    key: Qt.Key_Colon
                    text: ":"
                }
                Key {
                    key: 0x201C
                    text: '“'
                }
                Key {
                    key: 0x201D
                    text: '”'
                }
                Key {
                    key: Qt.Key_Backslash
                    text: "\\"
                }
                BackspaceKey {
                }
            }
            KeyboardRow {
                SymbolModeKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                    displayText: "\u0627\u200C\u0628\u200C\u067E"
                }
                ChangeLanguageKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                }
                Key {
                    key: Qt.Key_Comma
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "\u060C"
                    smallText: "\u2699"
                    smallTextVisible: keyboard.isFunctionPopupListAvailable()
                    highlighted: true
                }
                SpaceKey {
                }
                Key {
                    key: 0x2026
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "\u2026"
                    highlighted: true
                }
                HideKeyboardKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                }
                EnterKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
        }
    }
}
