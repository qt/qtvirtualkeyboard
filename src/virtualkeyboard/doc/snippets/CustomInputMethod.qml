// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.VirtualKeyboard

// file: CustomInputMethod.qml

InputMethod {
    function inputModes(locale) {
        return [InputEngine.InputMode.Latin];
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
