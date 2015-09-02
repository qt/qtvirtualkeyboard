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

.pragma library

.import "unipen_data.js" as UnipenData

function emulate(testcase, hwrInputArea, ch, instant) {
    var chKey = "0x" + (ch.charCodeAt(0) + 0x10000).toString(16).substr(-4)
    if (!UnipenData.unipenData.hasOwnProperty(chKey))
        return false
    var chData = UnipenData.unipenData[chKey]
    var scale = hwrInputArea.height / chData[".Y_DIM"]
    var strokes = UnipenData.unipenData[chKey][".PEN"]
    var boundingBox = calculateBoundingBox(strokes)
    var boxOffset = Qt.point(-boundingBox.x * scale + (hwrInputArea.width - boundingBox.width * scale) / 2, -boundingBox.y * scale + (hwrInputArea.height - boundingBox.height * scale) / 2)
    var t = 0
    for (var strokeIndex = 0; strokeIndex < strokes.length; strokeIndex++) {
        var stroke = strokes[strokeIndex]
        for (var i = 0; i < stroke.length; i++) {
            var strokeData = stroke[i]
            var pt = Qt.point(strokeData[0] * scale + boxOffset.x, strokeData[1] * scale + boxOffset.y)
            if (instant)
                t = strokeData[2]
            if (i == 0) {
                t = strokeData[2]
                testcase.mousePress(hwrInputArea, pt.x, pt.y, Qt.LeftButton, 0, strokeData[2] - t)
            } else {
                testcase.mouseMove(hwrInputArea, pt.x, pt.y, strokeData[2] - t, Qt.LeftButton)
            }
            if (i + 1 === stroke.length)
                testcase.mouseRelease(hwrInputArea, pt.x, pt.y, Qt.LeftButton, 0, instant ? 1 : strokeData[2] - t)
            t = strokeData[2]
        }
    }
    return true
}

function calculateBoundingBox(unipenStrokes) {
    var bboxLeft = 2147483647
    var bboxRight = -2147483647
    var bboxTop = 2147483647
    var bboxBottom = -2147483647
    for (var strokeIndex = 0; strokeIndex < unipenStrokes.length; strokeIndex++) {
        var stroke = unipenStrokes[strokeIndex]
        for (var i = 0; i < stroke.length; i++) {
            var strokeData = stroke[i]
            var x = strokeData[0]
            if (bboxLeft > x)
                bboxLeft = x
            if (bboxRight < x)
                bboxRight = x
            var y = strokeData[1]
            if (bboxTop > y)
                bboxTop = y
            if (bboxBottom < y)
                bboxBottom = y
        }
    }
    if (bboxLeft > bboxRight || bboxTop > bboxBottom)
        return Qt.rect(0, 0, 0, 0)
    return Qt.rect(bboxLeft, bboxTop, bboxRight - bboxLeft, bboxBottom -bboxTop)
}
