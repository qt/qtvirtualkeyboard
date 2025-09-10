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
            key: 0x0419
            text: "й"
        }
        Key {
            id: normalKey
            key: 0x0426
            text: "ц"
        }
        Key {
            key: 0x0423
            text: "у"
        }
        Key {
            key: 0x041A
            text: "к"
        }
        Key {
            key: 0x0415
            text: "е"
            alternativeKeys: "её"
        }
        Key {
            key: 0x041D
            text: "н"
        }
        Key {
            key: 0x0413
            text: "г"
        }
        Key {
            key: 0x0428
            text: "ш"
        }
        Key {
            key: 0x0429
            text: "щ"
        }
        Key {
            key: 0x0417
            text: "з"
        }
        Key {
            key: 0x0425
            text: "х"
        }
    }
    KeyboardRow {
        Key {
            key: 0x0424
            text: "ф"
        }
        Key {
            key: 0x042B
            text: "ы"
        }
        Key {
            key: 0x0412
            text: "в"
        }
        Key {
            key: 0x0410
            text: "а"
        }
        Key {
            key: 0x041F
            text: "п"
        }
        Key {
            key: 0x0420
            text: "р"
        }
        Key {
            key: 0x041E
            text: "о"
        }
        Key {
            key: 0x041B
            text: "л"
        }
        Key {
            key: 0x0414
            text: "д"
        }
        Key {
            key: 0x0416
            text: "ж"
        }
        Key {
            key: 0x042D
            text: "э"
        }
    }
    KeyboardRow {
        ShiftKey {
        }
        Key {
            key: 0x042F
            text: "я"
        }
        Key {
            key: 0x0427
            text: "ч"
        }
        Key {
            key: 0x0421
            text: "с"
        }
        Key {
            key: 0x041C
            text: "м"
        }
        Key {
            key: 0x0418
            text: "и"
        }
        Key {
            key: 0x0422
            text: "т"
        }
        Key {
            key: 0x042C
            text: "ь"
            alternativeKeys: "ьъ"
        }
        Key {
            key: 0x0411
            text: "б"
        }
        Key {
            key: 0x042E
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
