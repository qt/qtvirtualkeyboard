/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 1.0

KeyboardLayout {
    keyWeight: 160
    property var keys: ["ضصثقفغعهخحجد", "شسيبلاتنمكط"]
    KeyboardRow {
        Repeater {
            model: keys[0].length
            Key {
                text: keys[0][index]
            }
        }
        BackspaceKey {}
    }
    KeyboardRow {
        FillerKey {
            weight: 56
        }
        Repeater {
            model: keys[1].length
            Key {
                text: keys[1][index]
            }
        }
        EnterKey {
            weight: 283
        }
    }
    KeyboardRow {
        keyWeight: 156
        FillerKey {}
        Key {
            text: "ئ"
        }
        Key {
            text: "ء"
        }
        Key {
            text: "ؤ"
        }
        Key {
            text: "ر"
        }
        Key {
            text: "لا"
        }
        Key {
            text: "ى"
        }
        Key {
            text: "ة"
        }
        Key {
            text: "و"
        }
        Key {
            text: "ز"
        }
        Key {
            text: "ظ"
        }
        Key {
            key: 0x060C
            text: "\u060C"
            alternativeKeys: "\u060C,"
        }
        Key {
            key: Qt.Key_Period
            text: "."
        }
        FillerKey {
            weight: 204
        }
    }
    KeyboardRow {
        keyWeight: 154
        SymbolModeKey {
            weight: 217
            displayText: "\u061F\u0663\u0662\u0661"
        }
        ChangeLanguageKey {
            weight: 154
        }
        SpaceKey {
            weight: 864
        }
        Key {
            key: 0x064B
            text: "\u064B"
            alternativeKeys: "\u0656\u0670\u0653\u0650\u064F\u064E\u0640\u0655\u0654\u0652\u064D\u064C\u064B\u0651"
        }
        Key {
            key: 0xE000
            text: ":-)"
            alternativeKeys: [ ";-)", ":-)", ":-D", ":-(", "<3" ]
        }
        HideKeyboardKey {
            weight: 204
        }
    }
}
