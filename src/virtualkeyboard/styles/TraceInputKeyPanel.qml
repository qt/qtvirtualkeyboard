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

/*!
    \qmltype TraceInputKeyPanel
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard.Styles
    \brief A base type of the trace input key.
    \ingroup qtvirtualkeyboard-styles-qml
    \since QtQuick.Enterprise.VirtualKeyboard 2.0

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
