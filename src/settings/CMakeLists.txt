# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## qtvkbsettingsplugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtvkbsettingsplugin
    URI "QtQuick.VirtualKeyboard.Settings"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2 1
    PLUGIN_TARGET qtvkbsettingsplugin
    NO_PLUGIN_OPTIONAL
    SOURCES
        qquickvirtualkeyboardsettings.cpp
        qquickvirtualkeyboardsettings_p.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
        QT_VIRTUALKEYBOARD_DEFAULT_LAYOUTS_DIR="qrc:${VKB_LAYOUTS_PREFIX}"
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::VirtualKeyboardPrivate
)

qt_internal_extend_target(qtvkbsettingsplugin CONDITION QT_FEATURE_vkb_no_builtin_style
    DEFINES
        QT_VIRTUALKEYBOARD_DEFAULT_STYLE=""
)

qt_internal_extend_target(qtvkbsettingsplugin CONDITION QT_FEATURE_vkb_retro_style AND NOT QT_FEATURE_vkb_no_builtin_style
    DEFINES
        QT_VIRTUALKEYBOARD_DEFAULT_STYLE="retro"
)

qt_internal_extend_target(qtvkbsettingsplugin CONDITION NOT QT_FEATURE_vkb_no_builtin_style AND NOT QT_FEATURE_vkb_retro_style
    DEFINES
        QT_VIRTUALKEYBOARD_DEFAULT_STYLE="default"
)

