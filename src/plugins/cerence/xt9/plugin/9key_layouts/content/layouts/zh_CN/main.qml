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

KeyboardLayout {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; PinyinInputMethod {}', parent, "main.qml")
    }
    sharedLayouts: ['symbols']
    smallTextVisible: true
    inputMode: InputEngine.InputMode.Pinyin
    KeyboardRow {
        Layout.fillWidth: false
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignHCenter
        KeyboardColumn {
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.preferredWidth: parent.height / 4 * 1
            Key {
                text: "～"
                alternativeKeys: "～『』「」（）〔〕〈〉《》【】"
                highlighted: true
            }
            Key {
                text: "@"
                alternativeKeys: "@#$%^&*()=<>,.:;!?~"
                highlighted: true
            }
            FillerKey {}
            SymbolModeKey {}
        }
        KeyboardColumn {
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.preferredWidth: parent.height / 30
            KeyboardRow {
                FillerKey {}
            }
        }
        KeyboardColumn {
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.preferredWidth: parent.height / 4 * 3
            KeyboardRow {
                Key {
                    enabled: InputContext.preeditText.length > 0
                    key: Qt.Key_Apostrophe
                    text: "'"
                    displayText: "词"
                    smallText: "1"
                    alternativeKeys: "'1"
                }
                Key {
                    key: Qt.Key_2
                    text: "a"
                    displayText: "ABC"
                    smallText: "2"
                    alternativeKeys: "abc2"
                }
                Key {
                    key: Qt.Key_3
                    text: "d"
                    displayText: "DEF"
                    smallText: "3"
                    alternativeKeys: "def3"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_4
                    text: "g"
                    displayText: "GHI"
                    smallText: "4"
                    alternativeKeys: "ghi4"
                }
                Key {
                    key: Qt.Key_5
                    text: "j"
                    displayText: "JKL"
                    smallText: "5"
                    alternativeKeys: "jkl5"
                }
                Key {
                    key: Qt.Key_6
                    text: "m"
                    displayText: "MNO"
                    smallText: "6"
                    alternativeKeys: "mno6"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_7
                    text: "p"
                    displayText: "PQRS"
                    smallText: "7"
                    alternativeKeys: "pqrs7"
                }
                Key {
                    key: Qt.Key_8
                    text: "t"
                    displayText: "TUV"
                    smallText: "8"
                    alternativeKeys: "tuv8"
                }
                Key {
                    key: Qt.Key_9
                    text: "w"
                    displayText: "WXYZ"
                    smallText: "9"
                    alternativeKeys: "wxyz9"
                }
            }
            KeyboardRow {
                Key {
                    key: Qt.Key_Comma
                    text: "\u3001"
                    smallText: "\u2699"
                    smallTextVisible: true
                }
                Key {
                    key: Qt.Key_0
                    text: "，"
                    alternativeKeys: "，；0"
                    smallText: "0"
                }
                Key {
                    text: "。"
                    alternativeKeys: "。？！："
                }
            }
        }
        KeyboardColumn {
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.preferredWidth: parent.height / 30
            KeyboardRow {
                FillerKey {}
            }
        }
        KeyboardColumn {
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.preferredWidth: parent.height / 4 * 1
            BackspaceKey {}
            Key {
                text: "\u3000"
                displayText: "\u2423"
                repeat: true
                showPreview: false
                key: Qt.Key_Space
                highlighted: true
            }
            HideKeyboardKey {}
            EnterKey {}
        }
    }
}
