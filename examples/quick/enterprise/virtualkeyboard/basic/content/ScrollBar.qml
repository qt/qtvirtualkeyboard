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

Item {
    property var scrollArea: parent

    width: 6
    opacity: scrollArea && scrollArea.movingVertically ? 1.0 : 0.0
    visible: scrollArea && scrollArea.contentHeight >= scrollArea.height
    anchors { right: parent.right; top: parent.top; bottom: parent.bottom; margins: 2 }

    Behavior on opacity { NumberAnimation { properties: "opacity"; duration: 600 } }

    function size() {
        var nh = scrollArea.visibleArea.heightRatio * height
        var ny = scrollArea.visibleArea.yPosition * height
        return ny > 3 ? Math.min(nh, Math.ceil(height - 3 - ny)) : nh + ny
    }
    Rectangle {
        x: 1
        y: scrollArea ? Math.max(2, scrollArea.visibleArea.yPosition * parent.height) : 0
        height: scrollArea ? size() : 0
        width: parent.width - 2
        color: Qt.rgba(1.0, 1.0, 1.0, 0.5)
        radius: 1
    }
}
