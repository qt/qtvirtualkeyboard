// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Components

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; TCInputMethod {}', parent, "main.qml")
    }
    sharedLayouts: ['symbols']
    sourceComponent: {
        switch (InputContext.inputEngine.inputMode) {
        case InputEngine.InputMode.Cangjie:
            return pageCangjie
        case InputEngine.InputMode.Zhuyin:
            return pageZhuyin
        default:
            return null
        }
    }
    Component {
        id: pageCangjie
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            smallTextVisible: true
            KeyboardRow {
                Key {
                    text: "\u624B"
                    alternativeKeys: "\u624Bq"
                }
                Key {
                    id: normalKey
                    text: "\u7530"
                    alternativeKeys: "\u7530w"
                }
                Key {
                    text: "\u6C34"
                    alternativeKeys: "\u6C34e"
                }
                Key {
                    text: "\u53E3"
                    alternativeKeys: "\u53E3r"
                }
                Key {
                    text: "\u5EFF"
                    alternativeKeys: "\u5EFFt"
                }
                Key {
                    text: "\u535C"
                    alternativeKeys: "\u535Cy"
                }
                Key {
                    text: "\u5C71"
                    alternativeKeys: "\u5C71u"
                }
                Key {
                    text: "\u6208"
                    alternativeKeys: "\u6208i"
                }
                Key {
                    text: "\u4EBA"
                    alternativeKeys: "\u4EBAo"
                }
                Key {
                    text: "\u5FC3"
                    alternativeKeys: "\u5FC3p"
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
                        alternativeKeys: "\u65E5a"
                        weight: normalKeyWidth
                        Layout.fillWidth: false
                    }
                }
                Key {
                    text: "\u5C38"
                    alternativeKeys: "\u5C38s"
                }
                Key {
                    text: "\u6728"
                    alternativeKeys: "\u6728d"
                }
                Key {
                    text: "\u706B"
                    alternativeKeys: "\u706Bf"
                }
                Key {
                    text: "\u571F"
                    alternativeKeys: "\u571Fg"
                }
                Key {
                    text: "\u7AF9"
                    alternativeKeys: "\u7AF9h"
                }
                Key {
                    text: "\u5341"
                    alternativeKeys: "\u5341j"
                }
                Key {
                    text: "\u5927"
                    alternativeKeys: "\u5927k"
                }
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    Key {
                        text: "\u4E2D"
                        alternativeKeys: "\u4E2Dl"
                        weight: normalKeyWidth
                        Layout.fillWidth: false
                    }
                    FillerKey {
                    }
                }
            }
            KeyboardRow {
                ModeKey {
                    id: simplifiedModeKey
                    key: Qt.Key_Mode_switch
                    displayText: "速成"
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                    Component.onCompleted: updateBinding()
                    Connections {
                        target: InputContext.inputEngine
                        function onInputMethodChanged() { simplifiedModeKey.updateBinding() }
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
                    alternativeKeys: "\u91CDz"
                }
                Key {
                    text: "\u96E3"
                    alternativeKeys: "\u96E3x"
                }
                Key {
                    text: "\u91D1"
                    alternativeKeys: "\u91D1c"
                }
                Key {
                    text: "\u5973"
                    alternativeKeys: "\u5973v"
                }
                Key {
                    text: "\u6708"
                    alternativeKeys: "\u6708b"
                }
                Key {
                    text: "\u5F13"
                    alternativeKeys: "\u5F13n"
                }
                Key {
                    text: "\u4E00"
                    alternativeKeys: "\u4E00m"
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
    }
    Component {
        id: pageZhuyin
        KeyboardLayout {
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            smallTextVisible: true
            KeyboardRow {
                Layout.preferredHeight: 3
                KeyboardColumn {
                    KeyboardRow {
                        Key {
                            text: "\u3105"
                            alternativeKeys: "\u31051"
                        }
                        Key {
                            id: normalKey
                            text: "\u3109"
                            alternativeKeys: "\u31092"
                        }
                        Key {
                            text: "\u02C7"
                            alternativeKeys: "\u02C73"
                        }
                        Key {
                            text: "\u02CB"
                            alternativeKeys: "\u02CB4"
                            displayText: "`"
                        }
                        Key {
                            text: "\u3113"
                            alternativeKeys: "\u31135"
                        }
                        Key {
                            text: "\u02CA"
                            alternativeKeys: "\u02CA6"
                            displayText: "´"
                        }
                        Key {
                            text: "\u02D9"
                            alternativeKeys: "\u02D97"
                        }
                        Key {
                            text: "\u311A"
                            alternativeKeys: "\u311A8"
                        }
                        Key {
                            text: "\u311E"
                            alternativeKeys: "\u311E9"
                        }
                        Key {
                            text: "\u3122"
                            alternativeKeys: "\u31220"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "\u3106"
                            alternativeKeys: "\u3106q"
                        }
                        Key {
                            text: "\u310A"
                            alternativeKeys: "\u310Aw"
                        }
                        Key {
                            text: "\u310D"
                            alternativeKeys: "\u310De"
                        }
                        Key {
                            text: "\u3110"
                            alternativeKeys: "\u3110r"
                        }
                        Key {
                            text: "\u3114"
                            alternativeKeys: "\u3114t"
                        }
                        Key {
                            text: "\u3117"
                            alternativeKeys: "\u3117y"
                        }
                        Key {
                            text: "\u3127"
                            alternativeKeys: "\u3127u"
                        }
                        Key {
                            text: "\u311B"
                            alternativeKeys: "\u311Bi"
                        }
                        Key {
                            text: "\u311F"
                            alternativeKeys: "\u311Fo"
                        }
                        Key {
                            text: "\u3123"
                            alternativeKeys: "\u3123p"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "\u3107"
                            alternativeKeys: "\u3107a"
                        }
                        Key {
                            text: "\u310B"
                            alternativeKeys: "\u310Bs"
                        }
                        Key {
                            text: "\u310E"
                            alternativeKeys: "\u310Ed"
                        }
                        Key {
                            text: "\u3111"
                            alternativeKeys: "\u3111f"
                        }
                        Key {
                            text: "\u3115"
                            alternativeKeys: "\u3115g"
                        }
                        Key {
                            text: "\u3118"
                            alternativeKeys: "\u3118h"
                        }
                        Key {
                            text: "\u3128"
                            alternativeKeys: "\u3128j"
                        }
                        Key {
                            text: "\u311C"
                            alternativeKeys: "\u311Ck"
                        }
                        Key {
                            text: "\u3120"
                            alternativeKeys: "\u3120l"
                        }
                        Key {
                            text: "\u3124"
                            alternativeKeys: "\u3124…"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "\u3108"
                            alternativeKeys: "\u3108z"
                        }
                        Key {
                            text: "\u310C"
                            alternativeKeys: "\u310Cx"
                        }
                        Key {
                            text: "\u310F"
                            alternativeKeys: "\u310Fc"
                        }
                        Key {
                            text: "\u3112"
                            alternativeKeys: "\u3112v"
                        }
                        Key {
                            text: "\u3116"
                            alternativeKeys: "\u3116b"
                        }
                        Key {
                            text: "\u3119"
                            alternativeKeys: "\u3119n"
                        }
                        Key {
                            text: "\u3129"
                            alternativeKeys: "\u3129m"
                        }
                        Key {
                            text: "\u311D"
                            alternativeKeys: "、\u311D，"
                        }
                        Key {
                            text: "\u3121"
                            alternativeKeys: "。\u3121．"
                        }
                        Key {
                            text: "\u3125"
                            alternativeKeys: "；\u3125："
                        }
                    }
                }
            }
            KeyboardRow {
                id: bottomRow
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
                BackspaceKey {
                    weight: normalKeyWidth
                    Layout.fillWidth: false
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
    }
}
