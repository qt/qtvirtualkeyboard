# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qtvirtualkeyboard.pro.

cmake_minimum_required(VERSION 3.16)

include(.cmake.conf)
project(QtVirtualKeyboard
    VERSION "${QT_REPO_MODULE_VERSION}"
    DESCRIPTION "Qt VirtualKeyboard Libraries"
    HOMEPAGE_URL "https://qt.io/"
    LANGUAGES CXX C
)

# Make sure we use the fixed BASE argument of qt_add_resource.
set(QT_USE_FIXED_QT_ADD_RESOURCE_BASE TRUE)

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Core) # special case
find_package(Qt6 ${PROJECT_VERSION} QUIET CONFIG
    OPTIONAL_COMPONENTS
        Qml
        QmlTools
        Quick
        Svg
        QuickTest
        QuickControls2
        Multimedia
)
qt_internal_project_setup()

if(NOT TARGET Qt::Quick)
    message(NOTICE "Skipping the build as the condition \"TARGET Qt::Quick\" is not met.")
    return()
endif()
if(NOT TARGET Qt::Svg)
    message(NOTICE "Skipping the build as the condition \"TARGET Qt::Svg\" is not met.")
    return()
endif()
if(WINRT)
    message(NOTICE "Skipping the build as the condition \"NOT WINRT\" is not met.")
    return()
endif()
qt_build_repo()
