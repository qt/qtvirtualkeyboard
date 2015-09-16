/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
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
