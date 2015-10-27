/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Enterprise.VirtualKeyboard 2.0

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick 2.0; import QtQuick.Enterprise.VirtualKeyboard 2.0; TCInputMethod {}', parent, "tcInputMethod")
    }
    sharedLayouts: ['symbols']
    sourceComponent: InputContext.shift ? pageLatin : pageCangjie
    Component {
        id: pageCangjie
        KeyboardLayout {
            keyWeight: 160
            smallTextVisible: true
            KeyboardRow {
                Key {
                    text: "\u624B"
                    smallText: "q"
                }
                Key {
                    text: "\u7530"
                    smallText: "w"
                }
                Key {
                    text: "\u6C34"
                    smallText: "e"
                }
                Key {
                    text: "\u53E3"
                    smallText: "r"
                }
                Key {
                    text: "\u5EFF"
                    smallText: "t"
                }
                Key {
                    text: "\u535C"
                    smallText: "y"
                }
                Key {
                    text: "\u5C71"
                    smallText: "u"
                }
                Key {
                    text: "\u6208"
                    smallText: "i"
                }
                Key {
                    text: "\u4EBA"
                    smallText: "o"
                }
                Key {
                    text: "\u5FC3"
                    smallText: "p"
                }
                BackspaceKey {}
            }
            KeyboardRow {
                FillerKey {
                    weight: 56
                }
                Key {
                    text: "\u65E5"
                    smallText: "a"
                }
                Key {
                    text: "\u5C38"
                    smallText: "s"
                }
                Key {
                    text: "\u6728"
                    smallText: "d"
                }
                Key {
                    text: "\u706B"
                    smallText: "f"
                }
                Key {
                    text: "\u571F"
                    smallText: "g"
                }
                Key {
                    text: "\u7AF9"
                    smallText: "h"
                }
                Key {
                    text: "\u5341"
                    smallText: "j"
                }
                Key {
                    text: "\u5927"
                    smallText: "k"
                }
                Key {
                    text: "\u4E2D"
                    smallText: "l"
                }
                EnterKey {
                    weight: 283
                }
            }
            KeyboardRow {
                keyWeight: 156
                ModeKey {
                    id: simplifiedModeKey
                    key: Qt.Key_Mode_switch
                    displayText: "速成"
                    Component.onCompleted: updateBinding()
                    Connections {
                        target: InputContext.inputEngine
                        onInputMethodChanged: simplifiedModeKey.updateBinding()
                    }
                    function updateBinding() {
                        if (InputContext.inputEngine.inputMethod && InputContext.inputEngine.inputMethod.hasOwnProperty("simplified")) {
                            simplifiedModeKey.mode = InputContext.inputEngine.inputMethod.simplified
                            InputContext.inputEngine.inputMethod.simplified = Qt.binding(function() { return simplifiedModeKey.mode })
                        }
                    }
                }
                Key {
                    text: "\u91CD"
                    smallText: "z"
                }
                Key {
                    text: "\u96E3"
                    smallText: "x"
                }
                Key {
                    text: "\u91D1"
                    smallText: "c"
                }
                Key {
                    text: "\u5973"
                    smallText: "v"
                }
                Key {
                    text: "\u6708"
                    smallText: "b"
                }
                Key {
                    text: "\u5F13"
                    smallText: "n"
                }
                Key {
                    text: "\u4E00"
                    smallText: "m"
                }
                Key {
                    key: Qt.Key_Comma
                    text: "\uFF0C"
                    alternativeKeys: "\uFF0C\uFF1B\u3001"
                }
                Key {
                    key: Qt.Key_Period
                    text: "\uFF0E"
                    alternativeKeys: "\uFF0E\uFF1A\u3002"
                }
                ShiftKey {
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
                    key: Qt.Key_Question
                    text: "\uFF1F"
                    alternativeKeys: "\uFF1F\uFF01"
                }
                Key {
                    key: 0xE000
                    text: ":-)"
                    smallTextVisible: false
                    alternativeKeys: [ ";-)", ":-)", ":-D", ":-(", "<3" ]
                }
                HideKeyboardKey {
                    weight: 204
                }
            }
        }
    }
    Component {
        id: pageLatin
        KeyboardLayout {
            keyWeight: 160
            smallTextVisible: true
            KeyboardRow {
                Key {
                    key: Qt.Key_Q
                    text: "q"
                }
                Key {
                    key: Qt.Key_W
                    text: "w"
                }
                Key {
                    key: Qt.Key_E
                    text: "e"
                }
                Key {
                    key: Qt.Key_R
                    text: "r"
                }
                Key {
                    key: Qt.Key_T
                    text: "t"
                }
                Key {
                    key: Qt.Key_Y
                    text: "y"
                }
                Key {
                    key: Qt.Key_U
                    text: "u"
                }
                Key {
                    key: Qt.Key_I
                    text: "i"
                }
                Key {
                    key: Qt.Key_O
                    text: "o"
                }
                Key {
                    key: Qt.Key_P
                    text: "p"
                }
                BackspaceKey {}
            }
            KeyboardRow {
                FillerKey {
                    weight: 56
                }
                Key {
                    key: Qt.Key_A
                    text: "a"
                }
                Key {
                    key: Qt.Key_S
                    text: "s"
                }
                Key {
                    key: Qt.Key_D
                    text: "d"
                }
                Key {
                    key: Qt.Key_F
                    text: "f"
                }
                Key {
                    key: Qt.Key_G
                    text: "g"
                }
                Key {
                    key: Qt.Key_H
                    text: "h"
                }
                Key {
                    key: Qt.Key_J
                    text: "j"
                }
                Key {
                    key: Qt.Key_K
                    text: "k"
                }
                Key {
                    key: Qt.Key_L
                    text: "l"
                }
                EnterKey {
                    weight: 283
                }
            }
            KeyboardRow {
                keyWeight: 156
                ModeKey {
                    id: simplifiedModeKey
                    key: Qt.Key_Mode_switch
                    enabled: InputContext.inputEngine.inputMode == InputEngine.Cangjie
                    displayText: "速成"
                    Component.onCompleted: updateBinding()
                    Connections {
                        target: InputContext.inputEngine
                        onInputMethodChanged: simplifiedModeKey.updateBinding()
                    }
                    function updateBinding() {
                        if (InputContext.inputEngine.inputMethod && InputContext.inputEngine.inputMethod.hasOwnProperty("simplified")) {
                            simplifiedModeKey.mode = InputContext.inputEngine.inputMethod.simplified
                            InputContext.inputEngine.inputMethod.simplified = Qt.binding(function() { return simplifiedModeKey.mode })
                        }
                    }
                }
                Key {
                    key: Qt.Key_Z
                    text: "z"
                }
                Key {
                    key: Qt.Key_X
                    text: "x"
                }
                Key {
                    key: Qt.Key_C
                    text: "c"
                }
                Key {
                    key: Qt.Key_V
                    text: "v"
                }
                Key {
                    key: Qt.Key_B
                    text: "b"
                }
                Key {
                    key: Qt.Key_N
                    text: "n"
                }
                Key {
                    key: Qt.Key_M
                    text: "m"
                }
                Key {
                    key: Qt.Key_Comma
                    text: "\uFF0C"
                    alternativeKeys: "\uFF0C\uFF1B\u3001"
                }
                Key {
                    key: Qt.Key_Period
                    text: "\uFF0E"
                    alternativeKeys: "\uFF0E\uFF1A\u3002"
                }
                ShiftKey {
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
                HandwritingModeKey {
                    weight: 154
                }
                SpaceKey {
                    weight: 864
                }
                Key {
                    key: Qt.Key_Question
                    text: "\uFF1F"
                    alternativeKeys: "\uFF1F\uFF01"
                }
                Key {
                    key: 0xE000
                    text: ":-)"
                    smallTextVisible: false
                    alternativeKeys: [ ";-)", ":-)", ":-D", ":-(", "<3" ]
                }
                HideKeyboardKey {
                    weight: 204
                }
            }
        }
    }
}
