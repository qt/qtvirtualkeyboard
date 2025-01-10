# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QtVirtualKeyboardHangulPlugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtvkbhangulplugin
    URI "QtQuick.VirtualKeyboard.Plugins.Hangul"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbhangulplugin
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick.VirtualKeyboard/auto
    SOURCES
        hangul.cpp hangul_p.h
        hangulinputmethod.cpp hangulinputmethod_p.h
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
set(qmake_virtualkeyboard_hangul_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/ko_KR/dialpad.fallback"
    "${VKB_LAYOUTS_BASE}/ko_KR/digits.fallback"
    "${VKB_LAYOUTS_BASE}/ko_KR/main.qml"
    "${VKB_LAYOUTS_BASE}/ko_KR/numbers.fallback"
    "${VKB_LAYOUTS_BASE}/ko_KR/symbols.qml"
)

qt_internal_add_resource(qtvkbhangulplugin "qmake_virtualkeyboard_hangul_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${VKB_LAYOUTS_BASE}"
    FILES
        ${qmake_virtualkeyboard_hangul_layouts_resource_files}
)
