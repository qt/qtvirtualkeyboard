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
    inputMode: InputEngine.InputMode.Arabic
    readonly property bool alphabeticInputMode: [InputEngine.InputMode.Latin, InputEngine.InputMode.Dialable].indexOf(InputContext.inputEngine.inputMode) !== -1

    KeyboardRow {
        KeyboardColumn {
            Layout.preferredWidth: 1
            InputModeKey {
                inputModeNameList: [
                    "ABC",  // InputEngine.InputMode.Latin
                    "\u0660\u0661\u0662",  // InputEngine.InputMode.Numeric
                    "123",  // InputEngine.InputMode.Dialable
                    "",  // InputEngine.InputMode.Pinyin
                    "",  // InputEngine.InputMode.Cangjie
                    "",  // InputEngine.InputMode.Zhuyin
                    "",  // InputEngine.InputMode.Hangul
                    "",  // InputEngine.InputMode.Hiragana
                    "",  // InputEngine.InputMode.Katakana
                    "",  // InputEngine.InputMode.FullwidthLatin
                    "",  // InputEngine.InputMode.Greek
                    "",  // InputEngine.InputMode.Cyrillic
                    "\u0623\u200C\u0628\u200C\u062C",  // InputEngine.InputMode.Arabic
                ]
            }
            ChangeLanguageKey {
                visible: true
            }
            ShiftKey {
            }
            HandwritingModeKey {
            }
        }
        KeyboardColumn {
            Layout.preferredWidth: 8
            TraceInputKey {
                objectName: "hwrInputArea"
                patternRecognitionMode: InputEngine.PatternRecognitionMode.Handwriting
                horizontalRulers:
                    alphabeticInputMode ? [] :
                        [Math.round(boundingBox.height / 4), Math.round(boundingBox.height / 4) * 2, Math.round(boundingBox.height / 4) * 3]
            }
        }
        KeyboardColumn {
            Layout.preferredWidth: 1
            Key {
                key: Qt.Key_Period
                text: "."
                alternativeKeys: alphabeticInputMode ? "#%&*/\\\"'=+-_:;,.?!<>() " : "#%&*/\\\"'=+-_:\u061B\u060C.\u061F!<>() "
                smallText: alphabeticInputMode ? "!?" : "\u061F!"
                smallTextVisible: true
                highlighted: true
            }
            HideKeyboardKey {
                visible: true
            }
            BackspaceKey {
            }
            EnterKey {
            }
        }
    }
}
