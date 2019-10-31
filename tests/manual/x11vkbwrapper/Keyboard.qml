/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
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

import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2
import Qt.labs.platform 1.1

Window {
    id: keyboardWindow
    width: Screen.width / 2
    height: width / 3.2
    y: Screen.height - height
    color: "transparent"
    visible: Qt.inputMethod.visible
    flags: Qt.WindowStaysOnTopHint | Qt.WindowDoesNotAcceptFocus | Qt.FramelessWindowHint

    readonly property double scaleFactor: 1.5
    signal languageChangedSignal(string msg)

    Loader {
        id: testLoader
        sourceComponent: {
            if (typeof(QT_TESTING_RUN) !== undefined) {
                lang
            }
        }
    }

    Component {
       id: lang
        Text {
            id: langText
            visible: false
            text: qsTr(Qt.locale(InputContext.locale).nativeLanguageName)
            onTextChanged: {
                 keyboardWindow.languageChangedSignal(langText.text)
            }
        }
    }

    SystemTrayIcon {
        id: qtLogo
        icon {
            mask: true
            source: "graphics/Qt_logo.png"
        }
        visible: !Qt.inputMethod.visible
        onActivated: atspiFocus.setKeyboardVisible(!Qt.inputMethod.visible)
        Component.onCompleted: console.log("Found system tray?:",qtLogo.available)
    }

    InputPanel {
        id: inputPanel
        z: 99
        anchors.fill: parent

        DragHandler {
            target: null
            onTranslationChanged: {
                var dx = translation.x
                var dy = translation.y
                if (keyboardWindow.x < 0)
                    dx = 0
                if (keyboardWindow.x + keyboardWindow.width > Screen.width)
                    dx = 0
                if (keyboardWindow.y < 0)
                    dy = 0
                if (keyboardWindow.y + keyboardWindow.height > Screen.height)
                    dy = 0

                keyboardWindow.x += dx
                keyboardWindow.y += dy
            }
        }
    }
}
