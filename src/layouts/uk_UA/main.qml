// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components
import QtQuick.Layouts

KeyboardLayout {
    sharedLayouts: ['symbols']
    keyWeight: 160
    readonly property real normalKeyWidth: normalKey.width
    readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
    KeyboardRow {
        Key {
            text: "й"
        }
        Key {
            id: normalKey
            text: "ц"
        }
        Key {
            text: "у"
        }
        Key {
            text: "к"
        }
        Key {
            text: "е"
        }
        Key {
            text: "н"
        }
        Key {
            text: "г"
        }
        Key {
            text: "ш"
        }
        Key {
            text: "щ"
        }
        Key {
            text: "з"
        }
        Key {
            text: "х"
        }
        Key {
            text: "ї"
        }
    }
    KeyboardRow {
        KeyboardRow {
            Layout.preferredWidth: functionKeyWidth
            Layout.fillWidth: false
            FillerKey {
            }
            Key {
                text: "ф"
                weight: normalKeyWidth
                Layout.fillWidth: false
            }
        }
        Key {
            text: "і"
        }
        Key {
            text: "в"
        }
        Key {
            text: "а"
        }
        Key {
            text: "п"
        }
        Key {
            text: "р"
        }
        Key {
            text: "о"
        }
        Key {
            text: "л"
        }
        Key {
            text: "д"
        }
        Key {
            text: "ж"
        }
        KeyboardRow {
            Layout.preferredWidth: functionKeyWidth
            Layout.fillWidth: false
            Key {
                text: "є"
                weight: normalKeyWidth
                Layout.fillWidth: false
            }
            FillerKey {
            }
        }
    }
    KeyboardRow {
        ShiftKey {
        }
        Key {
            text: "ґ"
        }
        Key {
            text: "я"
            alternativeKeys: "$¢я₴€¥£"
            smallTextVisible: true
        }
        Key {
            text: "ч"
        }
        Key {
            text: "с"
        }
        Key {
            text: "м"
        }
        Key {
            text: "и"
        }
        Key {
            text: "т"
        }
        Key {
            text: "ь"
        }
        Key {
            text: "б"
        }
        Key {
            text: "ю"
        }
        BackspaceKey {
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
            text: ","
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
            alternativeKeys: "!.?"
            smallText: "!?"
            smallTextVisible: true
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
