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

KeyboardLayoutLoader {
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick; import QtQuick.VirtualKeyboard.Plugins; HangulInputMethod {}', parent, "main.qml")
    }
    sourceComponent: InputContext.shiftActive ? page2 : page1
    sharedLayouts: ['symbols']
    Component {
        id: page1
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    text: "\u3142"
                    alternativeKeys: "\u3142\u3143"
                }
                Key {
                    id: normalKey
                    text: "\u3148"
                    alternativeKeys: "\u3148\u3149"
                }
                Key {
                    text: "\u3137"
                    alternativeKeys: "\u3137\u3138"
                }
                Key {
                    text: "\u3131"
                    alternativeKeys: "\u3131\u3132"
                }
                Key {
                    text: "\u3145"
                    alternativeKeys: "\u3145\u3146"
                }
                Key {
                    text: "\u315B"
                }
                Key {
                    text: "\u3155"
                }
                Key {
                    text: "\u3151"
                }
                Key {
                    text: "\u3150"
                    alternativeKeys: "\u3150\u3152"
                }
                Key {
                    text: "\u3154"
                    alternativeKeys: "\u3154\u3156"
                }
            }
            KeyboardRow {
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    FillerKey {
                    }
                    Key {
                        text: "\u3141"
                        weight: normalKeyWidth
                        Layout.fillWidth: false
                    }
                }
                Key {
                    text: "\u3134"
                }
                Key {
                    text: "\u3147"
                }
                Key {
                    text: "\u3139"
                }
                Key {
                    text: "\u314E"
                }
                Key {
                    text: "\u3157"
                }
                Key {
                    text: "\u3153"
                }
                Key {
                    text: "\u314F"
                }
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    Key {
                        text: "\u3163"
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
                    text: "\u314B"
                }
                Key {
                    text: "\u314C"
                }
                Key {
                    text: "\u314A"
                }
                Key {
                    text: "\u314D"
                }
                Key {
                    text: "\u3160"
                }
                Key {
                    text: "\u315C"
                }
                Key {
                    text: "\u3161"
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
    }
    Component {
        id: page2
        KeyboardLayout {
            keyWeight: 160
            readonly property real normalKeyWidth: normalKey.width
            readonly property real functionKeyWidth: mapFromItem(normalKey, normalKey.width / 2, 0).x
            KeyboardRow {
                Key {
                    text: "\u3143"
                }
                Key {
                    id: normalKey
                    text: "\u3149"
                }
                Key {
                    text: "\u3138"
                }
                Key {
                    text: "\u3132"
                }
                Key {
                    text: "\u3146"
                }
                Key {
                    text: "\u315B"
                }
                Key {
                    text: "\u3155"
                }
                Key {
                    text: "\u3151"
                }
                Key {
                    text: "\u3152"
                }
                Key {
                    text: "\u3156"
                }
            }
            KeyboardRow {
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    FillerKey {
                    }
                    Key {
                        text: "\u3141"
                        weight: normalKeyWidth
                        Layout.fillWidth: false
                    }
                }
                Key {
                    text: "\u3134"
                }
                Key {
                    text: "\u3147"
                }
                Key {
                    text: "\u3139"
                }
                Key {
                    text: "\u314E"
                }
                Key {
                    text: "\u3157"
                }
                Key {
                    text: "\u3153"
                }
                Key {
                    text: "\u314F"
                }
                KeyboardRow {
                    Layout.preferredWidth: functionKeyWidth
                    Layout.fillWidth: false
                    Key {
                        text: "\u3163"
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
                    text: "\u314B"
                }
                Key {
                    text: "\u314C"
                }
                Key {
                    text: "\u314A"
                }
                Key {
                    text: "\u314D"
                }
                Key {
                    text: "\u3160"
                }
                Key {
                    text: "\u315C"
                }
                Key {
                    text: "\u3161"
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
    }
}
