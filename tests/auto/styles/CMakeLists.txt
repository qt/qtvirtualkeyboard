# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from styles.pro.

#####################################################################
## tst_styles Test:
#####################################################################

# Collect test data
file(GLOB_RECURSE test_data_glob
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/data/*)
list(APPEND test_data ${test_data_glob})

qt_internal_add_test(tst_styles
    QMLTEST
    SOURCES
        tst_styles.cpp
    DEFINES
        TESTDATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data"
    LIBRARIES
        Qt::Gui
    TESTDATA ${test_data}
)

qt_internal_add_resource(tst_styles "test_res"
    PREFIX
        "/qt/qml/QtQuick/VirtualKeyboard/Styles/test_res"
    BASE
        "data/QtQuick/VirtualKeyboard/Styles/test"
    FILES
        "data/QtQuick/VirtualKeyboard/Styles/test/style.qml"
)

qt_internal_add_resource(tst_styles "test_res_compat"
    PREFIX
        "/QtQuick/VirtualKeyboard/content/styles/test_res_compat"
    BASE
        "data/QtQuick/VirtualKeyboard/Styles/test"
    FILES
        "data/QtQuick/VirtualKeyboard/Styles/test/style.qml"
)

#### Keys ignored in scope 1:.:.:styles.pro:<TRUE>:
# DISTFILES = "data/tst_styles.qml" "data/QtQuick/VirtualKeyboard/Styles/test/style.qml"
# OTHER_FILES = "$$PWD/data/tst_styles.qml"
# TEMPLATE = "app"

## Scopes:
#####################################################################

qt_internal_extend_target(tst_styles CONDITION NOT QT_BUILD_SHARED_LIBS
    LIBRARIES
        Qt::Svg
)

#### Keys ignored in scope 2:.:.:styles.pro:static:
# QTPLUGIN = "qtvirtualkeyboardplugin"
