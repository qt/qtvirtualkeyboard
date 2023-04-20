// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components

KeyboardLayout {
    keyWeight: 160
    readonly property real normalKeyWidth: normalKey.width
    readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; CangjieInputMethod {}', parent, "main.qml")
    }
    sharedLayouts: ['symbols']
    smallTextVisible: true
    inputMode: InputEngine.InputMode.Cangjie
    KeyboardRow {
        Key {
            text: "\u624B"
        }
        Key {
            id: normalKey
            text: "\u7530"
        }
        Key {
            text: "\u6C34"
        }
        Key {
            text: "\u53E3"
        }
        Key {
            text: "\u5EFF"
        }
        Key {
            text: "\u535C"
        }
        Key {
            text: "\u5C71"
        }
        Key {
            text: "\u6208"
        }
        Key {
            text: "\u4EBA"
        }
        Key {
            text: "\u5FC3"
        }
    }
    KeyboardRow {
        KeyboardRow {
            Layout.preferredWidth: functionKeyWidth
            Layout.fillWidth: false
            FillerKey {
            }
            Key {
                text: "\u65E5"
                weight: normalKeyWidth
                Layout.fillWidth: false
            }
        }
        Key {
            text: "\u5C38"
        }
        Key {
            text: "\u6728"
        }
        Key {
            text: "\u706B"
        }
        Key {
            text: "\u571F"
        }
        Key {
            text: "\u7AF9"
        }
        Key {
            text: "\u5341"
        }
        Key {
            text: "\u5927"
        }
        KeyboardRow {
            Layout.preferredWidth: functionKeyWidth
            Layout.fillWidth: false
            Key {
                text: "\u4E2D"
                weight: normalKeyWidth
                Layout.fillWidth: false
            }
            FillerKey {
            }
        }
    }
    KeyboardRow {
        ShiftKey {
            weight: functionKeyWidth
            Layout.fillWidth: false
        }
        Key {
            text: "\u91CD"
        }
        Key {
            text: "\u96E3"
        }
        Key {
            text: "\u91D1"
        }
        Key {
            text: "\u5973"
        }
        Key {
            text: "\u6708"
        }
        Key {
            text: "\u5F13"
        }
        Key {
            text: "\u4E00"
        }
        BackspaceKey {
            weight: functionKeyWidth
            Layout.fillWidth: false
        }
    }
    KeyboardRow {
        SymbolModeKey {
            weight: functionKeyWidth
            Layout.fillWidth: false
        }
        ChangeLanguageKey {
            weight: normalKeyWidth
            Layout.fillWidth: false
        }
        Key {
            key: Qt.Key_Comma
            weight: normalKeyWidth
            Layout.fillWidth: false
            text: "\uFF0C"
            smallText: "\u2699"
            smallTextVisible: keyboard.isFunctionPopupListAvailable()
            highlighted: true
        }
        InputModeKey {
            visible: InputContext.inputEngine.inputModes.indexOf(InputEngine.InputMode.Zhuyin) !== -1
            weight: normalKeyWidth
            Layout.fillWidth: false
        }
        SpaceKey {
        }
        Key {
            key: Qt.Key_Period
            weight: normalKeyWidth
            Layout.fillWidth: false
            text: "\uFF0E"
            alternativeKeys: "\uFF1B\u3001\uFF0E\uFF1A\u3002？！"
            smallText: "!?"
            smallTextVisible: true
            highlighted: true
        }
        EnterKey {
            weight: functionKeyWidth
            Layout.fillWidth: false
        }
    }
}
