// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components
import QtQuick.Layouts

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; JapaneseInputMethod {}', parent, "inputMethod.qml")
    }

    function __pickInputMode(mode) {
        switch (mode) {
            case InputEngine.InputMode.FullwidthLatin:
                return page2
            case InputEngine.InputMode.HiraganaFlick:
                return page3
            default:
                return page1
        }
    }

    sharedLayouts: ['symbols']
    sourceComponent: __pickInputMode(InputContext.inputEngine.inputMode)
    Component {
        id: page1
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
                ChangeLanguageKey {
                    weight: normalKeyWidth
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
                        "",     // InputEngine.InputMode.Greek
                        "",     // InputEngine.InputMode.Cyrillic
                        "",     // InputEngine.InputMode.Arabic
                        "",     // InputEngine.InputMode.Hebrew
                        "",     // InputEngine.InputMode.ChineseHandwriting
                        "",     // InputEngine.InputMode.JapaneseHandwriting
                        "",     // InputEngine.InputMode.KoreanHandwriting
                        "",     // InputEngine.InputMode.Thai
                        "",     // InputEngine.InputMode.Stroke
                        "",     // InputEngine.InputMode.Romaji
                        "FLK",  // InputEngine.InputMode.HiraganaFlick
                    ]
                }
                SpaceKey {
                }
                Key {
                    key: Qt.Key_Left
                    Layout.preferredWidth: normalKeyWidth / 2
                    Layout.fillWidth: false
                    displayText: "\u2190"
                    repeat: true
                    noModifier: true
                    functionKey: true
                    highlighted: true
                }
                Key {
                    key: Qt.Key_Right
                    Layout.preferredWidth: normalKeyWidth / 2
                    Layout.fillWidth: false
                    displayText: "\u2192"
                    repeat: true
                    noModifier: true
                    functionKey: true
                    highlighted: true
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
                HideKeyboardKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                }
                EnterKey {
                    Layout.preferredWidth: functionKeyWidth
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
                ChangeLanguageKey {
                    weight: normalKeyWidth
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
                        "",     // InputEngine.InputMode.Greek
                        "",     // InputEngine.InputMode.Cyrillic
                        "",     // InputEngine.InputMode.Arabic
                        "",     // InputEngine.InputMode.Hebrew
                        "",     // InputEngine.InputMode.ChineseHandwriting
                        "",     // InputEngine.InputMode.JapaneseHandwriting
                        "",     // InputEngine.InputMode.KoreanHandwriting
                        "",     // InputEngine.InputMode.Thai
                        "",     // InputEngine.InputMode.Stroke
                        "",     // InputEngine.InputMode.Romaji
                        "FLK",  // InputEngine.InputMode.HiraganaFlick
                    ]
                }
                SpaceKey {
                }
                Key {
                    key: Qt.Key_Left
                    weight: normalKeyWidth / 2
                    Layout.fillWidth: false
                    displayText: "\u2190"
                    repeat: true
                    noModifier: true
                    functionKey: true
                    highlighted: true
                }
                Key {
                    key: Qt.Key_Right
                    weight: normalKeyWidth / 2
                    Layout.fillWidth: false
                    displayText: "\u2192"
                    repeat: true
                    noModifier: true
                    functionKey: true
                    highlighted: true
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
                FillerKey {}
                FlickKey {
                    text: "\u3042" //a
                    alternativeKeys: "\u3044\u3046\u3048\u304A"
                }
                FlickKey {
                    id: normalKey
                    text: "\u304B" //ka
                    alternativeKeys: "\u3053\u304D\u304F\u3051"
                }
                FlickKey {
                    text: "\u3055" //sa
                    alternativeKeys: "\u3057\u3059\u305B\u305D"
                }
                BackspaceKey {}
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_Left
                    displayText: "\u2190"
                    repeat: true
                    noModifier: true
                    functionKey: true
                    highlighted: true
                }
                FlickKey {
                    text: "\u305F" //ta
                    alternativeKeys: "\u3061\u3064\u3066\u3068"
                }
                FlickKey {
                    text: "\u306A" //na
                    alternativeKeys: "\u306B\u306C\u306D\u306E"
                }
                FlickKey {
                    text: "\u306F" //ha
                    alternativeKeys: "\u3072\u3075\u3078\u307B"
                }
                Key {
                    key: Qt.Key_Right
                    displayText: "\u2192"
                    repeat: true
                    noModifier: true
                    functionKey: true
                    highlighted: true
                }
            }
            KeyboardRow {
                SymbolModeKey {}
                FlickKey {
                    text: "\u307E" //ma
                    alternativeKeys: "\u307F\u3080\u3081\u3082"
                }
                FlickKey {
                    text: "\u3084" //ya
                    alternativeKeys: "\u3086\u3088"
                }
                FlickKey {
                    text: "\u3089" //ra
                    alternativeKeys: "\u308A\u308B\u308C\u308D"
                }
                SpaceKey {}
            }
            KeyboardRow {
                InputModeKey {
                    enabled: !(InputContext.inputMethodHints & Qt.ImhLatinOnly) && inputModeCount > 1
                    weight: normalKeyWidth / 2
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
                        "",     // InputEngine.InputMode.Greek
                        "",     // InputEngine.InputMode.Cyrillic
                        "",     // InputEngine.InputMode.Arabic
                        "",     // InputEngine.InputMode.Hebrew
                        "",     // InputEngine.InputMode.ChineseHandwriting
                        "",     // InputEngine.InputMode.JapaneseHandwriting
                        "",     // InputEngine.InputMode.KoreanHandwriting
                        "",     // InputEngine.InputMode.Thai
                        "",     // InputEngine.InputMode.Stroke
                        "",     // InputEngine.InputMode.Romaji
                        "FLK",  // InputEngine.InputMode.HiraganaFlick
                    ]
                }
                ChangeLanguageKey {
                    weight: normalKeyWidth / 2
                }
                FlickKey {
                    weight: normalKeyWidth
                    text: "\u3099"
                    alternativeKeys: "\u309A"
                }
                FlickKey {
                    weight: normalKeyWidth
                    text: "\u308F" //wa
                    alternativeKeys: "\u3093\u3092\u30FC\u301C"
                }
                FlickKey {
                    weight: normalKeyWidth
                    text: "\u3001" //
                    alternativeKeys: "\u3002\u003F\u0021\u2026"
                }
                EnterKey {
                    weight: normalKeyWidth
                }
            }
        }
    }
}
