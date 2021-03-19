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
import QtQuick.VirtualKeyboard
import QtQuick.Layouts

KeyboardLayout {
    inputMode: InputEngine.InputMode.Latin
    keyWeight: 160
    readonly property real normalKeyWidth: normalKey.width
    readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
    KeyboardRow {
        Key {
            key: Qt.Key_Q
            text: "q"
        }
        Key {
            id: normalKey
            key: Qt.Key_W
            text: "w"
        }
        Key {
            key: Qt.Key_E
            text: "e"
            alternativeKeys: "eę"
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
            alternativeKeys: "oó"
        }
        Key {
            key: Qt.Key_P
            text: "p"
        }
    }
    KeyboardRow {
        KeyboardRow {
            Layout.preferredWidth: functionKeyWidth
            Layout.fillWidth: false
            FillerKey {
            }
            Key {
                key: Qt.Key_A
                text: "a"
                alternativeKeys: "aą"
                weight: normalKeyWidth
                Layout.fillWidth: false
            }
        }
        Key {
            key: Qt.Key_S
            text: "s"
            alternativeKeys: "sś"
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
        KeyboardRow {
            Layout.preferredWidth: functionKeyWidth
            Layout.fillWidth: false
            Key {
                key: Qt.Key_L
                text: "l"
                alternativeKeys: "lł"
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
            key: Qt.Key_Z
            text: "z"
            alternativeKeys: "zźż"
        }
        Key {
            key: Qt.Key_X
            text: "x"
            alternativeKeys: "xź"
        }
        Key {
            key: Qt.Key_C
            text: "c"
            alternativeKeys: "cć"
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
            alternativeKeys: "nń"
        }
        Key {
            key: Qt.Key_M
            text: "m"
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
            text: "."
            alternativeKeys: "!.?"
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
