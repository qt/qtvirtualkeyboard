// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components

KeyboardLayout {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; PinyinInputMethod {}', parent, "main.qml")
    }
    sharedLayouts: ['symbols']
    smallTextVisible: true
    inputMode: InputEngine.InputMode.Pinyin
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
            FillerKey {}
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
                Key {
                    enabled: InputContext.preeditText.length > 0
                    key: Qt.Key_Apostrophe
                    text: "'"
                    displayText: "词"
                    smallText: "1"
                    alternativeKeys: "'1"
                }
                Key {
                    key: Qt.Key_2
                    text: "a"
                    displayText: "ABC"
                    smallText: "2"
                    alternativeKeys: "abc2"
                }
                Key {
                    key: Qt.Key_3
                    text: "d"
                    displayText: "DEF"
                    smallText: "3"
                    alternativeKeys: "def3"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_4
                    text: "g"
                    displayText: "GHI"
                    smallText: "4"
                    alternativeKeys: "ghi4"
                }
                Key {
                    key: Qt.Key_5
                    text: "j"
                    displayText: "JKL"
                    smallText: "5"
                    alternativeKeys: "jkl5"
                }
                Key {
                    key: Qt.Key_6
                    text: "m"
                    displayText: "MNO"
                    smallText: "6"
                    alternativeKeys: "mno6"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_7
                    text: "p"
                    displayText: "PQRS"
                    smallText: "7"
                    alternativeKeys: "pqrs7"
                }
                Key {
                    key: Qt.Key_8
                    text: "t"
                    displayText: "TUV"
                    smallText: "8"
                    alternativeKeys: "tuv8"
                }
                Key {
                    key: Qt.Key_9
                    text: "w"
                    displayText: "WXYZ"
                    smallText: "9"
                    alternativeKeys: "wxyz9"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_Comma
                    text: "\u3001"
                    smallText: "\u2699"
                    smallTextVisible: keyboard.isFunctionPopupListAvailable()
                }
                Key {
                    key: Qt.Key_0
                    text: "，"
                    alternativeKeys: "，；0"
                    smallText: "0"
                }
                Key {
                    text: "。"
                    alternativeKeys: "。？！："
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
