/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
import QtQuick.VirtualKeyboard

Item {
    property bool active
    property alias listView: listView
    property point origin
    signal clicked
    LayoutMirroring.enabled: false
    LayoutMirroring.childrenInherit: true

    z: 1
    visible: active
    anchors.fill: parent

    ListModel {
        id: listModel
    }

    ListView {
        id: listView
        spacing: 0
        model: listModel
        currentIndex: -1
        delegate: keyboard.style.functionPopupListDelegate
        highlight: keyboard.style.functionPopupListHighlight ? keyboard.style.functionPopupListHighlight : defaultHighlight
        highlightMoveDuration: 0
        highlightResizeDuration: 0
        keyNavigationWraps: true
        orientation: ListView.Horizontal
        width: contentItem.childrenRect.width
        height: contentItem.childrenRect.height
        x: {
            var result = origin.x
            if (count > 0) {
                const item = itemAtIndex(0)
                if (item) {
                    result -= Math.round(item.width / 2)
                }
            }
            return result
        }
        y: origin.y - height
        Component {
            id: defaultHighlight
            Item {}
        }
    }

    Loader {
        id: backgroundLoader
        sourceComponent: keyboard.style.functionPopupListBackground
        anchors.fill: listView
        z: -1
        Binding {
            target: backgroundLoader.item
            property: "view"
            value: listView
            when: backgroundLoader.item && backgroundLoader.item.hasOwnProperty("view")
        }
    }

    onClicked: {
        if (active && listView.currentIndex >= 0 && listView.currentIndex < listView.model.count) {
            const listElement = listView.model.get(listView.currentIndex)
            keyboard.doKeyboardFunction(listElement.keyboardFunction)
        }
    }

    function open(key, originX, originY) {
        listModel.clear()
        for (const keyboardFunction of [
                 QtVirtualKeyboard.HideInputPanel,
                 QtVirtualKeyboard.ChangeLanguage,
                 QtVirtualKeyboard.ToggleHandwritingMode,
             ]) {
            if (keyboard.isKeyboardFunctionAvailable(keyboardFunction)) {
                const listElement = {
                    keyboardFunction: keyboardFunction
                }
                listModel.append(listElement)
            }
        }
        origin = Qt.binding(function() {
            return Qt.point(Math.min(Math.max(0, originX), width - listView.width), originY)
        })
        listView.currentIndex = (listModel.count > 0) ? 0 : -1
        active = listView.currentIndex !== -1
        return active
    }

    function move(pt) {
        var listPt = mapToItem(listView, pt.x, pt.y)
        var newIndex = listView.indexAt(listPt.x, Math.max(1, Math.min(listView.height - 1, listPt.y)))
        if (newIndex !== listView.currentIndex) {
            listView.currentIndex = newIndex
        }
    }

    function close() {
        listView.currentIndex = -1
        active = false
    }
}
