/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Styles

/*!
    \qmltype ChangeLanguageKey
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits BaseKey

    \brief Change language key for keyboard layouts.

    This key changes the current input language in the list of supported
    languages. The key has two function modes:

    \list
        \li Popup mode
        \li Toggle mode
    \endlist

    The popup mode is enabled by the \l {KeyboardStyle::languagePopupListEnabled} property.
    If enabled, a key press will open a popup list with available languages. Otherwise
    it will cycle to the next available input language.
*/

BaseKey {
    /*! If this property is true, the input language is only
        changed between the languages providing custom layout.

        For example, if only the English and Arabic languages
        provide digits layout, then other locales using the
        shared default layout are ignored.

        The default is false.
    */
    property bool customLayoutsOnly: false

    id: changeLanguageKey
    keyType: QtVirtualKeyboard.ChangeLanguageKey
    objectName: "changeLanguageKey"
    functionKey: true
    highlighted: true
    displayText: keyboard.locale.split("_")[0]
    keyPanelDelegate: keyboard.style ? keyboard.style.languageKeyPanel : undefined
    onClicked: keyboard.doKeyboardFunction(QtVirtualKeyboard.ChangeLanguage, customLayoutsOnly)
    enabled: keyboard.isKeyboardFunctionAvailable(QtVirtualKeyboard.ChangeLanguage, customLayoutsOnly)
}
