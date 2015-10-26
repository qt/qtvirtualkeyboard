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
