/****************************************************************************
**
** Copyright (C) 2015 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Enterprise.VirtualKeyboard 2.0

KeyboardLayout {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick 2.0; import QtQuick.Enterprise.VirtualKeyboard 2.0; HandwritingInputMethod {}', parent)
    }
    sharedLayouts: ['symbols']
    inputMode: InputEngine.Latin

    KeyboardRow {
        Layout.preferredHeight: 3
        KeyboardColumn {
            Layout.preferredWidth: bottomRow.width - hideKeyboardKey.width
            KeyboardRow {
                TraceInputKey {
                    objectName: "hwrInputArea"
                    patternRecognitionMode: InputEngine.HandwritingRecoginition
                }
            }
        }
        KeyboardColumn {
            Layout.preferredWidth: hideKeyboardKey.width
            KeyboardRow {
                BackspaceKey {}
            }
            KeyboardRow {
                EnterKey {}
            }
            KeyboardRow {
                ShiftKey { }
            }
        }
    }
    KeyboardRow {
        id: bottomRow
        Layout.preferredHeight: 1
        keyWeight: 154
        Key {
            weight: 217
            key: Qt.Key_Mode_switch
            noKeyEvent: true
            functionKey: true
            text: InputContext.inputEngine.inputMode === InputEngine.Latin ? "123" : "ABC"
            onClicked: InputContext.inputEngine.inputMode = InputContext.inputEngine.inputMode === InputEngine.Latin ? InputEngine.Numeric : InputEngine.Latin
            keyPanelDelegate: keyboard.style ? keyboard.style.symbolKeyPanel : undefined
        }
        ChangeLanguageKey {
            weight: 154
        }
        HandwritingModeKey {
            weight: 154
        }
        SpaceKey {
            weight: 864
        }
        Key {
            key: Qt.Key_Apostrophe
            text: "'"
            alternativeKeys: "<>()#%&*/\\\"'=+-_"
        }
        Key {
            key: Qt.Key_Period
            text: "."
            alternativeKeys: ":;,.?!"
        }
        HideKeyboardKey {
            id: hideKeyboardKey
            weight: 204
        }
    }
}
