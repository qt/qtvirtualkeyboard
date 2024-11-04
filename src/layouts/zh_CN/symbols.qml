// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; PinyinInputMethod {}', parent, "inputMethodSymbols.qml")
    }
    sharedLayouts: ['main']
    property int page
    readonly property int numPages: 3
    sourceComponent: {
        switch (page) {
        case 2: return page3
        case 1: return page2
        default: return page1
        }
    }
    Component {
        id: page1
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    key: Qt.Key_1
                    text: "1"
                }
                Key {
                    id: normalKey
                    key: Qt.Key_2
                    text: "2"
                }
                Key {
                    key: Qt.Key_3
                    text: "3"
                }
                Key {
                    key: Qt.Key_4
                    text: "4"
                }
                Key {
                    key: Qt.Key_5
                    text: "5"
                }
                Key {
                    key: Qt.Key_6
                    text: "6"
                }
                Key {
                    key: Qt.Key_7
                    text: "7"
                }
                Key {
                    key: Qt.Key_8
                    text: "8"
                }
                Key {
                    key: Qt.Key_9
                    text: "9"
                }
                Key {
                    key: Qt.Key_0
                    text: "0"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_1
                    text: "@"
                }
                Key {
                    key: Qt.Key_1
                    text: "#"
                }
                Key {
                    key: Qt.Key_1
                    text: "%"
                }
                Key {
                    key: Qt.Key_1
                    text: "&"
                }
                Key {
                    key: Qt.Key_1
                    text: "*"
                }
                Key {
                    key: Qt.Key_1
                    text: "_"
                }
                Key {
                    key: Qt.Key_1
                    text: "-"
                }
                Key {
                    key: Qt.Key_1
                    text: "+"
                }
                Key {
                    key: Qt.Key_1
                    text: "("
                }
                Key {
                    key: Qt.Key_1
                    text: ")"
                }
            }
            KeyboardRow {
                Key {
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                    highlighted: true
                }
                Key {
                    text: "“"
                }
                Key {
                    text: "”"
                }
                Key {
                    text: "、"
                }
                Key {
                    text: "："
                }
                Key {
                    text: "；"
                }
                Key {
                    text: "！"
                }
                Key {
                    text: "？"
                }
                Key {
                    text: "～"
                }
                BackspaceKey {
                }
            }
            KeyboardRow {
                SymbolModeKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                    displayText: "ABC"
                }
                ChangeLanguageKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                }
                Key {
                    key: Qt.Key_Comma
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: ","
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
                    text: "—"
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
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    text: "½"
                    alternativeKeys: "½¼¾"
                }
                Key {
                    id: normalKey
                    text: "'"
                }
                Key {
                    text: "/"
                }
                Key {
                    text: "\\"
                }
                Key {
                    text: "|"
                }
                Key {
                    text: "["
                }
                Key {
                    text: "]"
                }
                Key {
                    text: "{"
                }
                Key {
                    text: "}"
                }
                Key {
                    text: "·"
                }
            }
            KeyboardRow {
                Key {
                    text: "<"
                }
                Key {
                    text: ">"
                }
                Key {
                    text: ","
                }
                Key {
                    text: "."
                }
                Key {
                    text: ":"
                }
                Key {
                    text: ";"
                }
                Key {
                    text: "!"
                }
                Key {
                    text: "?"
                }
                Key {
                    text: "="
                }
                Key {
                    text: "~"
                }
            }
            KeyboardRow {
                Key {
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                    highlighted: true
                }
                Key {
                    text: "\""
                }
                Key {
                    text: "§"
                }
                Key {
                    text: "^"
                }
                Key {
                    text: "$"
                }
                Key {
                    text: "￥"
                }
                Key {
                    text: "€"
                }
                Key {
                    text: "£"
                }
                Key {
                    text: "¢"
                }
                BackspaceKey {
                }
            }
            KeyboardRow {
                SymbolModeKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                    displayText: "ABC"
                }
                ChangeLanguageKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                }
                Key {
                    key: Qt.Key_Comma
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: ","
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
                    text: "。"
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
        id: page3
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    text: "＼"
                }
                Key {
                    id: normalKey
                    text: "／"
                }
                Key {
                    text: "（"
                }
                Key {
                    text: "）"
                }
                Key {
                    text: "〔"
                }
                Key {
                    text: "〕"
                }
                Key {
                    text: "〈"
                }
                Key {
                    text: "〉"
                }
                Key {
                    text: "《"
                }
                Key {
                    text: "》"
                }
            }
            KeyboardRow {
                Key {
                    text: "→"
                }
                Key {
                    text: "←"
                }
                Key {
                    text: "↑"
                }
                Key {
                    text: "↓"
                }
                Key {
                    text: "■"
                }
                Key {
                    text: "□"
                }
                Key {
                    text: "●"
                }
                Key {
                    text: "○"
                }
                Key {
                    text: "【"
                }
                Key {
                    text: "】"
                }
            }
            KeyboardRow {
                Key {
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                    highlighted: true
                }
                Key {
                    text: "『"
                }
                Key {
                    text: "』"
                }
                Key {
                    text: "「"
                }
                Key {
                    text: "」"
                }
                Key {
                    text: "★"
                }
                Key {
                    text: "☆"
                }
                Key {
                    text: "◆"
                }
                Key {
                    text: "◇"
                }
                BackspaceKey {
                }
            }
            KeyboardRow {
                SymbolModeKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                    displayText: "ABC"
                }
                ChangeLanguageKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                }
                Key {
                    key: Qt.Key_Comma
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: ","
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
                    text: "…"
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
