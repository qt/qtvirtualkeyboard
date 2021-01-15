/****************************************************************************
**
** Copyright (C) 2016 Jeremy Katz
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
****************************************************************************/

import QtTest 1.0
import QtQuick 2.0
import QtQuick.VirtualKeyboard.Settings 2.0

Item {

    TestCase {
        id: testcase
        name: "tst_styles"

        function test_style_data() {
            return [
                { tag: "default", result: "default"},
                { tag: "retro", result: "retro"}, // in-source alternate style
                { tag: "test", result: "test"} // out-of-source alternate style
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
