// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components

KeyboardLayoutLoader {
    inputMode: InputEngine.InputMode.Latin
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; ThaiInputMethod {}', parent, "inputMethod.qml")
    }
    sharedLayouts: [ "symbols" ]
    sourceComponent: InputContext.shiftActive ? page2 : page1
    Component {
        id: page1
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Layout.preferredHeight: 3
                smallTextVisible: true
                KeyboardColumn {
                    KeyboardRow {
                        Key {
                            text: "ๅ"
                            alternativeKeys: "ๅ1๑"
                        }
                        Key {
                            id: normalKey
                            text: "/"
                            alternativeKeys: "/2๒"
                        }
                        Key {
                            text: "_"
                            alternativeKeys: "_3๓"
                        }
                        Key {
                            text: "ภ"
                            alternativeKeys: "ภ4๔"
                        }
                        Key {
                            text: "ถ"
                            alternativeKeys: "ถ5๕"
                        }
                        Key {
                            text: "\u0E38"
                            displayText: " \u0E38"
                            alternativeKeys: [ "\u0E38", " \u0E39" ]
                        }
                        Key {
                            text: "\u0E36"
                            displayText: " \u0E36"
                        }
                        Key {
                            text: "ค"
                            alternativeKeys: "ค6๖"
                        }
                        Key {
                            text: "ต"
                            alternativeKeys: "ต7๗"
                        }
                        Key {
                            text: "จ"
                            alternativeKeys: "จ8๘"
                        }
                        Key {
                            text: "ข"
                            alternativeKeys: "๙ข9"
                        }
                        Key {
                            text: "ช"
                            alternativeKeys: "๐ช0"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "ๆ"
                        }
                        Key {
                            text: "ไ"
                            alternativeKeys: "ไ\""
                        }
                        Key {
                            text: " ำ"
                            alternativeKeys: " ำฎ"
                        }
                        Key {
                            text: "พ"
                            alternativeKeys: "พฑ"
                        }
                        Key {
                            text: "ะ"
                            alternativeKeys: "ะธ"
                        }
                        Key {
                            text: "\u0E31"
                            displayText: " \u0E31"
                            alternativeKeys: "\u0E31。"
                        }
                        Key {
                            text: "\u0E35"
                            displayText: " \u0E35"
                            alternativeKeys: [ "\u0E35", " \u0E4A" ]
                        }
                        Key {
                            text: "ร"
                            alternativeKeys: "รณ"
                        }
                        Key {
                            text: "น"
                            alternativeKeys: "นฯ"
                        }
                        Key {
                            text: "ย"
                            alternativeKeys: "ยญ"
                        }
                        Key {
                            text: "บ"
                            alternativeKeys: "บฐ"
                        }
                        Key {
                            text: "ล"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "ฟ"
                            alternativeKeys: "ฟฤ"
                        }
                        Key {
                            text: "ห"
                            alternativeKeys: "หฆ"
                        }
                        Key {
                            text: "ก"
                            alternativeKeys: "กฏ"
                        }
                        Key {
                            text: "ด"
                            alternativeKeys: "ดโ"
                        }
                        Key {
                            text: "เ"
                            alternativeKeys: "เฌ"
                        }
                        Key {
                            text: "\u0E49"
                            displayText: " \u0E49"
                            alternativeKeys: [ "\u0E49", " \u0E47" ]
                        }
                        Key {
                            text: "\u0E48"
                            displayText: " \u0E48"
                            alternativeKeys: [ "\u0E48", " \u0E4B" ]
                        }
                        Key {
                            text: "า"
                            alternativeKeys: "าษ"
                        }
                        Key {
                            text: "ส"
                            alternativeKeys: "สศ"
                        }
                        Key {
                            text: "ว"
                        }
                        Key {
                            text: "ง"
                        }
                        Key {
                            text: "ซ"
                        }
                    }
                    KeyboardRow {
                        ShiftKey {
                        }
                        Key {
                            text: "ผ"
                        }
                        Key {
                            text: "ป"
                        }
                        Key {
                            text: "แ"
                            alternativeKeys: "แฉ"
                        }
                        Key {
                            text: "อ"
                            alternativeKeys: "อฮ"
                        }
                        Key {
                            text: "\u0E34"
                            displayText: " \u0E34"
                            alternativeKeys: [ "\u0E34", " \u0E3A" ]
                        }
                        Key {
                            text: "\u0E37"
                            displayText: " \u0E37"
                            alternativeKeys: [ "\u0E37", " \u0E4C" ]
                        }
                        Key {
                            text: "ท"
                        }
                        Key {
                            text: "ม"
                            alternativeKeys: "มฒ"
                        }
                        Key {
                            text: "ใ"
                            alternativeKeys: "ใฬ"
                        }
                        Key {
                            text: "ฝ"
                            alternativeKeys: "ฝฦ"
                        }
                        BackspaceKey {
                        }
                    }
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
        id: page2
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Layout.preferredHeight: 3
                smallTextVisible: true
                KeyboardColumn {
                    KeyboardRow {
                        Key {
                            text: "+"
                        }
                        Key {
                            id: normalKey
                            text: "๑"
                        }
                        Key {
                            text: "๒"
                        }
                        Key {
                            text: "๓"
                        }
                        Key {
                            text: "๔"
                        }
                        Key {
                            text: "\u0E39"
                            displayText: " \u0E39"
                        }
                        Key {
                            text: "฿"
                        }
                        Key {
                            text: "๕"
                        }
                        Key {
                            text: "๖"
                        }
                        Key {
                            text: "๗"
                        }
                        Key {
                            text: "๘"
                        }
                        Key {
                            text: "๙"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "๐"
                        }
                        Key {
                            text: "\""
                        }
                        Key {
                            text: "ฎ"
                        }
                        Key {
                            text: "ฑ"
                        }
                        Key {
                            text: "ธ"
                        }
                        Key {
                            text: "。"
                        }
                        Key {
                            text: "\u0E4A"
                            displayText: " \u0E4A"
                        }
                        Key {
                            text: "ณ"
                        }
                        Key {
                            text: "ฯ"
                        }
                        Key {
                            text: "ญ"
                        }
                        Key {
                            text: "ฐ"
                        }
                        Key {
                            text: ","
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "ฤ"
                        }
                        Key {
                            text: "ฆ"
                        }
                        Key {
                            text: "ฏ"
                        }
                        Key {
                            text: "โ"
                        }
                        Key {
                            text: "ฌ"
                        }
                        Key {
                            text: "\u0E47"
                            displayText: " \u0E47"
                        }
                        Key {
                            text: "\u0E4B"
                            displayText: " \u0E4B"
                        }
                        Key {
                            text: "ษ"
                        }
                        Key {
                            text: "ศ"
                        }
                        Key {
                            text: "ซ"
                        }
                        Key {
                            text: "."
                        }
                        Key {
                            text: "ฅ"
                        }
                    }
                    KeyboardRow {
                        ShiftKey {
                        }
                        Key {
                            text: "("
                        }
                        Key {
                            text: ")"
                        }
                        Key {
                            text: "ฉ"
                        }
                        Key {
                            text: "ฮ"
                        }
                        Key {
                            text: "\u0E3A"
                            displayText: " \u0E3A"
                        }
                        Key {
                            text: "\u0E4C"
                            displayText: " \u0E4C"
                        }
                        Key {
                            text: "?"
                        }
                        Key {
                            text: "ฒ"
                        }
                        Key {
                            text: "ฬ"
                        }
                        Key {
                            text: "ฦ"
                        }
                        BackspaceKey {
                        }
                    }
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
