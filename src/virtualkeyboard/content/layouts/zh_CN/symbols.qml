/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Enterprise.VirtualKeyboard 1.3

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick 2.0; import QtQuick.Enterprise.VirtualKeyboard 1.3; PinyinInputMethod {}', parent, "pinyinInputMethod")
    }
    property int page
    readonly property int numPages: 3
    property var keysPage1: [
        "1234567890",
        "@#$%^&*()",
        "“”、=：；！？～"
    ]
    property var keysPage2: [
        "-+/\\|[]{}·",
        "<>,.:;!?~",
        "／\"'_§￥€£¢"
    ]
    property var keysPage3: [
        "（）〔〕〈〉《》【】",
        "→←↑↓↔■□●○",
        "＼『』「」★☆◆◇"
    ]
    sourceComponent: {
        switch (page) {
        case 2: return page3
        case 1: return page2
        default: return page1
        }
    }
    Component {
        id: page1
        KeyboardLayout {
            keyWeight: 160
            KeyboardRow {
                Repeater {
                    model: keysPage1[0].length
                    Key {
                        key: keysPage1[0][index].charCodeAt(0)
                        text: keysPage1[0][index]
                    }
                }
                BackspaceKey {}
            }
            KeyboardRow {
                FillerKey {
                    weight: 56
                }
                Repeater {
                    model: keysPage1[1].length
                    Key {
                        key: keysPage1[1][index].charCodeAt(0)
                        text: keysPage1[1][index]
                    }
                }
                EnterKey {
                    weight: 283
                }
            }
            KeyboardRow {
                keyWeight: 156
                Key {
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                }
                Repeater {
                    model: keysPage1[2].length
                    Key {
                        key: keysPage1[2][index].charCodeAt(0)
                        text: keysPage1[2][index]
                    }
                }
                Key {
                    weight: 204
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                }
            }
            KeyboardRow {
                keyWeight: 154
                SymbolModeKey {
                    weight: 217
                    displayText: "ABC"
                }
                ChangeLanguageKey {
                    weight: 154
                }
                SpaceKey {
                    weight: 864
                }
                Key {
                    key: 0x2014
                    text: "—"
                }
                Key {
                    key: 0xE000
                    text: ":-)"
                    alternativeKeys: [ ";-)", ":-)", ":-D", ":-(", "<3" ]
                }
                HideKeyboardKey {
                    weight: 204
                }
            }
        }
    }
    Component {
        id: page2
        KeyboardLayout {
            keyWeight: 160
            KeyboardRow {
                Repeater {
                    model: keysPage2[0].length
                    Key {
                        key: keysPage2[0][index].charCodeAt(0)
                        text: keysPage2[0][index]
                    }
                }
                BackspaceKey {}
            }
            KeyboardRow {
                FillerKey {
                    weight: 56
                }
                Repeater {
                    model: keysPage2[1].length
                    Key {
                        key: keysPage2[1][index].charCodeAt(0)
                        text: keysPage2[1][index]
                    }
                }
                EnterKey {
                    weight: 283
                }
            }
            KeyboardRow {
                keyWeight: 156
                Key {
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                }
                Repeater {
                    model: keysPage2[2].length
                    Key {
                        key: keysPage2[2][index].charCodeAt(0)
                        text: keysPage2[2][index]
                    }
                }
                Key {
                    weight: 204
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                }
            }
            KeyboardRow {
                keyWeight: 154
                SymbolModeKey {
                    weight: 217
                    displayText: "ABC"
                }
                ChangeLanguageKey {
                    weight: 154
                }
                SpaceKey {
                    weight: 864
                }
                Key {
                    key: 0x3002
                    text: "。"
                }
                Key {
                    key: 0xE000
                    text: ":-)"
                    alternativeKeys: [ ";-)", ":-)", ":-D", ":-(", "<3" ]
                }
                HideKeyboardKey {
                    weight: 204
                }
            }
        }
    }
    Component {
        id: page3
        KeyboardLayout {
            keyWeight: 160
            KeyboardRow {
                Repeater {
                    model: keysPage3[0].length
                    Key {
                        key: keysPage3[0][index].charCodeAt(0)
                        text: keysPage3[0][index]
                    }
                }
                BackspaceKey {}
            }
            KeyboardRow {
                FillerKey {
                    weight: 56
                }
                Repeater {
                    model: keysPage3[1].length
                    Key {
                        key: keysPage3[1][index].charCodeAt(0)
                        text: keysPage3[1][index]
                    }
                }
                EnterKey {
                    weight: 283
                }
            }
            KeyboardRow {
                keyWeight: 156
                Key {
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                }
                Repeater {
                    model: keysPage3[2].length
                    Key {
                        key: keysPage3[2][index].charCodeAt(0)
                        text: keysPage3[2][index]
                    }
                }
                Key {
                    weight: 204
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                }
            }
            KeyboardRow {
                keyWeight: 154
                SymbolModeKey {
                    weight: 217
                    displayText: "ABC"
                }
                ChangeLanguageKey {
                    weight: 154
                }
                SpaceKey {
                    weight: 864
                }
                Key {
                    key: 0x2026
                    text: "…"
                }
                Key {
                    key: 0xE000
                    text: ":-)"
                    alternativeKeys: [ ";-)", ":-)", ":-D", ":-(", "<3" ]
                }
                HideKeyboardKey {
                    weight: 204
                }
            }
        }
    }
}
