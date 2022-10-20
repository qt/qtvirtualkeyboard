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
    keyWeight: 160
    readonly property real normalKeyWidth: normalKey.width
    readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; CangjieInputMethod {}', parent, "main.qml")
    }
    sharedLayouts: ['symbols']
    smallTextVisible: true
    inputMode: InputEngine.InputMode.Cangjie
    KeyboardRow {
        Key {
            text: "\u624B"
        }
        Key {
            id: normalKey
            text: "\u7530"
        }
        Key {
            text: "\u6C34"
        }
        Key {
            text: "\u53E3"
        }
        Key {
            text: "\u5EFF"
        }
        Key {
            text: "\u535C"
        }
        Key {
            text: "\u5C71"
        }
        Key {
            text: "\u6208"
        }
        Key {
            text: "\u4EBA"
        }
        Key {
            text: "\u5FC3"
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
                weight: normalKeyWidth
                Layout.fillWidth: false
            }
        }
        Key {
            text: "\u5C38"
        }
        Key {
            text: "\u6728"
        }
        Key {
            text: "\u706B"
        }
        Key {
            text: "\u571F"
        }
        Key {
            text: "\u7AF9"
        }
        Key {
            text: "\u5341"
        }
        Key {
            text: "\u5927"
        }
        KeyboardRow {
            Layout.preferredWidth: functionKeyWidth
            Layout.fillWidth: false
            Key {
                text: "\u4E2D"
                weight: normalKeyWidth
                Layout.fillWidth: false
            }
            FillerKey {
            }
        }
    }
    KeyboardRow {
        ShiftKey {
            weight: functionKeyWidth
            Layout.fillWidth: false
        }
        Key {
            text: "\u91CD"
        }
        Key {
            text: "\u96E3"
        }
        Key {
            text: "\u91D1"
        }
        Key {
            text: "\u5973"
        }
        Key {
            text: "\u6708"
        }
        Key {
            text: "\u5F13"
        }
        Key {
            text: "\u4E00"
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
        Key {
            key: Qt.Key_Comma
            weight: normalKeyWidth
            Layout.fillWidth: false
            text: "\uFF0C"
            smallText: "\u2699"
            smallTextVisible: true
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
        EnterKey {
            weight: functionKeyWidth
            Layout.fillWidth: false
        }
    }
}
