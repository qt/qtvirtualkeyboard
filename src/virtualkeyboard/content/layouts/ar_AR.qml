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
import "../components"

KeyboardLayout {
    keyWeight: 160
    property var keys: ["ضصثقفغعهخحجد", "شسيبلاتنمكط", "ئءؤرلىةوزظ"]
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
        Repeater {
            model: keys[2].length
            Key {
                text: keys[2][index]
            }
        }
        Key {
            key: Qt.Key_Comma
            text: ","
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
        }
        ChangeLanguageKey {
            weight: 154
        }
        SpaceKey {
            weight: 864
        }
        Key {
            key: Qt.Key_Apostrophe
            text: "'"
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
