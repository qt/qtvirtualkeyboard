/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
import QtQuick.Layouts
import QtQuick.VirtualKeyboard

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; PinyinInputMethod {}', parent, "symbols.qml")
    }
    sharedLayouts: ['main']
    property int page
    readonly property int numPages: 3
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
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    key: Qt.Key_1
                    text: "1"
                }
                Key {
                    id: normalKey
                    key: Qt.Key_2
                    text: "2"
                }
                Key {
                    key: Qt.Key_3
                    text: "3"
                }
                Key {
                    key: Qt.Key_4
                    text: "4"
                }
                Key {
                    key: Qt.Key_5
                    text: "5"
                }
                Key {
                    key: Qt.Key_6
                    text: "6"
                }
                Key {
                    key: Qt.Key_7
                    text: "7"
                }
                Key {
                    key: Qt.Key_8
                    text: "8"
                }
                Key {
                    key: Qt.Key_9
                    text: "9"
                }
                Key {
                    key: Qt.Key_0
                    text: "0"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_1
                    text: "@"
                }
                Key {
                    key: Qt.Key_1
                    text: "#"
                }
                Key {
                    key: Qt.Key_1
                    text: "%"
                }
                Key {
                    key: Qt.Key_1
                    text: "&"
                }
                Key {
                    key: Qt.Key_1
                    text: "*"
                }
                Key {
                    key: Qt.Key_1
                    text: "_"
                }
                Key {
                    key: Qt.Key_1
                    text: "-"
                }
                Key {
                    key: Qt.Key_1
                    text: "+"
                }
                Key {
                    key: Qt.Key_1
                    text: "("
                }
                Key {
                    key: Qt.Key_1
                    text: ")"
                }
            }
            KeyboardRow {
                Key {
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                    highlighted: true
                }
                Key {
                    text: "“"
                }
                Key {
                    text: "”"
                }
                Key {
                    text: "、"
                }
                Key {
                    text: "："
                }
                Key {
                    text: "；"
                }
                Key {
                    text: "！"
                }
                Key {
                    text: "？"
                }
                Key {
                    text: "～"
                }
                BackspaceKey {
                }
            }
            KeyboardRow {
                SymbolModeKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                    displayText: "ABC"
                }
                Key {
                    key: Qt.Key_Comma
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: ","
                    smallText: "\u2699"
                    smallTextVisible: true
                    highlighted: true
                }
                SpaceKey {
                }
                Key {
                    key: Qt.Key_Period
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "—"
                    highlighted: true
                }
                EnterKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
        }
    }
    Component {
        id: page2
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    text: "½"
                    alternativeKeys: "½¼¾"
                }
                Key {
                    id: normalKey
                    text: "'"
                }
                Key {
                    text: "/"
                }
                Key {
                    text: "\\"
                }
                Key {
                    text: "|"
                }
                Key {
                    text: "["
                }
                Key {
                    text: "]"
                }
                Key {
                    text: "{"
                }
                Key {
                    text: "}"
                }
                Key {
                    text: "·"
                }
            }
            KeyboardRow {
                Key {
                    text: "<"
                }
                Key {
                    text: ">"
                }
                Key {
                    text: ","
                }
                Key {
                    text: "."
                }
                Key {
                    text: ":"
                }
                Key {
                    text: ";"
                }
                Key {
                    text: "!"
                }
                Key {
                    text: "?"
                }
                Key {
                    text: "="
                }
                Key {
                    text: "~"
                }
            }
            KeyboardRow {
                Key {
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                    highlighted: true
                }
                Key {
                    text: "\""
                }
                Key {
                    text: "§"
                }
                Key {
                    text: "^"
                }
                Key {
                    text: "$"
                }
                Key {
                    text: "￥"
                }
                Key {
                    text: "€"
                }
                Key {
                    text: "£"
                }
                Key {
                    text: "¢"
                }
                BackspaceKey {
                }
            }
            KeyboardRow {
                SymbolModeKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                    displayText: "ABC"
                }
                Key {
                    key: Qt.Key_Comma
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: ","
                    smallText: "\u2699"
                    smallTextVisible: true
                    highlighted: true
                }
                SpaceKey {
                }
                Key {
                    key: Qt.Key_Period
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "。"
                    highlighted: true
                }
                EnterKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
        }
    }
    Component {
        id: page3
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    text: "＼"
                }
                Key {
                    id: normalKey
                    text: "／"
                }
                Key {
                    text: "（"
                }
                Key {
                    text: "）"
                }
                Key {
                    text: "〔"
                }
                Key {
                    text: "〕"
                }
                Key {
                    text: "〈"
                }
                Key {
                    text: "〉"
                }
                Key {
                    text: "《"
                }
                Key {
                    text: "》"
                }
            }
            KeyboardRow {
                Key {
                    text: "→"
                }
                Key {
                    text: "←"
                }
                Key {
                    text: "↑"
                }
                Key {
                    text: "↓"
                }
                Key {
                    text: "■"
                }
                Key {
                    text: "□"
                }
                Key {
                    text: "●"
                }
                Key {
                    text: "○"
                }
                Key {
                    text: "【"
                }
                Key {
                    text: "】"
                }
            }
            KeyboardRow {
                Key {
                    displayText: (page + 1) + "/" + numPages
                    functionKey: true
                    onClicked: page = (page + 1) % numPages
                    highlighted: true
                }
                Key {
                    text: "『"
                }
                Key {
                    text: "』"
                }
                Key {
                    text: "「"
                }
                Key {
                    text: "」"
                }
                Key {
                    text: "★"
                }
                Key {
                    text: "☆"
                }
                Key {
                    text: "◆"
                }
                Key {
                    text: "◇"
                }
                BackspaceKey {
                }
            }
            KeyboardRow {
                SymbolModeKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                    displayText: "ABC"
                }
                Key {
                    key: Qt.Key_Comma
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: ","
                    smallText: "\u2699"
                    smallTextVisible: true
                    highlighted: true
                }
                SpaceKey {
                }
                Key {
                    key: Qt.Key_Period
                    weight: normalKeyWidth
                    Layout.fillWidth: false
                    text: "…"
                    highlighted: true
                }
                EnterKey {
                    weight: functionKeyWidth
                    Layout.fillWidth: false
                }
            }
        }
    }
}
