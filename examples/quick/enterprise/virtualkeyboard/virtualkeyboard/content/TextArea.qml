/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 1.3

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
            color: Qt.rgba(1.0, 1.0, 1.0, 0.5)
        }
    }
    TextEdit {
        id: textEdit

        EnterKeyAction.actionId: textArea.enterKeyAction
        EnterKeyAction.label: textArea.enterKeyText
        EnterKeyAction.enabled: textArea.enterKeyEnabled

        y: 6
        focus: true
        color: "#EEEEEE"
        wrapMode: TextEdit.Wrap
        cursorVisible: activeFocus
        height: Math.max(implicitHeight, 60)
        font.pixelSize: textArea.fontPixelSize
        selectionColor: Qt.rgba(1.0, 1.0, 1.0, 0.5)
        selectedTextColor: Qt.rgba(0.0, 0.0, 0.0, 0.8)
        anchors { left: parent.left; right: parent.right; margins: 12 }
        onActiveFocusChanged: if (!activeFocus) deselect()
    }
}
