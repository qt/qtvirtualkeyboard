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

import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2

Window {
    id: keyboardWindow
    width: Screen.width / scaleFactor
    height: inputPanel.height + d.alternativeKeySpaceHeight
    color: "transparent"
    visible: Qt.inputMethod.visible
    flags: Qt.WindowStaysOnTopHint | Qt.WindowDoesNotAcceptFocus | Qt.FramelessWindowHint

    readonly property double scaleFactor: 1.5
    signal languageChangedSignal(string msg)

    QtObject {
        id: d
        property double alternativeKeySpaceHeight: inputPanel.height / 4.5
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

    InputPanel {
        id: inputPanel
        z: 99
        width: keyboardWindow.width
        anchors.bottom: parent.bottom
    }
}
