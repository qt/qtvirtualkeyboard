# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QtVirtualKeyboardThaiPlugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtvkbthaiplugin
    URI "QtQuick.VirtualKeyboard.Plugins.Thai"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbthaiplugin
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick.VirtualKeyboard/auto
    SOURCES
        thaiinputmethod.cpp thaiinputmethod_p.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboard
)

# Resources:
set(qmake_virtualkeyboard_thai_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/th_TH/dialpad.fallback"
    "${VKB_LAYOUTS_BASE}/th_TH/digits.fallback"
    "${VKB_LAYOUTS_BASE}/th_TH/main.qml"
    "${VKB_LAYOUTS_BASE}/th_TH/numbers.fallback"
    "${VKB_LAYOUTS_BASE}/th_TH/symbols.qml"
)

qt_internal_add_resource(qtvkbthaiplugin "qmake_virtualkeyboard_thai_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${VKB_LAYOUTS_BASE}"
    FILES
        ${qmake_virtualkeyboard_thai_layouts_resource_files}
)

qt_internal_extend_target(qtvkbthaiplugin CONDITION QT_FEATURE_hunspell
    LIBRARIES
        Qt::HunspellInputMethodPrivate
)
