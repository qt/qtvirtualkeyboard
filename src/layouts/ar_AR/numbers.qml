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
                    key: Qt.Key_Period
                    text: "."
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
                    key: 0x0667
                    text: "\u0667"
                    alternativeKeys: "\u06677"
                }
                Key {
                    key: 0x0668
                    text: "\u0668"
                    alternativeKeys: "\u06688"
                }
                Key {
                    key: 0x0669
                    text: "\u0669"
                    alternativeKeys: "\u06699"
                }
                BackspaceKey {}
            }
            KeyboardRow {
                Key {
                    key: 0x0664
                    text: "\u0664"
                    alternativeKeys: "\u06644"
                }
                Key {
                    key: 0x0665
                    text: "\u0665"
                    alternativeKeys: "\u06655"
                }
                Key {
                    key: 0x0666
                    text: "\u0666"
                    alternativeKeys: "\u06666"
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
                    key: 0x0661
                    text: "\u0661"
                    alternativeKeys: "\u06611"
                }
                Key {
                    key: 0x0662
                    text: "\u0662"
                    alternativeKeys: "\u06622"
                }
                Key {
                    key: 0x0663
                    text: "\u0663"
                    alternativeKeys: "\u06633"
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
                    key: 0x0660
                    text: "\u0660"
                    alternativeKeys: "\u06600"
                }
                Key {
                    key: Qt.Key_Comma
                    text: "\u066B"
                    alternativeKeys: "\u066B,."
                }
                EnterKey {}
            }
        }
    }
}
