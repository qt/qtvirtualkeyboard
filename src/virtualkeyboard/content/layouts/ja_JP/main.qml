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
import QtQuick.VirtualKeyboard
import QtQuick.Layouts

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; JapaneseInputMethod {}', parent, "japaneseInputMethod")
    }
    sharedLayouts: ['symbols']
    sourceComponent: InputContext.inputEngine.inputMode === InputEngine.InputMode.FullwidthLatin ? page2 : page1
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
                EnterKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
        }
    }
}
