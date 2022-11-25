/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; JapaneseInputMethod {}', parent, "main.qml")
    }
    sourceComponent: {
        switch (InputContext.inputEngine.inputMode) {
        case InputEngine.Katakana:
            return katakana
        case InputEngine.Hiragana:
            return hiragana
        case InputEngine.FullwidthLatin:
            return fullWidthQwerty
        default:
            return qwerty
        }
    }
    Component {
        id: hiragana
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Layout.preferredHeight: 3
                KeyboardColumn {
                    KeyboardRow {
                        smallTextVisible: true
                        Key {
                            text: "\u306C"
                        }
                        Key {
                            id: normalKey
                            text: "\u3075"
                        }
                        Key {
                            text: "\u3042"
                            alternativeKeys: "\u3042\u3041"
                        }
                        Key {
                            text: "\u3046"
                            alternativeKeys: "\u3046\u3045"
                        }
                        Key {
                            text: "\u3048"
                            alternativeKeys: "\u3048\u3047"
                        }
                        Key {
                            text: "\u304A"
                            alternativeKeys: "\u304A\u3049"
                        }
                        Key {
                            text: "\u3084"
                            alternativeKeys: "\u3084\u3083"
                        }
                        Key {
                            text: "\u3086"
                            alternativeKeys: "\u3086\u3085"
                        }
                        Key {
                            text: "\u3088"
                            alternativeKeys: "\u3088\u3087"
                        }
                        Key {
                            text: "\u308F"
                            alternativeKeys: "\u308F\u3092"
                        }
                        Key {
                            text: "\u307B"
                        }
                        Key {
                            text: "\u3078"
                        }
                    }
                    KeyboardRow {
                        smallTextVisible: true
                        Key {
                            text: "\u305F"
                        }
                        Key {
                            text: "\u3066"
                        }
                        Key {
                            text: "\u3044"
                            alternativeKeys: "\u3044\u3043"
                        }
                        Key {
                            text: "\u3059"
                        }
                        Key {
                            text: "\u304B"
                        }
                        Key {
                            text: "\u3093"
                        }
                        Key {
                            text: "\u306A"
                        }
                        Key {
                            text: "\u306B"
                        }
                        Key {
                            text: "\u3089"
                        }
                        Key {
                            text: "\u305B"
                        }
                        Key {
                            text: "\u3099"
                        }
                        Key {
                            text: "\u309A"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "\u3061"
                        }
                        Key {
                            text: "\u3068"
                        }
                        Key {
                            text: "\u3057"
                        }
                        Key {
                            text: "\u306F"
                        }
                        Key {
                            text: "\u304D"
                        }
                        Key {
                            text: "\u304F"
                        }
                        Key {
                            text: "\u307E"
                        }
                        Key {
                            text: "\u306E"
                        }
                        Key {
                            text: "\u308A"
                        }
                        Key {
                            text: "\u308C"
                        }
                        Key {
                            text: "\u3051"
                        }
                        Key {
                            text: "\u3080"
                        }
                    }
                    KeyboardRow {
                        smallTextVisible: true
                        KeyboardRow {
                            Layout.preferredWidth: functionKeyWidth
                            Layout.fillWidth: false
                            FillerKey {
                            }
                            Key {
                                text: "\u3064"
                                alternativeKeys: "\u3064\u3063"
                                weight: normalKeyWidth
                                Layout.fillWidth: false
                            }
                        }
                        Key {
                            text: "\u3055"
                        }
                        Key {
                            text: "\u305D"
                        }
                        Key {
                            text: "\u3072"
                        }
                        Key {
                            text: "\u3053"
                        }
                        Key {
                            text: "\u307F"
                        }
                        Key {
                            text: "\u3082"
                        }
                        Key {
                            text: "\u306D"
                        }
                        Key {
                            text: "\u308B"
                        }
                        Key {
                            text: "\u3081"
                        }
                        KeyboardRow {
                            Layout.preferredWidth: functionKeyWidth
                            Layout.fillWidth: false
                            Key {
                                text: "\u308D"
                                weight: normalKeyWidth
                                Layout.fillWidth: false
                            }
                            FillerKey {
                            }
                        }
                    }
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
                    smallTextVisible: true
                    highlighted: true
                }
                InputModeKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    enabled: !(InputContext.inputMethodHints & Qt.ImhLatinOnly) && inputModeCount > 1
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
                BackspaceKey {
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
        id: katakana
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Layout.preferredHeight: 3
                KeyboardColumn {
                    KeyboardRow {
                        smallTextVisible: true
                        Key {
                            text: "\u30CC"
                        }
                        Key {
                            id: normalKey
                            text: "\u30D5"
                        }
                        Key {
                            text: "\u30A2"
                            alternativeKeys: "\u30A2\u30A1"
                        }
                        Key {
                            text: "\u30A6"
                            alternativeKeys: "\u30A6\u30A5"
                        }
                        Key {
                            text: "\u30A8"
                            alternativeKeys: "\u30A8\u30A7"
                        }
                        Key {
                            text: "\u30AA"
                            alternativeKeys: "\u30AA\u30A9"
                        }
                        Key {
                            text: "\u30E4"
                            alternativeKeys: "\u30E4\u30E3"
                        }
                        Key {
                            text: "\u30E6"
                            alternativeKeys: "\u30E6\u30E5"
                        }
                        Key {
                            text: "\u30E8"
                            alternativeKeys: "\u30E8\u30E7"
                        }
                        Key {
                            text: "\u30EF"
                            alternativeKeys: "\u30EF\u30F2"
                        }
                        Key {
                            text: "\u30DB"
                        }
                        Key {
                            text: "\u30D8"
                        }
                    }
                    KeyboardRow {
                        smallTextVisible: true
                        Key {
                            text: "\u30BF"
                        }
                        Key {
                            text: "\u30C6"
                        }
                        Key {
                            text: "\u30A4"
                            alternativeKeys: "\u30A4\u30A3"
                        }
                        Key {
                            text: "\u30B9"
                        }
                        Key {
                            text: "\u30AB"
                        }
                        Key {
                            text: "\u30F3"
                        }
                        Key {
                            text: "\u30CA"
                        }
                        Key {
                            text: "\u30CB"
                        }
                        Key {
                            text: "\u30E9"
                        }
                        Key {
                            text: "\u30BB"
                        }
                        Key {
                            text: "\u3099"
                        }
                        Key {
                            text: "\u309A"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "\u30C1"
                        }
                        Key {
                            text: "\u30C8"
                        }
                        Key {
                            text: "\u30B7"
                        }
                        Key {
                            text: "\u30CF"
                        }
                        Key {
                            text: "\u30AD"
                        }
                        Key {
                            text: "\u30AF"
                        }
                        Key {
                            text: "\u30DE"
                        }
                        Key {
                            text: "\u30CE"
                        }
                        Key {
                            text: "\u30EA"
                        }
                        Key {
                            text: "\u30EC"
                        }
                        Key {
                            text: "\u30B1"
                        }
                        Key {
                            text: "\u30E0"
                        }
                    }
                    KeyboardRow {
                        smallTextVisible: true
                        KeyboardRow {
                            Layout.preferredWidth: functionKeyWidth
                            Layout.fillWidth: false
                            FillerKey {
                            }
                            Key {
                                text: "\u30C4"
                                alternativeKeys: "\u30C4\u30C3"
                                weight: normalKeyWidth
                                Layout.fillWidth: false
                            }
                        }
                        Key {
                            text: "\u30B5"
                        }
                        Key {
                            text: "\u30BD"
                        }
                        Key {
                            text: "\u30D2"
                        }
                        Key {
                            text: "\u30B3"
                        }
                        Key {
                            text: "\u30DF"
                        }
                        Key {
                            text: "\u30E2"
                        }
                        Key {
                            text: "\u30CD"
                        }
                        Key {
                            text: "\u30EB"
                        }
                        Key {
                            text: "\u30E1"
                        }
                        KeyboardRow {
                            Layout.preferredWidth: functionKeyWidth
                            Layout.fillWidth: false
                            Key {
                                text: "\u30ED"
                                weight: normalKeyWidth
                                Layout.fillWidth: false
                            }
                            FillerKey {
                            }
                        }
                    }
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
                    smallTextVisible: true
                    highlighted: true
                }
                InputModeKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    enabled: !(InputContext.inputMethodHints & Qt.ImhLatinOnly) && inputModeCount > 1
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
                BackspaceKey {
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
                    smallTextVisible: true
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
                    smallTextVisible: true
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
