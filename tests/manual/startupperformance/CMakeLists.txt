# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_manual_test(startupperformance
    GUI
    SOURCES
        main.cpp
    LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::Quick
)

# Resources:
set(main_resource_files
    "main.qml"
)

qt_internal_add_resource(startupperformance "main"
    PREFIX
        "/"
    FILES
        ${main_resource_files}
)
