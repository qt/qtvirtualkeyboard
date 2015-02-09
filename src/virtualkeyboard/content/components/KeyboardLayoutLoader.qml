/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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
    \qmltype KeyboardLayoutLoader
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits Loader
    \since QtQuick.Enterprise.VirtualKeyboard 1.1

    \brief Allows dynamic loading of keyboard layout.

    This type is useful for keyboard layouts consisting of multiple pages of keys.

    A single keyboard layout (a page) is defined by using the Component
    as a container. The active keyboard layout can then be changed by
    setting the sourceComponent property to a different value.

    Example:

    \code
    import QtQuick 2.0
    import QtQuick.Layouts 1.0
    import QtQuick.Enterprise.VirtualKeyboard 1.2

    // file: layouts/en_GB/symbols.qml

    KeyboardLayoutLoader {
        property bool secondPage
        onVisibleChanged: if (!visible) secondPage = false
        sourceComponent: secondPage ? page2 : page1
        Component {
            id: page1
            KeyboardLayout {
                // Keyboard layout definition for page 1
            }
        }
        Component {
            id: page2
            KeyboardLayout {
                // Keyboard layout definition for page 2
            }
        }
    }
    \endcode
*/

Loader {
    /*! Sets the input method for all the keyboard layouts loaded
        in this context.

        The input method can either be set separately for each keyboard
        layout, or commonly at this context. If set separately, then this
        property should not be modified.
    */
    property var inputMethod: item.inputMethod

    /*! This function may be overridden by the keyboard layout
        to create the input method object dynamically. The default
        implementation forwards the call to the child keyboard
        layout.

        The input method object created by this function can outlive
        keyboard layout transitions in certain cases. In particular,
        this applies to the transitions between the symbol and the
        main view.
    */
    function createInputMethod() {
        return item ? item.createInputMethod() : null
    }

    /*! Sets the input mode for all the keyboard layouts loaded
        in this context.

        The input mode can either be set separately for each keyboard
        layout, or commonly at this context. If set separately, then this
        property should not be modified.
    */
    property int inputMode: item.inputMode

    property int __updateCount

    onItemChanged: if (item && __updateCount++ > 0) keyboard.updateInputMethod()
}
