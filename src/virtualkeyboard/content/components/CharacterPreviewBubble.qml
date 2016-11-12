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
            characterPreview.item.text = InputContext.shift ? activeKey.text.toUpperCase() : activeKey.text
            width = activeKey.width
            height = activeKey.height
            var position = keyboard.mapFromItem(activeKey, 0, 0)
            x = position.x
            y = position.y - height - keyboard.style.characterPreviewMargin
        }
    }
}
