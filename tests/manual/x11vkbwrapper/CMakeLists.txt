# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from x11vkbwrapper.pro.

#####################################################################
## x11vkbwrapper Binary:
#####################################################################

find_package(Qt6 ${PROJECT_VERSION} QUIET CONFIG OPTIONAL_COMPONENTS Widgets)
if(NOT TARGET Qt::Widgets)
    message("Manual test x11vkbwrapper won't be built, because Qt::Widgets was not found.")
    return()
endif()

find_package(ATSPI2)
if(NOT TARGET PkgConfig::ATSPI2)
    message("Manual test x11vkbwrapper won't be built, because ATSPI2 was not found.")
    return()
endif()

qt_internal_add_manual_test(x11vkbwrapper
    GUI
    SOURCES
        common_defs.h
        handleatspievents.cpp handleatspievents.h
        handledbusforchrome.cpp handledbusforchrome.h
        handlekeyevents.cpp handlekeyevents.h
        handlelanguagechange.cpp handlelanguagechange.h
        keysymmapsforfakeinput.h
        main.cpp
        vkbhidetimer.cpp vkbhidetimer.h
        xcbkeyboard.h
    DEFINES
        QT_DEPRECATED_WARNINGS
    LIBRARIES
        PkgConfig::ATSPI2
        Qt::DBus
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::Svg
        Qt::VirtualKeyboard
        Qt::Widgets
        X11::X11
        Xtst
        xdo
)

# Resources:
set(qml_resource_files
    "Keyboard.qml"
    "graphics/Qt_logo.png"
    "main.qml"
)

qt_internal_add_resource(x11vkbwrapper "qml"
    PREFIX
        "/"
    FILES
        ${qml_resource_files}
)


#### Keys ignored in scope 1:.:.:x11vkbwrapper.pro:<TRUE>:
# TEMPLATE = "app"

## Scopes:
#####################################################################

qt_internal_extend_target(x11vkbwrapper CONDITION NOT QT_BUILD_SHARED_LIBS
    LIBRARIES
        Qt::Svg
)

#### Keys ignored in scope 2:.:.:x11vkbwrapper.pro:static:
# QTPLUGIN = "qtvirtualkeyboardplugin"

qt_internal_extend_target(x11vkbwrapper CONDITION CMAKE_BUILD_TYPE STREQUAL Release
    DEFINES
        QT_NO_DEBUG_OUTPUT
)
