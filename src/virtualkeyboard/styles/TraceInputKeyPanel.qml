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

/*!
    \qmltype TraceInputKeyPanel
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard.Styles
    \brief A base type of the trace input key.
    \ingroup qtvirtualkeyboard-styles-qml
    \since QtQuick.Enterprise.VirtualKeyboard 1.4

    This type provides panel for decorating TraceInputKey
    items in the keyboard layout.
*/

Item {
    /*! Provides access to properties in TraceInputKey.

        A list of available properties in control:
        \list
            \li \c patternRecognitionMode Pattern recognition mode of this input area
            \li \c horizontalRulers A list of horizontal rulers
            \li \c verticalRulers A list of vertical rulers
            \li \c boundingBox Bounding box for the trace input
        \endlist
    */
    property Item control

    /*! Sets margins of the trace input area.

        The margins affect to the bounding box of the trace input area.
    */
    property real traceMargins
}
