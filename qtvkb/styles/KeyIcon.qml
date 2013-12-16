/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

import QtQuick 2.0
import QtGraphicalEffects 1.0

/*!
    \qmltype KeyIcon
    \inqmlmodule QtVkb.Styles
    \brief Key icon with adjustable color.

    The KeyIcon item displays an icon with adjustable color.
*/

Item {
    /*! The icon color. */
    property alias color: overlay.color
    /*! The source image. */
    property alias source: icon.source
    Image {
        id: icon
        width: sourceSize.width * parent.height / sourceSize.height
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        visible: false
    }
    ColorOverlay {
        id: overlay
        anchors.fill: icon
        source: icon
    }
}
