/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 2.0

TextBase {
    id: textArea

    property alias color: textEdit.color
    property alias text: textEdit.text
    property alias textWidth: textEdit.width
    property alias readOnly: textEdit.readOnly
    property alias inputMethodHints: textEdit.inputMethodHints

    editor: textEdit

    Repeater {
        model: Math.floor((parent.height - 30) / editor.cursorRectangle.height)
        Rectangle {
            x: 8
            y: (index+1)*editor.cursorRectangle.height+6
            height: 1; width: textArea.width-24
            color: "#D6D6D6"
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: textEdit.forceActiveFocus()
    }
    TextEdit {
        id: textEdit

        EnterKeyAction.actionId: textArea.enterKeyAction
        EnterKeyAction.label: textArea.enterKeyText
        EnterKeyAction.enabled: textArea.enterKeyEnabled

        y: 6
        focus: true
        color: "#2B2C2E"
        wrapMode: TextEdit.Wrap
        cursorVisible: activeFocus
        height: Math.max(implicitHeight, 60)
        font.pixelSize: textArea.fontPixelSize
        selectionColor: Qt.rgba(1.0, 1.0, 1.0, 0.5)
        selectedTextColor: Qt.rgba(0.0, 0.0, 0.0, 0.8)
        selectByMouse: true
        anchors { left: parent.left; right: parent.right; margins: 12 }
    }
}
