// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; JapaneseInputMethod {}', parent, "japaneseInputMethod")
    }
    sourceComponent: {
        switch (InputContext.inputEngine.inputMode) {
        case InputEngine.Katakana:
            return katakana9key
        case InputEngine.Hiragana:
            return hiragana9key
        case InputEngine.FullwidthLatin:
            return fullWidthQwerty
        default:
            return qwerty
        }
    }
    Component {
        id: hiragana9key
        KeyboardLayout {
            KeyboardRow {
                Layout.fillWidth: false
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter
                KeyboardColumn {
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.height / 4 * 1
                    Key {
                        text: "～"
                        alternativeKeys: "～『』「」（）〔〕〈〉《》【】"
                        highlighted: true
                    }
                    Key {
                        text: "@"
                        alternativeKeys: "@#$%^&*()=<>,.:;!?~"
                        highlighted: true
                    }
                    InputModeKey {}
                    SymbolModeKey {}
                }
                KeyboardColumn {
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.height / 30
                    KeyboardRow {
                        FillerKey {}
                    }
                }
                KeyboardColumn {
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.height / 4 * 3
                    KeyboardRow {
                        FlickKey {
                            text: "あ"
                            alternativeKeys: "あいうえお"
                        }
                        FlickKey {
                            text: "か"
                            alternativeKeys: "かきくけこ"
                        }
                        FlickKey {
                            text: "さ"
                            alternativeKeys: "さしすせそ"
                        }
                    }
                    KeyboardRow {
                        FlickKey {
                            text: "た"
                            alternativeKeys: "たちつてと"
                        }
                        FlickKey {
                            text: "な"
                            alternativeKeys: "なにぬねの"
                        }
                        FlickKey {
                            text: "は"
                            alternativeKeys: "はひふへほ"
                        }
                    }
                    KeyboardRow {
                        FlickKey {
                            text: "ま"
                            alternativeKeys: "まみむめも"
                        }
                        FlickKey {
                            text: "や"
                            alternativeKeys: "や（ゆ）よ"
                        }
                        FlickKey {
                            text: "ら"
                            alternativeKeys: "らりるれろ"
                        }
                    }
                    KeyboardRow {
                        readonly property bool modifyKeyEnabled: InputContext.inputEngine.inputMethod !== null &&
                                                                 InputContext.inputEngine.inputMethod.hasOwnProperty("modifyKeyEnabled") &&
                                                                 InputContext.inputEngine.inputMethod.modifyKeyEnabled
                        FlickKey {
                            visible: parent.modifyKeyEnabled
                            text: "小"
                            alternativeKeys: "小\u3099\u309A"
                        }
                        Key {
                            visible: !parent.modifyKeyEnabled
                            key: Qt.Key_Comma
                            text: "\u3001"
                            smallText: "\u2699"
                            smallTextVisible: keyboard.isFunctionPopupListAvailable()
                        }
                        FlickKey {
                            text: "わ"
                            alternativeKeys: "わをんー〜"
                        }
                        FlickKey {
                            text: "。"
                            alternativeKeys: "。，！：？"
                        }
                    }
                }
                KeyboardColumn {
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.height / 30
                    KeyboardRow {
                        FillerKey {}
                    }
                }
                KeyboardColumn {
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.height / 4 * 1
                    BackspaceKey {}
                    Key {
                        text: "\u3000"
                        displayText: "\u2423"
                        repeat: true
                        showPreview: false
                        key: Qt.Key_Space
                        highlighted: true
                    }
                    HideKeyboardKey {
                        visible: true
                    }
                    EnterKey {}
                }
            }
        }
    }
    Component {
        id: katakana9key
        KeyboardLayout {
            KeyboardRow {
                Layout.fillWidth: false
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter
                KeyboardColumn {
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.height / 4 * 1
                    Key {
                        text: "～"
                        alternativeKeys: "～『』「」（）〔〕〈〉《》【】"
                        highlighted: true
                    }
                    Key {
                        text: "@"
                        alternativeKeys: "@#$%^&*()=<>,.:;!?~"
                        highlighted: true
                    }
                    InputModeKey {}
                    SymbolModeKey {}
                }
                KeyboardColumn {
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.height / 30
                    KeyboardRow {
                        FillerKey {}
                    }
                }
                KeyboardColumn {
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.height / 4 * 3
                    KeyboardRow {
                        FlickKey {
                            text: "ア"
                            alternativeKeys: "アイウエオ"
                        }
                        FlickKey {
                            text: "カ"
                            alternativeKeys: "カキクケコ"
                        }
                        FlickKey {
                            text: "サ"
                            alternativeKeys: "サシスセソ"
                        }
                    }
                    KeyboardRow {
                        FlickKey {
                            text: "タ"
                            alternativeKeys: "タチツテト"
                        }
                        FlickKey {
                            text: "ナ"
                            alternativeKeys: "ナニヌネノ"
                        }
                        FlickKey {
                            text: "ハ"
                            alternativeKeys: "ハヒフヘホ"
                        }
                    }
                    KeyboardRow {
                        FlickKey {
                            text: "マ"
                            alternativeKeys: "マミムメモ"
                        }
                        FlickKey {
                            text: "ヤ"
                            alternativeKeys: "ヤ（ユ）ヨ"
                        }
                        FlickKey {
                            text: "ラ"
                            alternativeKeys: "ラリルレロ"
                        }
                    }
                    KeyboardRow {
                        readonly property bool modifyKeyEnabled: InputContext.inputEngine.inputMethod !== null &&
                                                                 InputContext.inputEngine.inputMethod.hasOwnProperty("modifyKeyEnabled") &&
                                                                 InputContext.inputEngine.inputMethod.modifyKeyEnabled
                        FlickKey {
                            visible: parent.modifyKeyEnabled
                            text: "小"
                            alternativeKeys: "小\u3099\u309A"
                        }
                        Key {
                            visible: !parent.modifyKeyEnabled
                            key: Qt.Key_Comma
                            text: "\u3001"
                            smallText: "\u2699"
                            smallTextVisible: keyboard.isFunctionPopupListAvailable()
                        }
                        FlickKey {
                            text: "ワ"
                            alternativeKeys: "ワヲンー〜"
                        }
                        FlickKey {
                            text: "。"
                            alternativeKeys: "。，！：？"
                        }
                    }
                }
                KeyboardColumn {
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.height / 30
                    KeyboardRow {
                        FillerKey {}
                    }
                }
                KeyboardColumn {
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.height / 4 * 1
                    BackspaceKey {}
                    Key {
                        text: "\u3000"
                        displayText: "\u2423"
                        repeat: true
                        showPreview: false
                        key: Qt.Key_Space
                        highlighted: true
                    }
                    HideKeyboardKey {
                        visible: true
                    }
                    EnterKey {}
                }
            }
        }
    }
    Component {
        id: qwerty
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    key: Qt.Key_Q
                    text: "q"
                }
                Key {
                    id: normalKey
                    key: Qt.Key_W
                    text: "w"
                }
                Key {
                    key: Qt.Key_E
                    text: "e"
                }
                Key {
                    key: Qt.Key_R
                    text: "r"
                }
                Key {
                    key: Qt.Key_T
                    text: "t"
                }
                Key {
                    key: Qt.Key_Y
                    text: "y"
                }
                Key {
                    key: Qt.Key_U
                    text: "u"
                }
                Key {
                    key: Qt.Key_I
                    text: "i"
                }
                Key {
                    key: Qt.Key_O
                    text: "o"
                }
                Key {
                    key: Qt.Key_P
                    text: "p"
                }
            }
            KeyboardRow {
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    FillerKey {
                    }
                    Key {
                        key: Qt.Key_A
                        text: "a"
                        Layout.preferredWidth: normalKeyWidth
                        Layout.fillWidth: false
                    }
                }
                Key {
                    key: Qt.Key_S
                    text: "s"
                }
                Key {
                    key: Qt.Key_D
                    text: "d"
                }
                Key {
                    key: Qt.Key_F
                    text: "f"
                }
                Key {
                    key: Qt.Key_G
                    text: "g"
                }
                Key {
                    key: Qt.Key_H
                    text: "h"
                }
                Key {
                    key: Qt.Key_J
                    text: "j"
                }
                Key {
                    key: Qt.Key_K
                    text: "k"
                }
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    Key {
                        key: Qt.Key_L
                        text: "l"
                        Layout.preferredWidth: normalKeyWidth
                        Layout.fillWidth: false
                    }
                    FillerKey {
                    }
                }
            }
            KeyboardRow {
                ShiftKey {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                }
                Key {
                    key: Qt.Key_Z
                    text: "z"
                }
                Key {
                    key: Qt.Key_X
                    text: "x"
                }
                Key {
                    key: Qt.Key_C
                    text: "c"
                }
                Key {
                    key: Qt.Key_V
                    text: "v"
                }
                Key {
                    key: Qt.Key_B
                    text: "b"
                }
                Key {
                    key: Qt.Key_N
                    text: "n"
                }
                Key {
                    key: Qt.Key_M
                    text: "m"
                }
                BackspaceKey {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
            KeyboardRow {
                SymbolModeKey {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                }
                Key {
                    key: Qt.Key_Comma
                    Layout.preferredWidth: normalKeyWidth
                    Layout.fillWidth: false
                    text: "\u3001"
                    smallText: "\u2699"
                    smallTextVisible: keyboard.isFunctionPopupListAvailable()
                    highlighted: true
                }
                InputModeKey {
                    enabled: !(InputContext.inputMethodHints & Qt.ImhLatinOnly) && inputModeCount > 1
                    Layout.preferredWidth: normalKeyWidth
                    Layout.fillWidth: false
                    inputModeNameList: [
                        "半角",  // InputEngine.InputMode.Latin
                        "",     // InputEngine.InputMode.Numeric
                        "",     // InputEngine.InputMode.Dialable
                        "",     // InputEngine.InputMode.Pinyin
                        "",     // InputEngine.InputMode.Cangjie
                        "",     // InputEngine.InputMode.Zhuyin
                        "",     // InputEngine.InputMode.Hangul
                        "あ",    // InputEngine.InputMode.Hiragana
                        "カ",    // InputEngine.InputMode.Katakana
                        "全角",  // InputEngine.InputMode.FullwidthLatin
                    ]
                }
                SpaceKey {
                }
                Key {
                    key: Qt.Key_Period
                    Layout.preferredWidth: normalKeyWidth
                    Layout.fillWidth: false
                    text: "\u3002"
                    alternativeKeys: "\u3001\uFF01\u3002\uFF1F,.?!"
                    smallText: "!?"
                    smallTextVisible: true
                    highlighted: true
                }
                EnterKey {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
        }
    }
    Component {
        id: fullWidthQwerty
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    key: Qt.Key_Q
                    text: "\uFF51"
                }
                Key {
                    id: normalKey
                    key: Qt.Key_W
                    text: "\uFF57"
                }
                Key {
                    key: Qt.Key_E
                    text: "\uFF45"
                }
                Key {
                    key: Qt.Key_R
                    text: "\uFF52"
                }
                Key {
                    key: Qt.Key_T
                    text: "\uFF54"
                }
                Key {
                    key: Qt.Key_Y
                    text: "\uFF59"
                }
                Key {
                    key: Qt.Key_U
                    text: "\uFF55"
                }
                Key {
                    key: Qt.Key_I
                    text: "\uFF49"
                }
                Key {
                    key: Qt.Key_O
                    text: "\uFF4F"
                }
                Key {
                    key: Qt.Key_P
                    text: "\uFF50"
                }
            }
            KeyboardRow {
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    FillerKey {
                    }
                    Key {
                        key: Qt.Key_A
                        text: "\uFF41"
                        weight: normalKeyWidth
                        Layout.fillWidth: false
                    }
                }
                Key {
                    key: Qt.Key_S
                    text: "\uFF53"
                }
                Key {
                    key: Qt.Key_D
                    text: "\uFF44"
                }
                Key {
                    key: Qt.Key_F
                    text: "\uFF46"
                }
                Key {
                    key: Qt.Key_G
                    text: "\uFF47"
                }
                Key {
                    key: Qt.Key_H
                    text: "\uFF48"
                }
                Key {
                    key: Qt.Key_J
                    text: "\uFF4A"
                }
                Key {
                    key: Qt.Key_K
                    text: "\uFF4B"
                }
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    Key {
                        key: Qt.Key_L
                        text: "\uFF4C"
                        weight: normalKeyWidth
                        Layout.fillWidth: false
                    }
                    FillerKey {
                    }
                }
            }
            KeyboardRow {
                ShiftKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
                Key {
                    key: Qt.Key_Z
                    text: "\uFF5A"
                }
                Key {
                    key: Qt.Key_X
                    text: "\uFF58"
                }
                Key {
                    key: Qt.Key_C
                    text: "\uFF43"
                }
                Key {
                    key: Qt.Key_V
                    text: "\uFF56"
                }
                Key {
                    key: Qt.Key_B
                    text: "\uFF42"
                }
                Key {
                    key: Qt.Key_N
                    text: "\uFF4E"
                }
                Key {
                    key: Qt.Key_M
                    text: "\uFF4D"
                }
                BackspaceKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
            KeyboardRow {
                SymbolModeKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
                Key {
                    key: Qt.Key_Comma
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "\u3001"
                    smallText: "\u2699"
                    smallTextVisible: keyboard.isFunctionPopupListAvailable()
                    highlighted: true
                }
                InputModeKey {
                    enabled: !(InputContext.inputMethodHints & Qt.ImhLatinOnly) && inputModeCount > 1
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    inputModeNameList: [
                        "半角",  // InputEngine.InputMode.Latin
                        "",     // InputEngine.InputMode.Numeric
                        "",     // InputEngine.InputMode.Dialable
                        "",     // InputEngine.InputMode.Pinyin
                        "",     // InputEngine.InputMode.Cangjie
                        "",     // InputEngine.InputMode.Zhuyin
                        "",     // InputEngine.InputMode.Hangul
                        "あ",    // InputEngine.InputMode.Hiragana
                        "カ",    // InputEngine.InputMode.Katakana
                        "全角",  // InputEngine.InputMode.FullwidthLatin
                    ]
                }
                SpaceKey {
                }
                Key {
                    key: Qt.Key_Period
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "\u3002"
                    alternativeKeys: "\u3001\uFF01\u3002\uFF1F,.?!"
                    smallText: "!?"
                    smallTextVisible: true
                    highlighted: true
                }
                EnterKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
        }
    }
}
