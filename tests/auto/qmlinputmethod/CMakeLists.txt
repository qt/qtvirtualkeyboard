# Copyright (C) 2025 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_test(tst_qmlinputmethod
    SOURCES
        tst_qmlinputmethod.cpp
    LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::Quick
    TESTDATA
        "${CMAKE_CURRENT_LIST_DIR}/data/inputpanel.qml"
    BUILTIN_TESTDATA
)

qt_internal_add_resource(tst_qmlinputmethod "tst_qmlinputmethod_layouts"
    PREFIX
        /qt-project.org/imports/tests/QtQuick/VirtualKeyboard/Layouts
    BASE
        "${CMAKE_CURRENT_LIST_DIR}/data/layouts/"
    FILES
        "${CMAKE_CURRENT_LIST_DIR}/data/layouts/en_GB/main.qml"
        "${CMAKE_CURRENT_LIST_DIR}/data/layouts/en_GB/numbers.qml"
)
