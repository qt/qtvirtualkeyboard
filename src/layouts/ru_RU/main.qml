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
                    key: 0x0419
                    text: "й"
                }
                Key {
                    id: normalKey
                    key: 0x0426
                    text: "ц"
                }
                Key {
                    key: 0x0423
                    text: "у"
                }
                Key {
                    key: 0x041A
                    text: "к"
                }
                Key {
                    key: 0x0415
                    text: "е"
                    alternativeKeys: "её"
                }
                Key {
                    key: 0x041D
                    text: "н"
                }
                Key {
                    key: 0x0413
                    text: "г"
                }
                Key {
                    key: 0x0428
                    text: "ш"
                }
                Key {
                    key: 0x0429
                    text: "щ"
                }
                Key {
                    key: 0x0417
                    text: "з"
                }
                Key {
                    key: 0x0425
                    text: "х"
                }
            }
            KeyboardRow {
                Key {
                    key: 0x0424
                    text: "ф"
                }
                Key {
                    key: 0x042B
                    text: "ы"
                }
                Key {
                    key: 0x0412
                    text: "в"
                }
                Key {
                    key: 0x0410
                    text: "а"
                }
                Key {
                    key: 0x041F
                    text: "п"
                }
                Key {
                    key: 0x0420
                    text: "р"
                }
                Key {
                    key: 0x041E
                    text: "о"
                }
                Key {
                    key: 0x041B
                    text: "л"
                }
                Key {
                    key: 0x0414
                    text: "д"
                }
                Key {
                    key: 0x0416
                    text: "ж"
                }
                Key {
                    key: 0x042D
                    text: "э"
                }
            }
            KeyboardRow {
                ShiftKey {
                }
                Key {
                    key: 0x042F
                    text: "я"
                }
                Key {
                    key: 0x0427
                    text: "ч"
                }
                Key {
                    key: 0x0421
                    text: "с"
                }
                Key {
                    key: 0x041C
                    text: "м"
                }
                Key {
                    key: 0x0418
                    text: "и"
                }
                Key {
                    key: 0x0422
                    text: "т"
                }
                Key {
                    key: 0x042C
                    text: "ь"
                    alternativeKeys: "ьъ"
                }
                Key {
                    key: 0x0411
                    text: "б"
                }
                Key {
                    key: 0x042E
                    text: "ю"
                }
                BackspaceKey {
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
                    text: ","
                    smallText: "\u2699"
                    smallTextVisible: true
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
                    key: Qt.Key_Z
                    text: "z"
                    alternativeKeys: "zž"
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
                    key: Qt.Key_Y
                    text: "y"
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
                Key {
                    key: Qt.Key_Comma
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: ","
                    smallText: "\u2699"
                    smallTextVisible: true
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
                EnterKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
        }
    }
}
