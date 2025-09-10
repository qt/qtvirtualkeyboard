// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components

KeyboardLayout {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; StrokeInputMethod {}', parent, "main.qml")
    }
    sharedLayouts: ['symbols']
    smallTextVisible: true
    inputMode: InputEngine.InputMode.Stroke
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
                    key: Qt.Key_1
                    text: "\u0001"
                    displayText: "\u4E00"
                    smallText: "1"
                    alternativeKeys: "\u00011"
                }
                Key {
                    key: Qt.Key_2
                    text: "\u0002"
                    displayText: "\u4E28"
                    smallText: "2"
                    alternativeKeys: "\u00022"
                }
                Key {
                    key: Qt.Key_3
                    text: "\u0003"
                    displayText: "\u4E3F"
                    smallText: "3"
                    alternativeKeys: "\u00033"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_4
                    text: "\u0004"
                    displayText: "\u4E36"
                    smallText: "4"
                    alternativeKeys: "\u00044"
                }
                Key {
                    key: Qt.Key_5
                    text: "\u0005"
                    displayText: "\u4E5B"
                    smallText: "5"
                    alternativeKeys: "\u00055"
                }
                Key {
                    key: Qt.Key_6
                    text: "\u0006"
                    displayText: "*"
                    smallText: "6"
                    alternativeKeys: "\u00066"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_7
                    text: "，"
                    smallText: "7"
                    alternativeKeys: "，7"
                }
                Key {
                    key: Qt.Key_8
                    text: "！"
                    smallText: "8"
                    alternativeKeys: "！8"
                }
                Key {
                    key: Qt.Key_9
                    text: "？"
                    smallText: "9"
                    alternativeKeys: "？9"
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
                    text: "；"
                    alternativeKeys: "；0"
                    smallText: "0"
                }
                Key {
                    text: "。"
                    alternativeKeys: "。："
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
