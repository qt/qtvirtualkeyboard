// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.VirtualKeyboard

Item {
    property bool active
    property Item activeKey: keyboard.activeKey

    visible: active && activeKey !== undefined && activeKey !== null && activeKey.showPreview
    z: 1

    Loader {
        id: characterPreview
        anchors.fill: parent
        sourceComponent: keyboard.style.characterPreviewDelegate
    }

    Binding {
        target: characterPreview.item
        property: "text"
        value: {
            if (!activeKey)
                return ""

            const displayText = (activeKey.keyType === QtVirtualKeyboard.KeyType.FlickKey) ? activeKey.text : activeKey.displayText
            return InputContext.uppercase ? displayText.toUpperCase() : displayText
        }
        when: activeKey && characterPreview.item
    }

    onActiveKeyChanged: {
        if (characterPreview.item !== null) {
            if (!activeKey)
                return

            if (activeKey.keyType === QtVirtualKeyboard.KeyType.FlickKey) {
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
