/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.VirtualKeyboard 2.3

/*!
    \qmltype InputModeKey
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \inherits Key
    \since QtQuick.VirtualKeyboard 2.3

    \brief Input mode key for keyboard layouts.

    This key toggles between available \l {InputEngine::inputModes} {InputEngine.inputModes}.
*/

Key {
    key: Qt.Key_Mode_switch
    noKeyEvent: true
    functionKey: true
    text: InputContext.inputEngine.inputMode < inputModeNameList.length ?
              inputModeNameList[InputContext.inputEngine.inputMode] : "ABC"
    onClicked: InputContext.inputEngine.inputMode = __nextInputMode(InputContext.inputEngine.inputMode)
    keyPanelDelegate: keyboard.style ? keyboard.style.symbolKeyPanel : undefined
    enabled: inputModeCount > 1

    /*!
        List of input mode names.

        The default list contains all known input modes for \l {InputEngine::inputMode} {InputEngine.inputMode}.
    */
    property var inputModeNameList: [
        "ABC",  // InputEngine.Latin
        "123",  // InputEngine.Numeric
        "123",  // InputEngine.Dialable
        "拼音",  // InputEngine.Pinyin
        "倉頡",  // InputEngine.Cangjie
        "注音",  // InputEngine.Zhuyin
        "한글",  // InputEngine.Hangul
        "あ",    // InputEngine.Hiragana
        "カ",    // InputEngine.Katakana
        "全角",  // InputEngine.FullwidthLatin
        "ΑΒΓ",  // InputEngine.Greek
        "АБВ",  // InputEngine.Cyrillic
        "\u0623\u200C\u0628\u200C\u062C",  // InputEngine.Arabic
        "\u05D0\u05D1\u05D2",  // InputEngine.Hebrew
        "中文",  // InputEngine.ChineseHandwriting
        "日本語", // InputEngine.JapaneseHandwriting
        "한국어", // InputEngine.KoreanHandwriting
    ]

    /*!
        List of input modes to toggle.

        This property allows to define a custom list of input modes to
        toggle.

        The default list contains all the available input modes.
    */
    property var inputModes: InputContext.inputEngine.inputModes

    /*!
        This read-only property reflects the actual number of input modes
        the user can cycle through this key.
    */
    readonly property int inputModeCount: __inputModes !== undefined ? __inputModes.length : 0

    property var __inputModes: __filterInputModes([].concat(InputContext.inputEngine.inputModes), inputModes)

    onInputModesChanged: {
        // Check that the current input mode is included in our list
        if (keyboard.active && InputContext.inputEngine.inputMode !== -1 &&
                __inputModes !== undefined && __inputModes.length > 0 &&
                __inputModes.indexOf(InputContext.inputEngine.inputMode) === -1)
            InputContext.inputEngine.inputMode = __inputModes[0]
    }

    function __nextInputMode(inputMode) {
        if (!enabled)
            return inputMode
        var inputModeIndex = __inputModes.indexOf(inputMode) + 1
        if (inputModeIndex >= __inputModes.length)
            inputModeIndex = 0
        return __inputModes[inputModeIndex]
    }

    function __filterInputModes(inputModes, filter) {
        for (var i = 0; i < inputModes.length; i++) {
            if (filter.indexOf(inputModes[i]) === -1)
                inputModes.splice(i, 1)
        }
        return inputModes
    }
}
