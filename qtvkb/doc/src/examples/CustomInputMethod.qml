import QtQuick 2.0
import QtVkb 1.0

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
