/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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
import QtQuick.Window
import QtQuick.VirtualKeyboard

/*!
    \qmltype TraceInputArea
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits MultiPointTouchArea
    \since QtQuick.VirtualKeyboard 2.0

    \brief A specialized MultiPointTouchArea for collecting touch input data.

    This type handles the trace interaction between the touch screen and the input engine.

    The traces are rendered using the delegate from the
    \l {KeyboardStyle::}{traceCanvasDelegate} property of the current
    \l KeyboardStyle.
*/

MultiPointTouchArea {
    id: traceInputArea

    /*! Pattern recognition mode of this input area.

        The default value is \l {InputEngine::patternRecognitionModes} {InputEngine.PatternRecognitionMode.None}.
    */
    property int patternRecognitionMode: InputEngine.PatternRecognitionMode.None

    /*! List of horizontal rulers in the input area.

        The rulers are defined as a number of pixels from the top edge of the boundingBox.

        Here is an example that demonstrates how to define rulers:

        \code
            horizontalRulers: [boundingBox.height / 3, boundingBox.height / 3 * 2]
            verticalRulers: [boundingBox.width / 3, boundingBox.width / 3 * 2]
        \endcode
    */
    property var horizontalRulers

    /*! List of vertical rulers in the input area.

        The rulers are defined as a number of pixels from the left edge of the boundingBox.
    */
    property var verticalRulers

    /*! Bounding box for the trace input.

        This property is readonly and is automatically updated based on the item size
        and margins.
    */
    readonly property rect boundingBox: (width > 0 && height > 0) ?
                    Qt.rect(traceInputArea.x + traceInputArea.anchors.leftMargin,
                            traceInputArea.y + traceInputArea.anchors.topMargin,
                            traceInputArea.width,
                            traceInputArea.height) :
                    Qt.rect(0, 0, 0, 0)

    /*! Canvas type of this trace input area.

        This property can be used to distinguish between different types of canvases.
        For example, in full screen handwriting mode this property is set to \c "fullscreen", and
        in keyboard handwriting mode this property is set to \c "keyboard".
    */
    property string canvasType

    property var __activeTraceCanvases:  ({})
    property var __traceCanvasList: ([])
    property var __recycledTraceCanvasList: ([])

    Component.onCompleted: {
        for (var i = 0; i < 6; i++) {
            __recycledTraceCanvasList.push(__createTraceCanvas())
        }
    }

    function __getTraceCanvas() {
        while (__recycledTraceCanvasList.length == 0 &&
               __traceCanvasList.length >= 15 &&
               !__traceCanvasList.shift().recycle()) {}

        return __recycledTraceCanvasList.length > 0 ?
                    __recycledTraceCanvasList.pop() :
                    __createTraceCanvas()
    }

    function __createTraceCanvas() {
        var traceCanvas = keyboard.style.traceCanvasDelegate.createObject(traceInputArea)
        traceCanvas.onRecycle.connect(__onTraceCanvasRecycled)
        traceCanvas.anchors.fill = traceCanvas.parent
        return traceCanvas
    }

    function __onTraceCanvasRecycled(traceCanvas) {
        var index = __traceCanvasList.findIndex(function(otherCanvas) {
            return traceCanvas === otherCanvas
        })
        if (index !== -1) {
            __traceCanvasList.splice(index, index + 1)
        }
        __recycledTraceCanvasList.push(traceCanvas)
    }

    property var __traceCaptureDeviceInfo:
        ({
             channels: ['t'],
             sampleRate: 60,
             uniform: false,
             latency: 0.0,
             dpi: Screen.pixelDensity * 25.4
         })
    property var __traceScreenInfo:
        ({
             boundingBox: traceInputArea.boundingBox,
             horizontalRulers: traceInputArea.horizontalRulers,
             verticalRulers: traceInputArea.verticalRulers,
             canvasType: traceInputArea.canvasType
         })

    enabled: patternRecognitionMode !== InputEngine.PatternRecognitionMode.None && InputContext.inputEngine.patternRecognitionModes.indexOf(patternRecognitionMode) !== -1

    onPressed: (touchPoints) => {
        if (!keyboard.style.traceCanvasDelegate)
            return
        for (var i = 0; i < touchPoints.length; i++) {
            var traceId = touchPoints[i].pointId
            var trace = InputContext.inputEngine.traceBegin(traceId, patternRecognitionMode, __traceCaptureDeviceInfo, __traceScreenInfo)
            if (trace) {
                var traceCanvas = __getTraceCanvas()
                if (traceCanvas) {
                    traceCanvas.trace = trace
                    var index = trace.addPoint(Qt.point(touchPoints[i].x, touchPoints[i].y))
                    if (trace.channels.indexOf('t') !== -1) {
                        var dt = new Date()
                        trace.setChannelData('t', index, dt.getTime())
                    }
                    __activeTraceCanvases[traceId] = traceCanvas
                } else {
                    __activeTraceCanvases[traceId] = null
                }
            } else {
                __activeTraceCanvases[traceId] = null
            }
        }
    }

    onUpdated: (touchPoints) => {
        for (var i = 0; i < touchPoints.length; i++) {
            var traceId = touchPoints[i].pointId
            var traceCanvas = __activeTraceCanvases[traceId]
            if (traceCanvas) {
                var trace = traceCanvas.trace
                var index = trace.addPoint(Qt.point(touchPoints[i].x, touchPoints[i].y))
                if (trace.channels.indexOf('t') !== -1) {
                    var dt = new Date()
                    trace.setChannelData('t', index, dt.getTime())
                }
            }
        }
    }

    onReleased: (touchPoints) => {
        for (var i = 0; i < touchPoints.length; i++) {
            var traceId = touchPoints[i].pointId
            var traceCanvas = __activeTraceCanvases[traceId]
            if (traceCanvas) {
                if (traceCanvas.trace) {
                    traceCanvas.trace.final = true
                    InputContext.inputEngine.traceEnd(traceCanvas.trace)
                }
                __traceCanvasList.push(traceCanvas)
                __activeTraceCanvases[traceId] = null
            }
        }
    }

    onCanceled: (touchPoints) => {
        for (var i = 0; i < touchPoints.length; i++) {
            var traceId = touchPoints[i].pointId
            var traceCanvas = __activeTraceCanvases[traceId]
            if (traceCanvas) {
                if (traceCanvas.trace) {
                    traceCanvas.trace.final = true
                    traceCanvas.trace.canceled = true
                    InputContext.inputEngine.traceEnd(traceCanvas.trace)
                }
                __traceCanvasList.push(traceCanvas)
                __activeTraceCanvases[traceId] = null
            }
        }
    }
}
