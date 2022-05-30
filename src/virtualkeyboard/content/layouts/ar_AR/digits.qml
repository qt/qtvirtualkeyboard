/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Plugins

KeyboardLayout {
    inputMethod: PlainInputMethod {}
    inputMode: InputEngine.InputMode.Numeric

    KeyboardColumn {
        Layout.fillWidth: false
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignHCenter
        Layout.preferredWidth: height
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
