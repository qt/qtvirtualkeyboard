/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Enterprise.VirtualKeyboard 1.3

KeyboardLayout {
    inputMethod: PlainInputMethod {}
    inputMode: InputEngine.Numeric

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
                HideKeyboardKey {}
            }
            KeyboardRow {
                ChangeLanguageKey {
                    customLayoutsOnly: true
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
