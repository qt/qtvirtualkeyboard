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

import QtTest 1.0
import QtQuick 2.0

Rectangle {
    id: container
    width: 400
    height: 400

    Component {
        id: textInputComp
        TextEdit {
            anchors.fill: parent
            visible: true
            focus: true
        }
    }

    TestCase {
        id: testcase
        name: "tst_plugin"
        when: windowShown

        property var inputPanel: null
        property var textInput: null

        function initTestCase() {
            var inputPanelComp = Qt.createComponent("inputpanel/inputpanel.qml")
            compare(inputPanelComp.status, Component.Ready, "Failed to create InputPanel component. Please set QT_IM_MODULE=qtvirtualkeyboard.")
            inputPanel = inputPanelComp.createObject(container)
            inputPanel.testcase = testcase
            inputPanel.keyboardLayoutsAvailableSpy.wait()
            textInput = textInputComp.createObject(container)
        }

        function cleanupTestCase() {
            if (textInput)
                textInput.destroy()
            if (inputPanel)
                inputPanel.destroy()
        }

        function prepareTest(data) {
            container.forceActiveFocus()
            if (data !== undefined && data.hasOwnProperty("initText")) {
                textInput.text = data.initText
                textInput.cursorPosition = data.hasOwnProperty("initCursorPosition") ? data.initCursorPosition : textInput.text.length
                if (data.hasOwnProperty("selectionStart") && data.hasOwnProperty("selectionEnd")) {
                    textInput.select(data.selectionStart, data.selectionEnd)
                }
            } else {
                textInput.text = ""
            }
            textInput.inputMethodHints = data !== undefined && data.hasOwnProperty("initInputMethodHints") ? data.initInputMethodHints : Qt.ImhNone
            textInput.forceActiveFocus()
            var locale = data !== undefined && data.hasOwnProperty("initLocale") ? data.initLocale : "en_GB"
            if (!inputPanel.isLocaleSupported(locale))
                expectFail("", "Input locale not enabled")
            verify(inputPanel.setLocale(locale))
            if (data !== undefined && data.hasOwnProperty("initInputMode"))
                verify(inputPanel.setInputMode(inputPanel.mapInputMode(data.initInputMode)))
            Qt.inputMethod.show()
            waitForRendering(inputPanel)
            verify(inputPanel.visible === true)
        }

        function test_versionCheck_data() {
            return [
                // Note: Add new import versions here
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard 1.0; \
                        InputPanel {}" },
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard 1.1; \
                        InputPanel {}" },
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard 1.2; \
                        InputPanel {}" },
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard 1.3; \
                        InputPanel {}" },
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard.Styles 1.0; \
                        KeyboardStyle {}" },
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard.Styles 1.1; \
                        KeyboardStyle {}" },
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard.Styles 1.2; \
                        KeyboardStyle {}" },
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard.Styles 1.3; \
                        KeyboardStyle {}" },
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard.Settings 1.0; \
                        Item { property var styleName: VirtualKeyboardSettings.styleName }" },
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard.Settings 1.1; \
                        Item { property var styleName: VirtualKeyboardSettings.styleName }" },
                { qml: "import QtQuick 2.0; \
                        import QtQuick.Enterprise.VirtualKeyboard.Settings 1.2; \
                        Item { property var styleName: VirtualKeyboardSettings.styleName }" },
            ]
        }

        function test_versionCheck(data) {
            var obj = null
            var errorMsg
            try {
                obj = Qt.createQmlObject(data.qml, testcase)
            } catch (e) {
                errorMsg = e
            }
            verify(obj !== null, errorMsg)
            if (obj)
                obj.destroy()
        }

        function test_focusShowKeyboard() {
            container.forceActiveFocus()
            verify(inputPanel.visible === false)

            mousePress(textInput, 0, 0)
            waitForRendering(inputPanel)
            mouseRelease(textInput, 0, 0)
            verify(inputPanel.visible === true)

            container.forceActiveFocus()
            verify(inputPanel.visible === false)
        }

        function test_inputMethodShowKeyboard() {
            container.forceActiveFocus()
            Qt.inputMethod.hide()
            verify(inputPanel.visible === false)

            Qt.inputMethod.show()
            waitForRendering(inputPanel)
            verify(inputPanel.visible === true)

            Qt.inputMethod.hide()
            verify(inputPanel.visible === false)
        }

        function test_keyPress_data() {
            return [
                // normal key press
                { initText: "", initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, inputKey: Qt.Key_A, outputKeyCountMin: 1, outputKey: Qt.Key_A, preview: true, outputKeyText: "a", outputKeyModifiers: Qt.NoModifier, outputKeyRepeat: false, outputText: "a" },
                { initText: "", initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, inputKey: Qt.Key_AsciiTilde, outputKeyCountMin: 1, outputKey: Qt.Key_AsciiTilde, preview: true, outputKeyText: "~", outputKeyModifiers: Qt.NoModifier, outputKeyRepeat: false, outputText: "~" },
                // alternative key press, i.e. long key press
                { initText: "", initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, inputKey: "\u00E4", outputKeyCountMin: 1, outputKey: Qt.Key_A, preview: true, outputKeyText: "\u00E4", outputKeyModifiers: Qt.NoModifier, outputKeyRepeat: false, outputText: "\u00E4" },
                // function key press
                { initText: "x", initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, inputKey: Qt.Key_Shift, outputKeyCountMin: 1, outputKey: Qt.Key_Shift, preview: false, outputKeyText: "", outputKeyModifiers: Qt.NoModifier, outputKeyRepeat: false, outputText: "x" },
                { initText: "x", initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, inputKey: Qt.Key_Backspace, outputKeyCountMin: 1, outputKey: Qt.Key_Backspace, preview: false, outputKeyText: "", outputKeyModifiers: Qt.NoModifier, outputKeyRepeat: false, outputText: "" },
                { initText: "xxxxxx", initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, inputKey: Qt.Key_Backspace, keyHold: 600 + 8 * 50, outputKeyCountMin: 6, outputKey: Qt.Key_Backspace, preview: false, outputKeyText: "", outputKeyModifiers: Qt.NoModifier, outputKeyRepeat: true, outputText: "" },
            ]
        }

        function test_keyPress(data) {
            prepareTest(data)

            inputPanel.characterPreviewBubbleSpy.clear()
            inputPanel.virtualKeyClickedSpy.clear()
            if (data.hasOwnProperty("keyHold")) {
                inputPanel.virtualKeyPress(data.inputKey)
                wait(data.keyHold)
                inputPanel.virtualKeyRelease()
            } else {
                inputPanel.virtualKeyClick(data.inputKey)
            }

            compare(inputPanel.characterPreviewBubbleSpy.count, data.preview ? 2 : 0) // show + hide == 2
            verify(inputPanel.virtualKeyClickedSpy.count >= data.outputKeyCountMin)
            for (var i = 0; i < inputPanel.virtualKeyClickedSpy.count; i++) {
                compare(inputPanel.virtualKeyClickedSpy.signalArguments[i][0], data.outputKey)
                compare(inputPanel.virtualKeyClickedSpy.signalArguments[i][1], data.outputKeyText)
                compare(inputPanel.virtualKeyClickedSpy.signalArguments[i][2], data.outputKeyModifiers)
                compare(inputPanel.virtualKeyClickedSpy.signalArguments[i][3], data.outputKeyRepeat)
            }

            compare(textInput.text, data.outputText)
        }

        function test_keyReleaseInaccuracy() {
            prepareTest({ initInputMethodHints: Qt.ImhNoPredictiveText })

            inputPanel.virtualKeyClickedSpy.clear()
            verify(inputPanel.virtualKeyPress(Qt.Key_A))
            var keyObj = inputPanel.findVirtualKey(Qt.Key_A)
            inputPanel.virtualKeyPressPoint = inputPanel.mapFromItem(keyObj, keyObj.width * 1.1, keyObj.height / 2)
            mouseMove(inputPanel, inputPanel.virtualKeyPressPoint.x, inputPanel.virtualKeyPressPoint.y)
            verify(inputPanel.virtualKeyRelease())

            compare(inputPanel.virtualKeyClickedSpy.count, 1)
            compare(inputPanel.virtualKeyClickedSpy.signalArguments[0][0], Qt.Key_A)
            compare(inputPanel.virtualKeyClickedSpy.signalArguments[0][1], "A")
            compare(inputPanel.virtualKeyClickedSpy.signalArguments[0][2], Qt.ShiftModifier)
            compare(inputPanel.virtualKeyClickedSpy.signalArguments[0][3], false)

            Qt.inputMethod.commit()
            waitForRendering(inputPanel)
            compare(textInput.text, "A")
        }

        function test_inputLocale_data() {
            return [
                { initLocale: "ar_AR", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "\u0645\u0631\u062D\u0628\u0627", outputText: "\u0645\u0631\u062D\u0628\u0627" },
                { initLocale: "fa_FA", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "\u0633\u0644\u0627\u0645", outputText: "\u0633\u0644\u0627\u0645" },
                { initLocale: "da_DK", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "hej", outputText: "Hej" },
                { initLocale: "de_DE", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "hallo", outputText: "Hallo" },
                { initLocale: "en_GB", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "hello", outputText: "Hello" },
                { initLocale: "es_ES", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "hola", outputText: "Hola" },
                { initLocale: "hi_IN", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "\u0928\u092E\u0938\u094D\u0915\u093E\u0930", outputText: "\u0928\u092E\u0938\u094D\u0915\u093E\u0930" },
                { initLocale: "fi_FI", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "hei", outputText: "Hei" },
                { initLocale: "fr_FR", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "bonjour", outputText: "Bonjour" },
                { initLocale: "it_IT", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "ciao", outputText: "Ciao" },
                { initLocale: "ja_JP", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "watashi", outputText: "\u308F\u305F\u3057" },
                { initLocale: "nb_NO", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "hallo", outputText: "Hallo" },
                { initLocale: "pl_PL", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "cze\u015B\u0107", outputText: "Cze\u015B\u0107" },
                { initLocale: "pt_PT", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "ol\u00E1", outputText: "Ol\u00E1" },
                { initLocale: "ru_RU", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "\u043F\u0440\u0438\u0432\u0435\u0442", outputText: "\u041F\u0440\u0438\u0432\u0435\u0442" },
                { initLocale: "sv_SE", initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "hall\u00E5", outputText: "Hall\u00E5" }
            ]
        }

        function test_inputLocale(data) {
            prepareTest(data)

            compare(Qt.inputMethod.locale.name, Qt.locale(data.initLocale).name)
            for (var inputIndex in data.inputSequence) {
                verify(inputPanel.virtualKeyClick(data.inputSequence[inputIndex]))
            }

            Qt.inputMethod.commit()
            waitForRendering(inputPanel)
            compare(textInput.text, data.outputText)
        }

        function test_inputMethodHints_data() {
            return [
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhUppercaseOnly, inputSequence: "uppercase text? yes.", outputText: "UPPERCASE TEXT? YES." },
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhLowercaseOnly, inputSequence: "uppercase text? no.", outputText: "uppercase text? no." },
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhDigitsOnly, inputSequence: "1234567890.", outputText: "1234567890." },
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhFormattedNumbersOnly, inputSequence: "1234567890+-,.()", outputText: "1234567890+-,.()" },
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhDialableCharactersOnly, inputSequence: "1234567890+*#", outputText: "1234567890+*#" },
            ]
        }

        function test_inputMethodHints(data) {
            prepareTest(data)

            for (var inputIndex in data.inputSequence) {
                verify(inputPanel.virtualKeyClick(data.inputSequence[inputIndex]))
            }

            Qt.inputMethod.commit()
            waitForRendering(inputPanel)
            compare(textInput.text, data.outputText)
        }

        function test_toggleShift_data() {
            return [
                { initInputMethodHints: Qt.ImhNoPredictiveText, toggleShiftCount: 0, inputSequence: "aaa bbb", outputText: "Aaa bbb", autoCapitalizationEnabled: true, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText, toggleShiftCount: 1, inputSequence: "aaa bbb", outputText: "aaa bbb", autoCapitalizationEnabled: true, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText, toggleShiftCount: 2, inputSequence: "aaa bbb", outputText: "Aaa bbb", autoCapitalizationEnabled: true, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText, toggleShiftCount: 3, inputSequence: "aaa bbb", outputText: "AAA BBB", autoCapitalizationEnabled: true, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText, toggleShiftCount: 4, inputSequence: "aaa bbb", outputText: "aaa bbb", autoCapitalizationEnabled: true, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText, toggleShiftCount: 5, inputSequence: "aaa bbb", outputText: "Aaa bbb", autoCapitalizationEnabled: true, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText, toggleShiftCount: 6, inputSequence: "aaa bbb", outputText: "AAA BBB", autoCapitalizationEnabled: true, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, toggleShiftCount: 0, inputSequence: "aaa bbb", outputText: "aaa bbb", autoCapitalizationEnabled: false, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, toggleShiftCount: 1, inputSequence: "aaa bbb", outputText: "AAA BBB", autoCapitalizationEnabled: false, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, toggleShiftCount: 2, inputSequence: "aaa bbb", outputText: "aaa bbb", autoCapitalizationEnabled: false, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, toggleShiftCount: 3, inputSequence: "aaa bbb", outputText: "AAA BBB", autoCapitalizationEnabled: false, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText, initLocale: "ar_AR", toggleShiftCount: 0, inputSequence: "\u0645\u0631\u062D\u0628\u0627", outputText: "\u0645\u0631\u062D\u0628\u0627", autoCapitalizationEnabled: false, toggleShiftEnabled: true },
                { initInputMethodHints: Qt.ImhNoPredictiveText, initLocale: "hi_IN", toggleShiftCount: 0, inputSequence: "\u0928\u092E\u0938\u094D\u0915\u093E\u0930", outputText: "\u0928\u092E\u0938\u094D\u0915\u093E\u0930", autoCapitalizationEnabled: false, toggleShiftEnabled: true },
            ]
        }

        function test_toggleShift(data) {
            prepareTest(data)

            compare(inputPanel.autoCapitalizationEnabled, data.autoCapitalizationEnabled)
            compare(inputPanel.toggleShiftEnabled, data.toggleShiftEnabled)
            for (var i = 0; i < data.toggleShiftCount; i++) {
                inputPanel.toggleShift()
            }
            for (var inputIndex in data.inputSequence) {
                verify(inputPanel.virtualKeyClick(data.inputSequence[inputIndex]))
            }

            Qt.inputMethod.commit()
            waitForRendering(inputPanel)
            compare(textInput.text, data.outputText)
        }

        function test_symbolMode() {
            prepareTest({ initInputMethodHints: Qt.ImhNoPredictiveText })

            verify(inputPanel.keyboard.symbolMode === false)
            inputPanel.virtualKeyClick(Qt.Key_Context1)
            waitForRendering(inputPanel)
            verify(inputPanel.keyboard.symbolMode === true)
            verify(inputPanel.virtualKeyClick(Qt.Key_Plus))
            verify(inputPanel.keyboard.symbolMode === true)
            verify(inputPanel.virtualKeyClick(Qt.Key_Dollar))
            verify(inputPanel.keyboard.symbolMode === true)
            inputPanel.virtualKeyClick(Qt.Key_Context1)
            waitForRendering(inputPanel)
            verify(inputPanel.keyboard.symbolMode === false)

            Qt.inputMethod.commit()
            compare(textInput.text, "+$")
        }

        function test_dragSymbolMode() {
            prepareTest({ initInputMethodHints: Qt.ImhNoPredictiveText })

            verify(inputPanel.keyboard.symbolMode === false)
            inputPanel.dragSymbolModeSpy.clear()
            inputPanel.virtualKeyPress(Qt.Key_Context1)
            inputPanel.dragSymbolModeSpy.wait()
            waitForRendering(inputPanel)
            verify(inputPanel.keyboardInputArea.dragSymbolMode === true)

            inputPanel.characterPreviewBubbleSpy.clear()
            inputPanel.virtualKeyClickedSpy.clear()
            verify(inputPanel.virtualKeyDrag(Qt.Key_Plus))
            compare(inputPanel.characterPreviewBubbleSpy.count, 1)
            compare(inputPanel.virtualKeyClickedSpy.count, 0)
            inputPanel.virtualKeyRelease()
            waitForRendering(inputPanel)
            compare(inputPanel.virtualKeyClickedSpy.signalArguments[0][0], Qt.Key_Plus)
            compare(inputPanel.virtualKeyClickedSpy.signalArguments[0][1], "+")
            compare(inputPanel.virtualKeyClickedSpy.signalArguments[0][2], Qt.ShiftModifier)
            compare(inputPanel.virtualKeyClickedSpy.signalArguments[0][3], false)
            verify(inputPanel.keyboardInputArea.dragSymbolMode === false)
            verify(inputPanel.keyboard.symbolMode === false)

            Qt.inputMethod.commit()
            waitForRendering(inputPanel)
            compare(textInput.text, "+")
        }

        function test_themeChange() {
            prepareTest()

            var origStyle = inputPanel.style()
            inputPanel.setStyle("default")
            inputPanel.styleSpy.clear()

            inputPanel.setStyle("retro")
            inputPanel.styleSpy.wait()
            waitForRendering(inputPanel)

            inputPanel.setStyle("default")
            inputPanel.styleSpy.wait()
            waitForRendering(inputPanel)

            compare(inputPanel.styleSpy.count, 2)

            inputPanel.setStyle(origStyle)
            waitForRendering(inputPanel)
        }

        function test_soundEffects() {
            prepareTest({ initInputMethodHints: Qt.ImhNoPredictiveText })

            wait(500)
            inputPanel.soundEffectSpy.clear()

            verify(inputPanel.virtualKeyClick(Qt.Key_A))
            wait(500)
            if (!inputPanel.keyboard.soundEffect.available || !inputPanel.keyboard.soundEffect.enabled)
                expectFail("", "Sound effects not enabled")
            compare(inputPanel.soundEffectSpy.count, 2)
        }

        function test_navigationKeyInputSequence_data() {
            return [
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, inputSequence: "\u00E1\u017C", outputText: "\u00E1\u017C" },
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, inputSequence: "~123qwe", outputText: "~123qwe" },
                { initInputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase, inputSequence: [ Qt.Key_Shift, Qt.Key_V, Qt.Key_K, Qt.Key_B, Qt.Key_Return ], outputText: "VKB\n" },
            ]
        }

        function test_navigationKeyInputSequence(data) {
            prepareTest(data)

            if (!inputPanel.activateNavigationKeyMode())
                expectFail("", "Arrow key navigation not enabled")
            verify(inputPanel.naviationHighlight.visible)

            for (var inputIndex in data.inputSequence) {
                verify(inputPanel.navigationKeyClick(data.inputSequence[inputIndex]))
            }

            Qt.inputMethod.commit()
            waitForRendering(inputPanel)
            compare(textInput.text, data.outputText)
        }

        function test_navigationCursorWrap_data() {
            return [
                { initialKey: Qt.Key_Q, navigationKey: Qt.Key_Up, navigationKeyRepeat: 4 },
                { initialKey: Qt.Key_Q, navigationKey: Qt.Key_Down, navigationKeyRepeat: 4 },
                { initialKey: Qt.Key_T, navigationKey: Qt.Key_Up, navigationKeyRepeat: 4 },
                { initialKey: Qt.Key_T, navigationKey: Qt.Key_Down, navigationKeyRepeat: 4 },
                { initialKey: Qt.Key_Backspace, navigationKey: Qt.Key_Up, navigationKeyRepeat: 4 },
                { initialKey: Qt.Key_Backspace, navigationKey: Qt.Key_Down, navigationKeyRepeat: 4 },
                { initialKey: Qt.Key_Backspace, navigationKeySequence: [ Qt.Key_Right, Qt.Key_Left ] },
                { initialKey: Qt.Key_Return, navigationKeySequence: [ Qt.Key_Right, Qt.Key_Left ] },
                { initialKey: Qt.Key_Shift, navigationKeySequence: [ Qt.Key_Left, Qt.Key_Right ] },
                { initialKey: Qt.Key_Context1, navigationKeySequence: [ Qt.Key_Left, Qt.Key_Right ] },
                { initialKey: Qt.Key_Q, navigationKeySequence: [ Qt.Key_Left, Qt.Key_Right ] },
            ]
        }

        function test_navigationCursorWrap(data) {
            prepareTest()

            if (!inputPanel.activateNavigationKeyMode())
                expectFail("", "Arrow key navigation not enabled")
            verify(inputPanel.naviationHighlight.visible)

            verify(inputPanel.navigateToKey(data.initialKey))
            var initialKeyObj = inputPanel.keyboardInputArea.initialKey

            if (data.hasOwnProperty("navigationKey")) {
                for (var i = 0; i < data.navigationKeyRepeat; i++) {
                    inputPanel.emulateNavigationKeyClick(data.navigationKey)
                }
            } else if (data.hasOwnProperty("navigationKeySequence")) {
                for (var navigationKeyIndex in data.navigationKeySequence) {
                    inputPanel.emulateNavigationKeyClick(data.navigationKeySequence[navigationKeyIndex])
                }
            }

            verify(inputPanel.keyboardInputArea.initialKey === initialKeyObj)
        }

        function test_navigationCursorAndWordCandidateView() {
            prepareTest()

            if (!inputPanel.activateNavigationKeyMode())
                expectFail("", "Arrow key navigation not enabled")
            verify(inputPanel.naviationHighlight.visible)

            verify(inputPanel.navigationKeyClick("q"))
            verify(inputPanel.navigationKeyClick("q"))
            wait(200)
            var focusKey = inputPanel.keyboardInputArea.initialKey
            verify(focusKey !== null)

            if (inputPanel.wordCandidateView.count <= 1)
                expectFail("", "Prediction/spell correction not enabled")
            verify(inputPanel.wordCandidateView.count > 1)
            verify(inputPanel.keyboardInputArea.initialKey === focusKey)
            verify(inputPanel.wordCandidateView.currentIndex !== -1)

            // Move focus to word candidate list
            inputPanel.emulateNavigationKeyClick(Qt.Key_Up)
            verify(inputPanel.keyboardInputArea.initialKey === null)
            verify(inputPanel.wordCandidateView.currentIndex !== -1)

            // Move focus to the next item in the list
            var previousHighlightIndex = inputPanel.wordCandidateView.currentIndex
            inputPanel.emulateNavigationKeyClick(Qt.Key_Right)
            compare(inputPanel.wordCandidateView.currentIndex, previousHighlightIndex + 1)

            // Move focus to previously focused key on keyboard and back
            previousHighlightIndex = inputPanel.wordCandidateView.currentIndex
            inputPanel.emulateNavigationKeyClick(Qt.Key_Down)
            verify(inputPanel.keyboardInputArea.initialKey === focusKey)
            compare(inputPanel.wordCandidateView.currentIndex, previousHighlightIndex)
            inputPanel.emulateNavigationKeyClick(Qt.Key_Up)
            verify(inputPanel.keyboardInputArea.initialKey === null)
            compare(inputPanel.wordCandidateView.currentIndex, previousHighlightIndex)

            // Move focus to last item in the list
            for (previousHighlightIndex = inputPanel.wordCandidateView.currentIndex;
                 previousHighlightIndex < inputPanel.wordCandidateView.count - 1;
                 previousHighlightIndex++) {
                inputPanel.emulateNavigationKeyClick(Qt.Key_Right)
                compare(inputPanel.wordCandidateView.currentIndex, previousHighlightIndex + 1)
            }

            // Move focus to keyboard (from the end of the word candidate list)
            inputPanel.emulateNavigationKeyClick(Qt.Key_Right)
            verify(inputPanel.keyboardInputArea.initialKey === focusKey)
            compare(inputPanel.wordCandidateView.currentIndex, previousHighlightIndex)

            // Move focus back to last item in the list
            inputPanel.emulateNavigationKeyClick(Qt.Key_Left)
            verify(inputPanel.keyboardInputArea.initialKey === null)
            compare(inputPanel.wordCandidateView.currentIndex, previousHighlightIndex)

            // Move focus to first item in the list
            for (previousHighlightIndex = inputPanel.wordCandidateView.currentIndex;
                 previousHighlightIndex > 0;
                 previousHighlightIndex--) {
                inputPanel.emulateNavigationKeyClick(Qt.Key_Left)
                compare(inputPanel.wordCandidateView.currentIndex, previousHighlightIndex - 1)
            }

            // Move focus to bottom right corner of keyboard
            inputPanel.emulateNavigationKeyClick(Qt.Key_Left)
            verify(inputPanel.keyboardInputArea.initialKey !== null)
            verify(inputPanel.keyboardInputArea.initialKey !== focusKey)
            compare(inputPanel.wordCandidateView.currentIndex, previousHighlightIndex)

            // Move back to word candidate list by doing an opposite move
            inputPanel.emulateNavigationKeyClick(Qt.Key_Right)
            verify(inputPanel.keyboardInputArea.initialKey === null)
            compare(inputPanel.wordCandidateView.currentIndex, previousHighlightIndex)

            // Select item
            inputPanel.emulateNavigationKeyClick(Qt.Key_Return)
            verify(inputPanel.keyboardInputArea.initialKey !== null)
            verify(inputPanel.wordCandidateView.currentIndex === -1)
            verify(inputPanel.wordCandidateView.count === 0)
            verify(textInput.text.length > 0)
        }

        function test_spellCorrectionSuggestions_data() {
            return [
                { initInputMethodHints: Qt.ImhNoPredictiveText, inputSequence: "hwllo", outputText: "Hwllo" },
                { initInputMethodHints: Qt.ImhNone, inputSequence: "hwllo", expectedSuggestion: "Hello", outputText: "Hello" },
                { initText: "Hello", initInputMethodHints: Qt.ImhNone, inputSequence: "qorld", expectedSuggestion: "world", outputText: "Helloworld" },
                { initText: "isn'", initInputMethodHints: Qt.ImhNone, inputSequence: "t", outputText: "isn't" },
                { initInputMethodHints: Qt.ImhUrlCharactersOnly | Qt.ImhNoAutoUppercase, inputSequence: "www.example.com", expectedSuggestion: "www.example.com", outputText: "www.example.com" },
                { initInputMethodHints: Qt.ImhEmailCharactersOnly | Qt.ImhNoAutoUppercase, inputSequence: "user.name@example.com", expectedSuggestion: "user.name@example.com", outputText: "user.name@example.com" },
            ]
        }

        function test_spellCorrectionSuggestions(data) {
            prepareTest(data)

            for (var inputIndex in data.inputSequence) {
                verify(inputPanel.virtualKeyClick(data.inputSequence[inputIndex]))
            }
            waitForRendering(inputPanel)

            if (data.hasOwnProperty("expectedSuggestion")) {
                if (inputPanel.wordCandidateView.count > 0) {
                    verify(inputPanel.selectionListSearchSuggestion(data.expectedSuggestion, 2000), "The expected spell correction suggestion \"%1\" was not found".arg(data.expectedSuggestion))
                    verify(inputPanel.selectionListSelectCurrentItem(), "Word candidate not selected")
                } else if (textInput.text !== data.outputText) {
                    expectFail("", "Prediction/spell correction not enabled")
                }
            } else {
                wait(1000)
                verify(inputPanel.wordCandidateView.count <= 1, "Prediction/spell correction results are not expected")
                Qt.inputMethod.commit()
                waitForRendering(inputPanel)
            }

            compare(textInput.text, data.outputText)
        }

        function test_spellCorrectionAutomaticSpaceInsertion_data() {
            return [
                { inputSequence: ['h','e','l','l','o',Qt.Key_Select,'w','o','r','l','d'], outputText: "Hello world" },
                { inputSequence: ['h','e','l','l','o','\'','s',Qt.Key_Select,'w','o','r','l','d'], outputText: "Hello's world" },
                { inputSequence: ['h','e','l','l','o','s','\'',Qt.Key_Select,'w','o','r','l','d'], outputText: "Hellos' world" },
                { inputSequence: ['h','e','l','l','o','-','w','o','r','l','d'], outputText: "Hello-world" },
                { inputSequence: ['h','e','l','l','o',Qt.Key_Select,'.','w','o','r','l','d'], outputText: "Hello. World" },
                { inputSequence: ['h','e','l','l','o',Qt.Key_Select,',','w','o','r','l','d'], outputText: "Hello, world" },
                { inputSequence: ['h','e','l','l','o','.',Qt.Key_Backspace,'w','o','r','l','d'], outputText: "Helloworld" },
                { inputSequence: ['h','e','l','l','o',' ',Qt.Key_Backspace,'w','o','r','l','d'], outputText: "Helloworld" },
                { inputSequence: ['h','e','l','l','o',Qt.Key_Select,'w','o','r','l','d',':-)'], outputText: "Hello world :-)" },
                { inputSequence: ['h','e','l','l','o',Qt.Key_Select,'w','o','r','l','d',':-)',':-)'], outputText: "Hello world :-) :-)" },
                { inputSequence: ['h','e','l','l','o',Qt.Key_Select,':-)'], outputText: "Hello :-)" },
                { initText: "Hekko world", selectionStart: 2, selectionEnd: 4, inputSequence: ['l','l'], outputText: "Hello world" },
            ]
        }

        function test_spellCorrectionAutomaticSpaceInsertion(data) {
            prepareTest(data)

            for (var inputIndex in data.inputSequence) {
                var key = data.inputSequence[inputIndex]
                if (key === Qt.Key_Select) {
                    inputPanel.selectionListSelectCurrentItem()
                } else {
                    inputPanel.virtualKeyClick(key)
                }
            }

            Qt.inputMethod.commit()
            waitForRendering(inputPanel)
            compare(textInput.text, data.outputText)
        }

        function test_selectionListSelectInvalidItem() {
            prepareTest()

            // Note: This test passes if it does not crash
            if (inputPanel.wordCandidateView.model) {
                compare(inputPanel.wordCandidateView.count, 0)
                inputPanel.wordCandidateView.model.selectItem(-2)
                inputPanel.wordCandidateView.model.selectItem(-1)
                inputPanel.wordCandidateView.model.selectItem(0)
                inputPanel.wordCandidateView.model.selectItem(1)
                inputPanel.wordCandidateView.model.selectItem(2)
            }
        }

        function test_pinyinInputMethod_data() {
            return [
                { initInputMethodHints: Qt.ImhNone, initLocale: "zh_CN", inputSequence: "suoer", expectedCandidates: [ "\u7D22\u5C14" ], outputText: "\u7D22\u5C14" },
                // Build phase from individual candidates
                // Note: this phrase does not exist in the system dictionary
                { initInputMethodHints: Qt.ImhNone, initLocale: "zh_CN", inputSequence: "bailou", expectedCandidates: [ "\u5457", "\u5A04" ], outputText: "\u5457\u5A04" },
                // Select phrase from the user dictinary
                { initInputMethodHints: Qt.ImhNone, initLocale: "zh_CN", inputSequence: "bailou", expectedCandidates: [ "\u5457\u5A04" ], outputText: "\u5457\u5A04" },
                // Add an apostrophe before joined syllables in cases of ambiguity, disable the user dictionary (Qt.ImhSensitiveData) so it does not affect to the results
                { initInputMethodHints: Qt.ImhNone | Qt.ImhSensitiveData, initLocale: "zh_CN", inputSequence: "zhangang", expectedCandidates: [ "\u5360", "\u94A2" ], outputText: "\u5360\u94A2" },
                { initInputMethodHints: Qt.ImhNone | Qt.ImhSensitiveData, initLocale: "zh_CN", inputSequence: "zhang'ang", expectedCandidates: [ "\u7AE0", "\u6602" ], outputText: "\u7AE0\u6602" },
            ]
        }

        function test_pinyinInputMethod(data) {
            prepareTest(data)

            for (var inputIndex in data.inputSequence) {
                verify(inputPanel.virtualKeyClick(data.inputSequence[inputIndex]))
            }
            waitForRendering(inputPanel)

            for (var candidateIndex in data.expectedCandidates) {
                verify(inputPanel.selectionListSearchSuggestion(data.expectedCandidates[candidateIndex]))
                verify(inputPanel.selectionListSelectCurrentItem())
            }

            compare(textInput.text, data.outputText)
        }

        function test_hangulInputMethod_data() {
            return [
                // Test boundaries of the Hangul Jamo BMP plane
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F", outputText: "\uAC00" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3131", outputText: "\uAC01" },
                { initLocale: "ko_KR", inputSequence: "\u314E\u3163", outputText: "\uD788" },
                { initLocale: "ko_KR", inputSequence: "\u314E\u3163\u314E", outputText: "\uD7A3" },
                // Test double medial Jamos
                { initLocale: "ko_KR", inputSequence: "\u3131\u3157\u314F", outputText: "\uACFC" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u3157\u3150", outputText: "\uAD18" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u3157\u3163", outputText: "\uAD34" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u315C\u3153", outputText: "\uAD88" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u315C\u3154", outputText: "\uADA4" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u315C\u3163", outputText: "\uADC0" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u3161\u3163", outputText: "\uAE14" },
                // Test double final Jamos
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3131\u3145", outputText: "\uAC03" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3134\u3148", outputText: "\uAC05" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3134\u314E", outputText: "\uAC06" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3139\u3131", outputText: "\uAC09" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3139\u3141", outputText: "\uAC0A" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3139\u3142", outputText: "\uAC0B" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3139\u3145", outputText: "\uAC0C" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3139\u314C", outputText: "\uAC0D" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3139\u314D", outputText: "\uAC0E" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3139\u314E", outputText: "\uAC0F" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3142\u3145", outputText: "\uAC12" },
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3145\u3145", outputText: "\uAC14" },
                // Test using the final Jamo of the first syllable as an initial
                // Jamo of the following syllable
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3131\u314F", outputText: "\uAC00\uAC00" },
                // Test splitting the final double Jamo and use the second Jamo of
                // the split Jamo as initial Jamo of the following syllable
                { initLocale: "ko_KR", inputSequence: "\u3131\u314F\u3131\u3145\u314F", outputText: "\uAC01\uC0AC" },
                // Test entering a Jamo syllable with surrounding text
                { initLocale: "ko_KR", initText: "abcdef", initCursorPosition: 3, inputSequence: "\u3131\u314F\u3131", outputText: "abc\uAC01def" },
            ]
        }

        function test_hangulInputMethod(data) {
            prepareTest(data)

            compare(Qt.inputMethod.locale.name, Qt.locale(data.initLocale).name)

            // Add Jamos one by one
            var intermediateResult = []
            for (var inputIndex in data.inputSequence) {
                verify(inputPanel.virtualKeyClick(data.inputSequence[inputIndex]))
                intermediateResult.push(textInput.text)
            }

            compare(textInput.text, data.outputText)

            // Remove Jamos one by one.
            // The number of removed characters must match to the number of Jamos entered.
            for (; inputIndex >= 0; inputIndex--) {
                compare(textInput.text, intermediateResult.pop())
                inputPanel.virtualKeyClick(Qt.Key_Backspace)
            }

            waitForRendering(inputPanel)
            compare(textInput.text, data.initText !== undefined ? data.initText : "")
        }

        function test_japaneseInputModes_data() {
            return [
                // Hiragana
                { initLocale: "ja_JP", initInputMode: "Hiragana", inputSequence: ["n","i","h","o","n","g","o",Qt.Key_Return], outputText: "\u306B\u307B\u3093\u3054" },
                // Hiragana to Kanjie conversion
                { initLocale: "ja_JP", initInputMode: "Hiragana", inputSequence: ["n","i","h","o","n","g","o",Qt.Key_Space,Qt.Key_Return], outputText: "\u65E5\u672C\u8A9E" },
                // Correction to Hiragana sequence using exact match mode
                { initLocale: "ja_JP", initInputMode: "Hiragana", inputSequence: [
                                // Write part of the text leaving out "ni" from the beginning
                                "h","o","n","g","o",
                                // Activate the exact mode and move the cursor to beginning
                                Qt.Key_Left,Qt.Key_Left,Qt.Key_Left,Qt.Key_Left,
                                // Enter the missing text
                                "n","i",
                                // Move the cursor to end
                                Qt.Key_Right,Qt.Key_Right,Qt.Key_Right,Qt.Key_Right,Qt.Key_Right,
                                // Do Kanjie conversion
                                Qt.Key_Space,
                                // Choose the first candidate
                                Qt.Key_Return], outputText: "\u65E5\u672C\u8A9E" },
                // Katakana
                { initLocale: "ja_JP", initInputMode: "Katakana", inputSequence: ["a","m","e","r","i","k","a"], outputText: "\u30A2\u30E1\u30EA\u30AB" },
                // Toggle symbol mode without affecting the input method state
                { initLocale: "ja_JP", initInputMode: "Hiragana", inputSequence: ["n","i","h","o","n","g","o"], outputText: "" },
                // Latin only
                { initLocale: "ja_JP", initInputMethodHints: Qt.ImhLatinOnly, inputSequence: "hello", outputText: "Hello" },
            ]
        }

        function test_japaneseInputModes(data) {
            prepareTest(data)

            for (var inputIndex in data.inputSequence) {
                verify(inputPanel.virtualKeyClick(data.inputSequence[inputIndex]))
            }

            waitForRendering(inputPanel)
            compare(textInput.text, data.outputText)
        }

        function test_baseKeyNoModifier() {
            // The Japanese keyboard uses the BaseKey.noModifier flag for the arrow keys.
            // Without this flag the arrow key + shift would extend the text selection.
            prepareTest({ initLocale: "ja_JP", initInputMethodHints: Qt.ImhLatinOnly })
            verify(inputPanel.virtualKeyClick("a"))
            verify(inputPanel.virtualKeyClick(Qt.Key_Left))
            compare(textInput.cursorPosition, 0)
            verify(inputPanel.virtualKeyClick(Qt.Key_Right))
            compare(textInput.cursorPosition, 1)
            compare(textInput.selectedText, "")
        }
    }
}
