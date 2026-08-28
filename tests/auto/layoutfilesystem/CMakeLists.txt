# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_layoutfilesystem LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

# Generated from layoutfilesystem.pro.

#####################################################################
## tst_layoutfilesystem Test:
#####################################################################

qt_internal_add_test(tst_layoutfilesystem
    SOURCES
        ../shared/layouttesthelper.cpp ../shared/layouttesthelper.h
        tst_layoutfilesystem.cpp
    DEFINES
        SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    INCLUDE_DIRECTORIES
        ../shared
    LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::Quick
)

#### Keys ignored in scope 1:.:.:layoutfilesystem.pro:<TRUE>:
# OTHER_FILES = "data/layouts/en_GB/main.qml"

## Scopes:
#####################################################################

qt_internal_extend_target(tst_layoutfilesystem CONDITION NOT QT_BUILD_SHARED_LIBS
    LIBRARIES
        Qt::Svg
)

#### Keys ignored in scope 3:.:.:layoutfilesystem.pro:static:
# QTPLUGIN = "qtvirtualkeyboardplugin"
