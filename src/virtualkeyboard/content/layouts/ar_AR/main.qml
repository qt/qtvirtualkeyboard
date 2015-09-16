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
import QtQuick.Enterprise.VirtualKeyboard 1.3

KeyboardLayoutLoader {
    inputMode: InputEngine.Latin
    sourceComponent: InputContext.shift ? page2 : page1
    Component {
        id: page1
        KeyboardLayout {
            keyWeight: 160
            KeyboardRow {
                Key {
                    text: "\u0636"
                }
                Key {
                    text: "\u0635"
                }
                Key {
                    text: "\u062B"
                }
                Key {
                    text: "\u0642"
                }
                Key {
                    text: "\u0641"
                }
                Key {
                    text: "\u063A"
                }
                Key {
                    text: "\u0639"
                }
                Key {
                    text: "\u0647"
                }
                Key {
                    text: "\u062E"
                }
                Key {
                    text: "\u062D"
                }
                Key {
                    text: "\u062C"
                }
                Key {
                    text: "\u062F"
                }
                BackspaceKey {}
            }
            KeyboardRow {
                FillerKey {
                    weight: 56
                }
                Key {
                    text: "\u0634"
                }
                Key {
                    text: "\u0633"
                }
                Key {
                    text: "\u064A"
                }
                Key {
                    text: "\u0628"
                }
                Key {
                    text: "\u0644"
                }
                Key {
                    text: "\u0627"
                }
                Key {
                    text: "\u062A"
                }
                Key {
                    text: "\u0646"
                }
                Key {
                    text: "\u0645"
                }
                Key {
                    text: "\u0643"
                }
                Key {
                    text: "\u0637"
                }
                EnterKey {
                    weight: 283
                }
            }
            KeyboardRow {
                keyWeight: 156
                ShiftKey {}
                Key {
                    text: "\u0626"
                }
                Key {
                    text: "\u0621"
                }
                Key {
                    text: "\u0624"
                }
                Key {
                    text: "\u0631"
                }
                Key {
                    text: "\u0644\u0627"
                }
                Key {
                    text: "\u0649"
                }
                Key {
                    text: "\u0629"
                }
                Key {
                    text: "\u0648"
                }
                Key {
                    text: "\u0632"
                }
                Key {
                    text: "\u0638"
                }
                ShiftKey {
                    weight: 264
                }
            }
            KeyboardRow {
                keyWeight: 154
                SymbolModeKey {
                    weight: 217
                    displayText: "\u0661\u0662\u0663\u061F"
                }
                ChangeLanguageKey {
                    weight: 154
                }
                SpaceKey {
                    weight: 864
                }
                Key {
                    key: 0x060C
                    text: "\u060C"
                    alternativeKeys: ".,\u060C\u061F"
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
    }
    Component {
        id: page2
        KeyboardLayout {
            keyWeight: 160
            KeyboardRow {
                Key {
                    text: "\u064E"
                }
                Key {
                    text: "\u064B"
                }
                Key {
                    text: "\u064F"
                }
                Key {
                    text: "\u064C"
                }
                Key {
                    text: "\uFEF9"
                }
                Key {
                    text: "\u0625"
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    text: "\u0630"
                }
                BackspaceKey {}
            }
            KeyboardRow {
                FillerKey {
                    weight: 56
                }
                Key {
                    text: "\u0650"
                }
                Key {
                    text: "\u064D"
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    text: "\u0644\u0623"
                }
                Key {
                    text: "\u0623"
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                EnterKey {
                    weight: 283
                }
            }
            KeyboardRow {
                keyWeight: 156
                ShiftKey {}
                Key {
                    enabled: false
                }
                Key {
                    text: "\u0652"
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    text: "\u0644\u0622"
                }
                Key {
                    text: "\u0622"
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                Key {
                    enabled: false
                }
                ShiftKey {
                    weight: 264
                }
            }
            KeyboardRow {
                keyWeight: 154
                SymbolModeKey {
                    weight: 217
                    displayText: "\u0661\u0662\u0663\u061F"
                }
                ChangeLanguageKey {
                    weight: 154
                }
                SpaceKey {
                    weight: 864
                }
                Key {
                    key: 0x061F
                    text: "\u061F"
                    alternativeKeys: ".,\u060C\u061F"
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
    }
}
