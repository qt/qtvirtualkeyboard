/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2
import Qt.labs.platform 1.1

Window {
    id: keyboardWindow
    width: Screen.width / 2
    height: width / 2.65
    y: Screen.height - height
    color: "transparent"
    visible: Qt.inputMethod.visible
    flags: Qt.WindowStaysOnTopHint | Qt.WindowDoesNotAcceptFocus | Qt.FramelessWindowHint

    readonly property double scaleFactor: 1.5
    signal languageChangedSignal(string msg)

    QtObject {
        id: d
        property double alternativeKeySpaceHeight: inputPanel.height / 4.7
    }

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

    Rectangle {
        id: dragArea
        anchors.fill: parent
        anchors.bottomMargin: keyboardWindow.height - d.alternativeKeySpaceHeight
        color: "#aa444444"
        opacity: hoverHandler.hovered ? 1 : 0
        DragHandler {
            target: null
            onTranslationChanged: {
                var dx = translation.x
                var dy = translation.y
                var ksx = keyboardWindow.x + keyboardWindow.width
                var ksy = keyboardWindow.y + keyboardWindow.height
                if (keyboardWindow.x < 0 && (keyboardWindow.x + dx) < 0)
                    dx = 0
                if (ksx > Screen.width && (ksx + dx) > Screen.width)
                    dx = 0
                if (keyboardWindow.y < 0 && (keyboardWindow.y + dy) < 0)
                    dy = 0
                if (ksy > Screen.height && (ksy + dy) > Screen.height)
                    dy = 0

                keyboardWindow.x += dx
                keyboardWindow.y += dy
            }
        }

        HoverHandler {
            id: hoverHandler
        }

        Behavior on opacity {
            NumberAnimation {}
        }
        Text {
            text: "Click here and then drag to move the keyboard"
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            y: (d.alternativeKeySpaceHeight - height) / 2
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        anchors.fill: parent
    }
}
