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
    inputMode: preferredInputMode()

    Connections {
        target: InputContext
        function onInputMethodHintsChanged() {
            var newInputMode = preferredInputMode()
            if (InputContext.inputEngine.inputModes.indexOf(newInputMode) !== -1)
                InputContext.inputEngine.inputMode = newInputMode
        }
    }

    function preferredInputMode() {
        return InputContext.inputMethodHints &
                (Qt.ImhPreferLatin | Qt.ImhEmailCharactersOnly | Qt.ImhUrlCharactersOnly |
                 Qt.ImhLatinOnly) ? InputEngine.InputMode.Latin : InputEngine.InputMode.KoreanHandwriting
    }

    KeyboardRow {
        KeyboardColumn {
            Layout.preferredWidth: 1
            InputModeKey {
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
                    InputContext.inputEngine.inputMode !== InputEngine.InputMode.KoreanHandwriting ? [] :
                        [Math.round(boundingBox.height / 4), Math.round(boundingBox.height / 4) * 2, Math.round(boundingBox.height / 4) * 3]
            }
        }
        KeyboardColumn {
            Layout.preferredWidth: 1
            Key {
                key: Qt.Key_Period
                text: "."
                alternativeKeys: "<>()/\\\"'=+-_:;,.?! "
                smallText: "!?"
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
