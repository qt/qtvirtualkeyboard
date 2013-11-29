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
import QtQuick.Layouts 1.0

Item {
    id: keyItem

    property real weight: parent.keyWeight
    property string text: ""
    property string displayText: text
    property var alternativeKeys: []
    property int key: Qt.Key_unknown
    property bool active: false
    property bool repeat: false
    property bool highlighted: false
    property bool functionKey: false
    property bool showPreview: !functionKey
    property bool enabled: true
    property bool pressed: enabled && active
    property bool uppercased: keyboard.uppercased
    property alias keyPanelDelegate: keyPanel.sourceComponent

    Layout.minimumWidth: keyPanel.implicitWidth
    Layout.minimumHeight: keyPanel.implicitHeight
    Layout.preferredWidth: weight
    Layout.fillWidth: true
    Layout.fillHeight: true

    Loader {
        id: keyPanel
        anchors.fill: parent
        onStatusChanged: if (status == Loader.Ready) keyPanel.item.control = keyItem
    }

    signal clicked
}
