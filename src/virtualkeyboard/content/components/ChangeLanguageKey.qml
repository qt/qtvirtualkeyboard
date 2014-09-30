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
    \qmltype ChangeLanguageKey
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits BaseKey

    \brief Change language key for keyboard layouts.

    Changes the current input language to the next one in the list of supported
    languages.
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

    functionKey: true
    displayText: keyboard.locale.split("_")[0]
    keyPanelDelegate: keyboard.style ? keyboard.style.languageKeyPanel : undefined
    onClicked: keyboard.changeInputLanguage(customLayoutsOnly)
    enabled: keyboard.canChangeInputLanguage(customLayoutsOnly)
}
