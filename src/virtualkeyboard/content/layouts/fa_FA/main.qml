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
    inputMode: InputEngine.InputMode.Arabic
    keyWeight: 160
    smallTextVisible: true
    readonly property real normalKeyWidth: normalKey.width
    readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
    KeyboardRow {
        Key {
            text: "\u0635"
            alternativeKeys: "1\u0635\u0636\u0661"
            smallText: "\u0636\u0661"
        }
        Key {
            id: normalKey
            text: "\u0642"
            alternativeKeys: "2\u0642\u0662"
        }
        Key {
            text: "\u0641"
            alternativeKeys: "3\u0641\u0663"
        }
        Key {
            text: "\u063A"
            alternativeKeys: "4\u063A\u0664"
        }
        Key {
            text: "\u0639"
            alternativeKeys: "5\u0639\u0665"
        }
        Key {
            text: "\u0647"
            alternativeKeys: "6\u0647\u0666"
        }
        Key {
            text: "\u062E"
            alternativeKeys: "7\u062E\u0667"
        }
        Key {
            text: "\u062D"
            alternativeKeys: "8\u062D\u0668"
        }
        Key {
            text: "\u062C"
            alternativeKeys: "9\u062C\u0669"
        }
        Key {
            text: "\u0686"
            alternativeKeys: "0\u0686\u0660"
        }
    }
    KeyboardRow {
        Key {
            text: "\u0634"
        }
        Key {
            text: "\u0633"
        }
        Key {
            text: "\u06CC"
        }
        Key {
            text: "\u0628"
        }
        Key {
            text: "\u0644"
        }
        Key {
            text: "\u0627"
            alternativeKeys: "\u0625\u0627\u0623\u0622"
        }
        Key {
            text: "\u062A"
            alternativeKeys: "\u062A\u062B"
        }
        Key {
            text: "\u0646"
        }
        Key {
            text: "\u0645"
        }
        Key {
            text: "\u06A9"
        }
    }
    KeyboardRow {
        Key {
            text: "\u200C"
            alternativeKeys: "\u200C\u200D"
            displayText: "\u25C2\u205E\u25B8"
            displayAlternativeKeys: ["\u25B8\u205E\u25C2"]
            highlighted: true
        }
        Key {
            text: "\u064E"
            alternativeKeys: "\u064C\u064E\u064F\u0652\u064B\u064D\u0640\u0651\u0650"
            smallText: "\u25CC\u064F "
        }
        Key {
            text: "\u0637"
            alternativeKeys: "\u0637\u0638"
        }
        Key {
            text: "\u0632"
            alternativeKeys: "\u0632\u0698"
        }
        Key {
            text: "\u0631"
        }
        Key {
            text: "\u0630"
        }
        Key {
            text: "\u062F"
        }
        Key {
            text: "\u0648"
            alternativeKeys: "\u0624\u0648\u0621"
        }
        Key {
            text: "\u06AF"
            alternativeKeys: "\u06AF\u067E"
        }
        BackspaceKey {
        }
    }
    KeyboardRow {
        SymbolModeKey {
            displayText: "\u0661\u0662\u0663\u061F"
            weight: functionKeyWidth
            Layout.fillWidth: false
        }
        Key {
            key: Qt.Key_Comma
            weight: normalKeyWidth
            Layout.fillWidth: false
            text: "\u060C"
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
            alternativeKeys: "!,\u060C\u061B.\u061F"
            highlighted: true
        }
        EnterKey {
            weight: functionKeyWidth
            Layout.fillWidth: false
        }
    }
}
