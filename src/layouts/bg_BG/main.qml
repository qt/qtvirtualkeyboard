// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components
import QtQuick.Layouts

KeyboardLayoutLoader {
    sharedLayouts: ['symbols']
    sourceComponent: InputContext.inputEngine.inputMode === InputEngine.InputMode.Cyrillic ? cyrillicLayout : latinLayout
    Component {
        id: cyrillicLayout
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    text: "я"
                }
                Key {
                    id: normalKey
                    text: "в"
                }
                Key {
                    text: "е"
                }
                Key {
                    text: "р"
                }
                Key {
                    text: "т"
                }
                Key {
                    text: "ъ"
                }
                Key {
                    text: "у"
                }
                Key {
                    text: "и"
                }
                Key {
                    text: "о"
                }
                Key {
                    text: "п"
                }
                Key {
                    text: "ч"
                }
            }
            KeyboardRow {
                Key {
                    text: "а"
                }
                Key {
                    text: "с"
                }
                Key {
                    text: "д"
                }
                Key {
                    text: "ф"
                }
                Key {
                    text: "г"
                }
                Key {
                    text: "х"
                }
                Key {
                    text: "й"
                }
                Key {
                    text: "к"
                }
                Key {
                    text: "л"
                }
                Key {
                    text: "ш"
                }
                Key {
                    text: "щ"
                }
            }
            KeyboardRow {
                ShiftKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
                Key {
                    text: "з"
                }
                Key {
                    text: "ь"
                }
                Key {
                    text: "ц"
                }
                Key {
                    text: "ж"
                }
                Key {
                    text: "б"
                }
                Key {
                    text: "н"
                }
                Key {
                    text: "м"
                }
                Key {
                    text: "ю"
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
                    text: ","
                    smallText: "\u2699"
                    smallTextVisible: keyboard.isFunctionPopupListAvailable()
                    highlighted: true
                }
                InputModeKey {
                    inputModes: [InputEngine.InputMode.Cyrillic, InputEngine.InputMode.Latin]
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                }
                SpaceKey {
                }
                Key {
                    key: Qt.Key_Period
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "."
                    alternativeKeys: "!.?"
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
        id: latinLayout
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
                    alternativeKeys: "êeëèé"
                }
                Key {
                    key: Qt.Key_R
                    text: "r"
                    alternativeKeys: "ŕrř"
                }
                Key {
                    key: Qt.Key_T
                    text: "t"
                    alternativeKeys: "ţtŧť"
                }
                Key {
                    key: Qt.Key_Y
                    text: "y"
                    alternativeKeys: "ÿyýŷ"
                }
                Key {
                    key: Qt.Key_U
                    text: "u"
                    alternativeKeys: "űūũûüuùú"
                }
                Key {
                    key: Qt.Key_I
                    text: "i"
                    alternativeKeys: "îïīĩiìí"
                }
                Key {
                    key: Qt.Key_O
                    text: "o"
                    alternativeKeys: "œøõôöòóo"
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
                        alternativeKeys: (InputContext.inputMethodHints & (Qt.ImhEmailCharactersOnly | Qt.ImhUrlCharactersOnly)) ? "a@äåãâàá" : "aäåãâàá"
                        smallTextVisible: (InputContext.inputMethodHints & (Qt.ImhEmailCharactersOnly | Qt.ImhUrlCharactersOnly))
                        weight: normalKeyWidth
                        Layout.fillWidth: false
                    }
                }
                Key {
                    key: Qt.Key_S
                    text: "s"
                    alternativeKeys: "šsşś"
                }
                Key {
                    key: Qt.Key_D
                    text: "d"
                    alternativeKeys: "dđď"
                }
                Key {
                    key: Qt.Key_F
                    text: "f"
                }
                Key {
                    key: Qt.Key_G
                    text: "g"
                    alternativeKeys: "ġgģĝğ"
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
                        alternativeKeys: "ĺŀłļľl"
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
                    text: "z"
                    alternativeKeys: "zžż"
                }
                Key {
                    key: Qt.Key_X
                    text: "x"
                }
                Key {
                    key: Qt.Key_C
                    text: "c"
                    alternativeKeys: "çcċčć"
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
                    alternativeKeys: "ņńnň"
                }
                Key {
                    key: Qt.Key_M
                    text: "m"
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
                    text: ","
                    smallText: "\u2699"
                    smallTextVisible: keyboard.isFunctionPopupListAvailable()
                    highlighted: true
                }
                InputModeKey {
                    enabled: !(InputContext.inputMethodHints & Qt.ImhLatinOnly) && inputModeCount > 1
                    inputModes: [InputEngine.InputMode.Cyrillic, InputEngine.InputMode.Latin]
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                }
                SpaceKey {
                }
                Key {
                    key: Qt.Key_Period
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "."
                    alternativeKeys: "!.?"
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
}
