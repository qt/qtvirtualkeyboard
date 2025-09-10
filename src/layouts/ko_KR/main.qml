// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components
import QtQuick.Layouts

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; HangulInputMethod {}', parent, "inputMethod.qml")
    }
    sourceComponent: InputContext.shiftActive ? page2 : page1
    sharedLayouts: ['symbols']
    Component {
        id: page1
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    text: "\u3142"
                    alternativeKeys: "\u3142\u3143"
                }
                Key {
                    id: normalKey
                    text: "\u3148"
                    alternativeKeys: "\u3148\u3149"
                }
                Key {
                    text: "\u3137"
                    alternativeKeys: "\u3137\u3138"
                }
                Key {
                    text: "\u3131"
                    alternativeKeys: "\u3131\u3132"
                }
                Key {
                    text: "\u3145"
                    alternativeKeys: "\u3145\u3146"
                }
                Key {
                    text: "\u315B"
                }
                Key {
                    text: "\u3155"
                }
                Key {
                    text: "\u3151"
                }
                Key {
                    text: "\u3150"
                    alternativeKeys: "\u3150\u3152"
                }
                Key {
                    text: "\u3154"
                    alternativeKeys: "\u3154\u3156"
                }
            }
            KeyboardRow {
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    FillerKey {
                    }
                    Key {
                        text: "\u3141"
                        weight: normalKeyWidth
                        Layout.fillWidth: false
                    }
                }
                Key {
                    text: "\u3134"
                }
                Key {
                    text: "\u3147"
                }
                Key {
                    text: "\u3139"
                }
                Key {
                    text: "\u314E"
                }
                Key {
                    text: "\u3157"
                }
                Key {
                    text: "\u3153"
                }
                Key {
                    text: "\u314F"
                }
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    Key {
                        text: "\u3163"
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
                    text: "\u314B"
                }
                Key {
                    text: "\u314C"
                }
                Key {
                    text: "\u314A"
                }
                Key {
                    text: "\u314D"
                }
                Key {
                    text: "\u3160"
                }
                Key {
                    text: "\u315C"
                }
                Key {
                    text: "\u3161"
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
                Key {
                    text: "\u3143"
                }
                Key {
                    id: normalKey
                    text: "\u3149"
                }
                Key {
                    text: "\u3138"
                }
                Key {
                    text: "\u3132"
                }
                Key {
                    text: "\u3146"
                }
                Key {
                    text: "\u315B"
                }
                Key {
                    text: "\u3155"
                }
                Key {
                    text: "\u3151"
                }
                Key {
                    text: "\u3152"
                }
                Key {
                    text: "\u3156"
                }
            }
            KeyboardRow {
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    FillerKey {
                    }
                    Key {
                        text: "\u3141"
                        weight: normalKeyWidth
                        Layout.fillWidth: false
                    }
                }
                Key {
                    text: "\u3134"
                }
                Key {
                    text: "\u3147"
                }
                Key {
                    text: "\u3139"
                }
                Key {
                    text: "\u314E"
                }
                Key {
                    text: "\u3157"
                }
                Key {
                    text: "\u3153"
                }
                Key {
                    text: "\u314F"
                }
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    Key {
                        text: "\u3163"
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
                    text: "\u314B"
                }
                Key {
                    text: "\u314C"
                }
                Key {
                    text: "\u314A"
                }
                Key {
                    text: "\u314D"
                }
                Key {
                    text: "\u3160"
                }
                Key {
                    text: "\u315C"
                }
                Key {
                    text: "\u3161"
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
