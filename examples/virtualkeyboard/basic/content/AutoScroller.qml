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

    property var innerFlickable
    property var outerFlickable
    property var inputItem: InputContext.inputItem

    onInputItemChanged: {
        innerFlickable = null
        outerFlickable = null
        if (inputItem !== null) {
            var parent_ = inputItem.parent
            while (parent_) {
                if (parent_.maximumFlickVelocity) {
                    if (innerFlickable) {
                        outerFlickable = parent_
                        break
                    } else {
                        innerFlickable = parent_
                    }
                }
                parent_ = parent_.parent
            }
            delayedLoading.triggered()
        }
    }

    function ensureVisible(flickable) {
        if (Qt.inputMethod.visible && inputItem && flickable && flickable.visible && flickable.interactive) {

            var verticallyFlickable = (flickable.flickableDirection === Flickable.HorizontalAndVerticalFlick || flickable.flickableDirection === Flickable.VerticalFlick
                                       || (flickable.flickableDirection === Flickable.AutoFlickDirection && flickable.contentHeight > flickable.height))
            var horizontallyFlickable = (flickable.flickableDirection === Flickable.HorizontalAndVerticalFlick || flickable.flickableDirection === Flickable.HorizontalFlick
                                         || (flickable.flickableDirection === Flickable.AutoFlickDirection && flickable.contentWidth > flickable.width))

            if ((!verticallyFlickable && !horizontallyFlickable) || !inputItem.hasOwnProperty("cursorRectangle"))
                return

            var cursorRectangle = flickable.contentItem.mapFromItem(inputItem, inputItem.cursorRectangle.x, inputItem.cursorRectangle.y)

            var oldContentY = flickable.contentY
            if (verticallyFlickable) {
                var scrollMarginVertical = (flickable && flickable.scrollMarginVertical) ? flickable.scrollMarginVertical : 10
                if (flickable.contentY >= cursorRectangle.y  - scrollMarginVertical)
                    flickable.contentY = Math.max(0, cursorRectangle.y  - scrollMarginVertical)
                else if (flickable.contentY + flickable.height <= cursorRectangle.y  + inputItem.cursorRectangle.height + scrollMarginVertical)
                    flickable.contentY = Math.min(flickable.contentHeight - flickable.height, cursorRectangle.y + inputItem.cursorRectangle.height - flickable.height + scrollMarginVertical)
            }
            if (horizontallyFlickable) {
                var scrollMarginHorizontal = (flickable && flickable.scrollMarginHorizontal) ? flickable.scrollMarginHorizontal : 10
                if (flickable.contentX >= cursorRectangle.x - scrollMarginHorizontal)
                    flickable.contentX = Math.max(0, cursorRectangle.x - scrollMarginHorizontal)
                else if (flickable.contentX + flickable.width <= cursorRectangle.x + inputItem.cursorRectangle.width + scrollMarginHorizontal)
                    flickable.contentX = Math.min(flickable.contentWidth - flickable.width, cursorRectangle.x + inputItem.cursorRectangle.width - flickable.width + scrollMarginHorizontal)
            }
        }
    }
    Timer {
        id: delayedLoading
        interval: 10
        onTriggered: {
            ensureVisible(innerFlickable)
            ensureVisible(outerFlickable)
        }
    }
    Connections {
        ignoreUnknownSignals: true
        target: inputItem && !Qt.inputMethod.animating ? Qt.inputMethod : null
        onKeyboardRectangleChanged: delayedLoading.triggered()
    }
    Connections {
        ignoreUnknownSignals: true
        target: inputItem && inputItem.activeFocus ? inputItem : null
        onCursorRectangleChanged: delayedLoading.triggered()
    }
}
