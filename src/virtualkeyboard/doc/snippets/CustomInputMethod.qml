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
import Qt.Quick.Enterprise.VirtualKeyboard 1.0

// file: CustomInputMethod.qml

InputMethod {
    function inputModes(locale) {
        return [InputEngine.Latin];
    }

    function setInputMode(locale, inputMode) {
        return true
    }

    function setTextCase(textCase) {
        return true
    }

    function reset() {
        // TODO: reset the input method without modifying input context
    }

    function update() {
        // TODO: commit current state and update the input method
    }

    function keyEvent(key, text, modifiers) {
        var accept = false
        // TODO: Handle key and set accept or fallback to default processing
        return accept;
    }
}
