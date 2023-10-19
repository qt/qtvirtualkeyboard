// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Item {
    id: handwritingModeButton
    state: "unavailable"
    property bool floating
    property bool flipable
    readonly property real __minWidthHeight: Math.min(width, height)

    signal clicked()
    signal doubleClicked()

    Flipable {
        id: flipableImage
        anchors.fill: parent

        property bool flipped

        front: Image {
            sourceSize.width: handwritingModeButton.__minWidthHeight
            sourceSize.height: handwritingModeButton.__minWidthHeight
            smooth: false
            source: "qrc:/content/FloatingButton_Unavailable.svg"
        }

        back: Image {
            id: buttonImage
            sourceSize.width: handwritingModeButton.__minWidthHeight
            sourceSize.height: handwritingModeButton.__minWidthHeight
            smooth: false
            source: "qrc:/content/FloatingButton_Available.svg"
        }

        states: State {
            PropertyChanges { target: rotation; angle: 180 }
            when: flipableImage.flipped
        }

        transform: Rotation {
            id: rotation
            origin.x: flipableImage.width / 2
            origin.y: flipableImage.height / 2
            axis { x: 0; y: 1; z: 0 }
            angle: 0
        }

        transitions: Transition {
            enabled: handwritingModeButton.flipable
            NumberAnimation { target: rotation; property: "angle"; duration: 400 }
        }
    }

    states: [
        State {
            name: "available"
            PropertyChanges { target: flipableImage; flipped: true }
        },
        State {
            name: "active"
            PropertyChanges { target: flipableImage; flipped: true }
            PropertyChanges { target: buttonImage; source: "qrc:/content/FloatingButton_Active.svg" }
        }
    ]

    function snapHorizontal() {
        if (!floating)
            return
        if (mouseArea.drag.maximumX > mouseArea.drag.minimumX) {
            if (x + 20 >= mouseArea.drag.maximumX) {
                anchors.left = undefined
                anchors.right = parent.right
            } else if (x - 20 <= mouseArea.drag.minimumX) {
                anchors.right = undefined
                anchors.left = parent.left
            }
        }
    }

    function snapVertical() {
        if (!floating)
            return
        if (mouseArea.drag.maximumY > mouseArea.drag.minimumY) {
            if (y + 20 >= mouseArea.drag.maximumY) {
                anchors.top = undefined
                anchors.bottom = parent.bottom
            } else if (y - 20 <= mouseArea.drag.minimumY) {
                anchors.bottom = undefined
                anchors.top = parent.top
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag {
            target: handwritingModeButton.floating ? handwritingModeButton : undefined
            axis: Drag.XAxis | Drag.YAxis
            minimumX: 0
            maximumX: handwritingModeButton.parent.width - handwritingModeButton.width
            onMaximumXChanged: !mouseArea.drag.active && handwritingModeButton.snapHorizontal()
            minimumY: 0
            maximumY: handwritingModeButton.parent.height - handwritingModeButton.height
            onMaximumYChanged: !mouseArea.drag.active && handwritingModeButton.snapVertical()
        }
        onPressed: {
            if (!handwritingModeButton.floating)
                return
            handwritingModeButton.anchors.left = undefined
            handwritingModeButton.anchors.top = undefined
            handwritingModeButton.anchors.right = undefined
            handwritingModeButton.anchors.bottom = undefined
        }
        onReleased: {
            handwritingModeButton.snapHorizontal()
            handwritingModeButton.snapVertical()
        }
        onClicked: {
            handwritingModeButton.snapHorizontal()
            handwritingModeButton.snapVertical()
            clickTimer.restart()
        }
        onDoubleClicked: {
            clickTimer.stop()
            handwritingModeButton.snapHorizontal()
            handwritingModeButton.snapVertical()
            handwritingModeButton.doubleClicked()
        }
        Timer {
            id: clickTimer
            interval: Qt.styleHints ? Qt.styleHints.mouseDoubleClickInterval / 3 : 0
            repeat: false
            onTriggered: handwritingModeButton.clicked()
        }
    }
}
