/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

import QtQuick 2.0

/*!
    \qmltype KeyIcon
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard.Styles
    \brief Key icon with adjustable color.
    \ingroup qtvirtualkeyboard-styles-qml

    The KeyIcon item displays an icon with adjustable color.
*/

Item {
    /*! The icon color. */
    property alias color: overlay.color
    /*! The source image. */
    property alias source: icon.source
    Image {
        id: icon
        sourceSize.height: parent.height
        sourceSize.width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        visible: false
    }
    ShaderEffect {
        id: overlay
        property color color
        property variant texture: icon
        anchors.fill: icon
        fragmentShader: "
            uniform lowp vec4 color;
            uniform lowp float qt_Opacity;
            uniform lowp sampler2D texture;
            varying highp vec2 qt_TexCoord0;
            void main() {
                highp vec4 sample = texture2D(texture, qt_TexCoord0) * qt_Opacity;
                gl_FragColor = vec4(color.rgb, 1.0) * sample.a;
            }
            "
    }
}
