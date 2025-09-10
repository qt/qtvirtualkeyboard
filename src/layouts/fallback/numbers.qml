// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components
import QtQuick.VirtualKeyboard.Plugins

KeyboardLayout {
    inputMethod: PlainInputMethod {}
    inputMode: InputEngine.InputMode.Numeric

    KeyboardRow {
        Layout.fillWidth: false
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignHCenter
        KeyboardColumn {
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.preferredWidth: parent.height / 4 * 3
            KeyboardRow {
                Key {
                    key: Qt.Key_ParenLeft
                    text: "("
                }
                Key {
                    key: Qt.Key_ParenRight
                    text: ")"
                }
                Key {
                    key: Qt.Key_Comma
                    text: ","
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_division
                    text: "\u00F7"
                }
                Key {
                    key: Qt.Key_multiply
                    text: "\u00D7"
                }
                Key {
                    key: Qt.Key_Plus
                    text: "+"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_AsciiCircum
                    text: "^"
                }
                Key {
                    key: Qt.Key_Slash
                    text: "/"
                }
                Key {
                    key: Qt.Key_Minus
                    text: "-"
                }
            }
            KeyboardRow {
                Key {
                    key: 0x221A
                    text: "√"
                }
                Key {
                    key: Qt.Key_Percent
                    text: "%"
                }
                Key {
                    key: Qt.Key_Asterisk
                    text: "*"
                }
            }
        }
        KeyboardColumn {
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.preferredWidth: parent.height / 8
            KeyboardRow {
                FillerKey {}
            }
        }
        KeyboardColumn {
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.preferredWidth: parent.height
            KeyboardRow {
                Key {
                    key: Qt.Key_7
                    text: "7"
                }
                Key {
                    key: Qt.Key_8
                    text: "8"
                }
                Key {
                    key: Qt.Key_9
                    text: "9"
                }
                BackspaceKey {}
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_4
                    text: "4"
                }
                Key {
                    key: Qt.Key_5
                    text: "5"
                }
                Key {
                    key: Qt.Key_6
                    text: "6"
                }
                Key {
                    text: " "
                    displayText: "\u2423"
                    repeat: true
                    showPreview: false
                    key: Qt.Key_Space
                    highlighted: true
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_1
                    text: "1"
                }
                Key {
                    key: Qt.Key_2
                    text: "2"
                }
                Key {
                    key: Qt.Key_3
                    text: "3"
                }
                HideKeyboardKey {
                    visible: true
                }
            }
            KeyboardRow {
                ChangeLanguageKey {
                    customLayoutsOnly: true
                    visible: true
                }
                Key {
                    key: Qt.Key_0
                    text: "0"
                }
                Key {
                    key: Qt.Key_Period
                    text: "."
                    alternativeKeys: ".,"
                }
                EnterKey {}
            }
        }
    }
}
