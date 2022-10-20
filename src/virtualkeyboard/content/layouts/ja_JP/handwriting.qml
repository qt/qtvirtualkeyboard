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
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; HandwritingInputMethod {}', parent)
    }
    sharedLayouts: ['symbols']

    KeyboardRow {
        Layout.preferredHeight: 3
        TraceInputKey {
            objectName: "hwrInputArea"
            patternRecognitionMode: InputEngine.PatternRecognitionMode.Handwriting
            horizontalRulers:
                InputContext.inputEngine.inputMode !== InputEngine.InputMode.JapaneseHandwriting ? [] :
                    [Math.round(boundingBox.height / 4), Math.round(boundingBox.height / 4) * 2, Math.round(boundingBox.height / 4) * 3]
        }
    }
    KeyboardRow {
        id: bottomRow
        Layout.preferredHeight: 1
        keyWeight: 160
        ShiftKey {
            weight: 240
        }
        InputModeKey {
        }
        Key {
            key: Qt.Key_Comma
            text: "、"
            smallText: "\u2699"
            smallTextVisible: true
            highlighted: true
        }
        SpaceKey {
            weight: 10 * 160 - 4 * 160  - 2 * 240
        }
        Key {
            key: Qt.Key_Period
            text: "．"
            alternativeKeys: "‘’“”～…—《》〈〉「」\"，．：；。？！"
            smallText: "!?"
            smallTextVisible: true
            highlighted: true
        }
        BackspaceKey {
        }
        EnterKey {
            weight: 240
        }
    }
}
