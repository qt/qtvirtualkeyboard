// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components

KeyboardLayout {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; HandwritingInputMethod {}', parent)
    }
    sharedLayouts: ['symbols']

    KeyboardRow {
        Layout.preferredHeight: 3
        TraceInputKey {
            objectName: "hwrInputArea"
            patternRecognitionMode: InputEngine.PatternRecognitionMode.Handwriting
            horizontalRulers:
                InputContext.inputEngine.inputMode !== InputEngine.InputMode.Thai ? [] :
                    [Math.round(boundingBox.height / 4), Math.round(boundingBox.height / 4) * 3]
        }
    }
    KeyboardRow {
        id: bottomRow
        Layout.preferredHeight: 1
        keyWeight: 160
        ShiftKey {
            weight: 240
        }
        InputModeKey {
        }
        Key {
            key: Qt.Key_Comma
            text: ","
            smallText: "\u2699"
            smallTextVisible: true
            highlighted: true
        }
        SpaceKey {
            weight: 10 * 160 - 4 * 160 - 2 * 240
        }
        Key {
            key: Qt.Key_Period
            text: "."
            alternativeKeys: "<>()/\\\"'=+-_:;.?!"
            smallText: "!?"
            smallTextVisible: true
            highlighted: true
        }
        BackspaceKey {
        }
        EnterKey {
            weight: 240
        }
    }
}
