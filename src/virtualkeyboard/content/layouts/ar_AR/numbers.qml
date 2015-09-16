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
                HideKeyboardKey {}
            }
            KeyboardRow {
                ChangeLanguageKey {
                    customLayoutsOnly: true
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
