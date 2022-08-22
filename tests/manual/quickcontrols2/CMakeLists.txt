# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from quickcontrols2.pro.

#####################################################################
## quickcontrols2 Binary:
#####################################################################

qt_internal_add_manual_test(quickcontrols2
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

qt_internal_add_resource(quickcontrols2 "main"
    PREFIX
        "/"
    FILES
        ${main_resource_files}
)


#### Keys ignored in scope 1:.:.:quickcontrols2.pro:<TRUE>:
# QML_IMPORT_PATH = <EMPTY>
