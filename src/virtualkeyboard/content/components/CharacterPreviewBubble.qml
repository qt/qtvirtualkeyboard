/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

import QtQuick
import QtQuick.VirtualKeyboard

Item {
    property bool active
    property var activeKey: keyboard.activeKey

    visible: active && activeKey !== undefined && activeKey !== null && activeKey.showPreview
    z: 1

    Loader {
        id: characterPreview
        anchors.fill: parent
        sourceComponent: keyboard.style.characterPreviewDelegate
    }

    onActiveKeyChanged: {
        if (characterPreview.item !== null) {
            if (!activeKey) {
                characterPreview.item.text = ""
                return
            }

            characterPreview.item.text = Qt.binding(function() {
                if (!activeKey)
                    return ""
                var displayText = (activeKey.keyType === QtVirtualKeyboard.FlickKey) ? activeKey.text : activeKey.displayText
                return InputContext.uppercase ? displayText.toUpperCase() : displayText
            })
            if (activeKey.keyType === QtVirtualKeyboard.FlickKey) {
                if (characterPreview.item.hasOwnProperty("flickLeft")) {
                    characterPreview.item.flickLeft = activeKey.flickLeft
                    characterPreview.item.flickRight = activeKey.flickRight
                    characterPreview.item.flickTop = activeKey.flickTop
                    characterPreview.item.flickBottom = activeKey.flickBottom
                }
            } else {
                if (characterPreview.item.hasOwnProperty("flickLeft")) {
                    characterPreview.item.flickLeft = ""
                    characterPreview.item.flickRight = ""
                    characterPreview.item.flickTop = ""
                    characterPreview.item.flickBottom = ""
                }
            }
            width = activeKey.width
            height = activeKey.height
            var position = keyboard.mapFromItem(activeKey, 0, 0)
            x = position.x
            y = position.y - height - keyboard.style.characterPreviewMargin
        }
    }
}
