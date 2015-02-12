/****************************************************************************
**
** Copyright (C) 2015 Digia Plc
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
import "TraceUtils.js" as TraceUtils

/*!
    \qmltype TraceCanvas
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard.Styles
    \brief A specialized Canvas type for rendering Trace objects.
    \ingroup qtvirtualkeyboard-styles-qml
    \inherits Canvas
    \since QtQuick.Enterprise.VirtualKeyboard 1.4

    This type provides capabilities for rendering Trace objects on the screen.

    To make the Trace rendering available in the keyboard, this type must be
    declared as the \l {KeyboardStyle::traceCanvasDelegate}
    {KeyboardStyle.traceCanvasDelegate} component.

    \code
        traceCanvasDelegate: TraceCanvas {
        }
    \endcode

    Custom drawing attributes can be initialized in the Canvas.available
    signal. For example:

    \code
        onAvailableChanged: {
            if (!available)
                return;
            var ctx = getContext("2d")
            ctx.lineWidth = 8 * scaleHint
            ctx.lineCap = "round"
            ctx.strokeStyle = Qt.rgba(0xFF, 0xFF, 0xFF)
            ctx.fillStyle = ctx.strokeStyle
        }
    \endcode

    The type offers built-in options for Trace rendering. Currently
    the following rendering options are available:

    \list
        \li \c renderSmoothedLine Renders smoothed line with round corners (the default)
    \endlist

    The rendering function can be changed with the renderFunction property.

    \code
        renderFunction: renderSmoothedLine
    \endcode

    Custom rendering function is also supported. Consider the following example:

    \code
        renderFunction: renderCustomLine

        function renderCustomLine() {
            getContext("2d")
            var points = trace.points()

            ...
        }
    \endcode
*/

Canvas {
    id: canvas

    /*! Provides access to \l Trace object.
    */
    property var trace

    /*! Enables auto destruction mode.

        If enabled, this item will be destroyed when the \c trace object is
        destroyed.

        The default value is false.
    */
    property bool autoDestroy

    /*! Specifies the approximate delay in milliseconds, counted from the beginning of the
        auto destruction, before the object is to be destroyed.

        This delay makes it possible, for example, to animate the item before destruction.

        The default value is 0.
    */
    property int autoDestroyDelay

    /*! This property defines the rendering function.

        The default value is \c renderSmoothedLine
    */
    property var renderFunction: renderSmoothedLine

    property int __renderPos

    /*! Renders smoothed line with round corners.

        This function is incremental and renders only the new part added to the Trace.

        This function does not alter any of the canvas attributes (i.e. they can be set elsewhere.)
    */
    function renderSmoothedLine() {
        __renderPos = TraceUtils.renderSmoothedLine(getContext("2d"), trace, __renderPos)
    }

    onTraceChanged: if (trace === null && autoDestroy) destroy(autoDestroyDelay)

    Connections {
        target: trace ? trace : null
        onLengthChanged: if (renderFunction) canvas.requestAnimationFrame(renderFunction)
        onFinalChanged: if (renderFunction) canvas.requestAnimationFrame(renderFunction)
    }
}
