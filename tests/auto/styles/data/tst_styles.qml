// Copyright (C) 2016 Jeremy Katz
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtTest
import QtQuick
import QtQuick.VirtualKeyboard.Settings
import QtQuick.VirtualKeyboard.Styles

Item {

    TestCase {
        id: testcase
        name: "tst_styles"

        function test_style_data() {
            return [
                { tag: "default", result: "default"},
                { tag: "retro", result: "retro"}, // in-source alternate style
                { tag: "test", result: "test"}, // out-of-source alternate style
                { tag: "test_res", result: "test_res"}, // default resource path
                { tag: "test_res_compat", result: "test_res_compat"}, // compatibility resource path
            ];
        }

        function test_style(data) {
            VirtualKeyboardSettings.styleName = data.tag;
            compare(VirtualKeyboardSettings.styleName, data.result,
                    "Failed setting VirtualKeyboardSettings.styleName to " + data.result);
        }

        function test_unknownStyle() {
            var previous = VirtualKeyboardSettings.styleName;
            VirtualKeyboardSettings.styleName = "bogus";
            compare(VirtualKeyboardSettings.styleName, previous,
                    "Unknown style names should be ignored");
        }
    }
}
