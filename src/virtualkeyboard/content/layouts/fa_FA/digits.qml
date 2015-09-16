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

    KeyboardColumn {
        Layout.fillWidth: false
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignHCenter
        Layout.preferredWidth: height
        KeyboardRow {
            Key {
                text: "\u06F7"
                alternativeKeys: "\u06F77"
            }
            Key {
                text: "\u06F8"
                alternativeKeys: "\u06F88"
            }
            Key {
                text: "\u06F9"
                alternativeKeys: "\u06F99"
            }
            BackspaceKey {}
        }
        KeyboardRow {
            Key {
                text: "\u06F4"
                alternativeKeys: "\u06F44"
            }
            Key {
                text: "\u06F5"
                alternativeKeys: "\u06F55"
            }
            Key {
                text: "\u06F6"
                alternativeKeys: "\u06F66"
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
                text: "\u06F1"
                alternativeKeys: "\u06F11"
            }
            Key {
                text: "\u06F2"
                alternativeKeys: "\u06F22"
            }
            Key {
                text: "\u06F3"
                alternativeKeys: "\u06F33"
            }
            HideKeyboardKey {}
        }
        KeyboardRow {
            ChangeLanguageKey {
                customLayoutsOnly: true
            }
            Key {
                text: "\u06F0"
                alternativeKeys: "\u06F00"
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
