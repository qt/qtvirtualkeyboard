# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QVirtualKeyboardPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QVirtualKeyboardPlugin
    OUTPUT_NAME qtvirtualkeyboardplugin
    PLUGIN_TYPE platforminputcontexts
    DEFAULT_IF ANDROID
    SOURCES
        plugin.cpp plugin.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::VirtualKeyboardPrivate
)

# Desktop keyboard loads QML module implicitly, which should be considered
# by build system.
qt_internal_extend_target(QVirtualKeyboardPlugin CONDITION QT_FEATURE_vkb_desktop
    LIBRARIES
        Qt6::VirtualKeyboardQml
)

qt_internal_extend_target(QVirtualKeyboardPlugin CONDITION WIN32
    LIBRARIES
        imm32
)
