// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components
import QtQuick.Layouts

KeyboardLayout {
    inputMode: InputEngine.InputMode.Arabic
    keyWeight: 160
    smallTextVisible: true
    readonly property real normalKeyWidth: normalKey.width
    readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
    KeyboardRow {
        Key {
            text: "\u0636"
            alternativeKeys: "1\u0636\u0661"
        }
        Key {
            id: normalKey
            text: "\u0635"
            alternativeKeys: "2\u0635\u0662"
        }
        Key {
            text: "\u062B"
            alternativeKeys: "3\u062B\u0663"
        }
        Key {
            text: "\u0642"
            alternativeKeys: "4\u0642\u0664"
        }
        Key {
            text: "\u0641"
            alternativeKeys: "5\u0641\u0665"
        }
        Key {
            text: "\u063A"
            alternativeKeys: "6\u063A\u0666"
        }
        Key {
            text: "\u0639"
            alternativeKeys: "7\u0639\u0667"
        }
        Key {
            text: "\u0647"
            alternativeKeys: "8\u0647\u0668"
        }
        Key {
            text: "\u062E"
            alternativeKeys: "9\u062E\u0669"
        }
        Key {
            text: "\u062D"
            alternativeKeys: "0\u062D\u0660"
        }
        Key {
            text: "\u062C"
            alternativeKeys: "\u062C\u0686"
        }
        Key {
            text: "\u062F"
            alternativeKeys: "\u062F\uFDFC"
        }
    }
    KeyboardRow {
        KeyboardRow {
            Layout.preferredWidth: functionKeyWidth
            Layout.fillWidth: false
            FillerKey {
            }
            Key {
                text: "\u0634"
                weight: normalKeyWidth
                Layout.fillWidth: false
            }
        }
        Key {
            text: "\u0633"
        }
        Key {
            text: "\u064A"
        }
        Key {
            text: "\u0628"
            alternativeKeys: "\u0628\u067E"
        }
        Key {
            text: "\u0644"
            alternativeKeys: ["\u0644\u0623", "\u0644\u0622", "\u0644", "\u0644\u0627", "\u0644\u0625"]
        }
        Key {
            text: "\u0627"
            alternativeKeys: "\u0625\u0627\u0623\u0622"
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
            alternativeKeys: "\u0643\u06AF"
        }
        KeyboardRow {
            Layout.preferredWidth: functionKeyWidth
            Layout.fillWidth: false
            Key {
                text: "\u0630"
                weight: normalKeyWidth
                Layout.fillWidth: false
            }
            FillerKey {
            }
        }
    }
    KeyboardRow {
        KeyboardRow {
            Layout.preferredWidth: functionKeyWidth
            Layout.fillWidth: false
            FillerKey {
            }
            Key {
                text: "\u0626"
                weight: normalKeyWidth
                Layout.fillWidth: false
            }
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
            text: "\u0637"
        }
        Key {
            text: "\u0638"
            alternativeKeys: "\u064E\u064C\u0650\u064D\u0651\u0652\u0670\u0653\u0640\u0638\u064B\u064F"
            smallText: "\u25CC\u0650 "
        }
        BackspaceKey {
            weight: functionKeyWidth
            Layout.fillWidth: false
        }
    }
    KeyboardRow {
        SymbolModeKey {
            displayText: "\u0661\u0662\u0663\u061F"
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
            text: "\u060C"
            smallText: "\u2699"
            smallTextVisible: keyboard.isFunctionPopupListAvailable()
            highlighted: true
        }
        SpaceKey {
        }
        Key {
            key: Qt.Key_Period
            weight: normalKeyWidth
            Layout.fillWidth: false
            text: "."
            alternativeKeys: "!,\u060C\u061B.\u061F"
            highlighted: true
        }
        HideKeyboardKey {
            weight: normalKeyWidth
            Layout.fillWidth: false
        }
        EnterKey {
            weight: functionKeyWidth
            Layout.fillWidth: false
        }
    }
}
