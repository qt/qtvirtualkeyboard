/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
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
import QtQuick.Enterprise.VirtualKeyboard 1.2

/*!
    \qmltype KeyboardLayout
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits ColumnLayout

    \brief Keyboard layout.

    This type is the root element of the keyboard layout.
    Use this element to build a new keyboard layout.

    Example:

    \code
    import QtQuick 2.0
    import QtQuick.Layouts 1.0
    import QtQuick.Enterprise.VirtualKeyboard 1.2

    // file: layouts/en_GB/main.qml

    KeyboardLayout {
        KeyboardRow {
            Key {
                key: Qt.Key_Q
                text: "q"
            }
            Key {
                key: Qt.Key_W
                text: "w"
            }
            Key {
                key: Qt.Key_E
                text: "e"
            }
            Key {
                key: Qt.Key_R
                text: "r"
            }
            Key {
                key: Qt.Key_T
                text: "t"
            }
            Key {
                key: Qt.Key_Y
                text: "y"
            }
        }
    }
    \endcode
*/

ColumnLayout {
    /*! Sets the input method to be used in this layout.

        This property allows a custom input method to be
        used in this layout.
    */
    property var inputMethod

    /*! Sets the input mode to be used in this layout.

        By default, the virtual keyboard attempts to preserve
        the current input mode when switching to a different
        keyboard layout.

        If the current input mode is not valid in the current
        context, the default input mode is specified by the
        input method.
    */
    property int inputMode: -1

    /*! Sets the key weight for all children keys.

        The default value is inherited from the parent element
        in the layout hierarchy.
    */
    property real keyWeight

    spacing: 0
}
