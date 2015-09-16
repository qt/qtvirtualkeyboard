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
        if (activeKey && characterPreview.item !== null) {
            characterPreview.item.text = keyboard.uppercased ? activeKey.text.toUpperCase() : activeKey.text
            width = activeKey.width
            height = activeKey.height
            var position = keyboard.mapFromItem(activeKey, 0, 0)
            x = position.x
            y = position.y - height - keyboard.style.characterPreviewMargin
        }
    }
}
