# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Collect test data
file(GLOB_RECURSE test_data_glob
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/data/*)
list(APPEND test_data ${test_data_glob})

qt_internal_add_test(tst_virtualkeyboardattached
    QMLTEST
    SOURCES
        tst_virtualkeyboardattached.cpp
    LIBRARIES
        Qt::Gui
    TESTDATA ${test_data}
)
