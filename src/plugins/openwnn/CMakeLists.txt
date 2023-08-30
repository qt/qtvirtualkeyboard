# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory(3rdparty/openwnn)

#####################################################################
## QtVirtualKeyboardOpenWnnPlugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtvkbopenwnnplugin
    URI "QtQuick.VirtualKeyboard.Plugins.OpenWNN"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbopenwnnplugin
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick.VirtualKeyboard/auto
    SOURCES
        openwnninputmethod.cpp openwnninputmethod_p.h
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
        Qt::BundledOpenwnn
)

# Resources:
set(qmake_virtualkeyboard_openwnn_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/ja_JP/dialpad.fallback"
    "${VKB_LAYOUTS_BASE}/ja_JP/digits.fallback"
    "${VKB_LAYOUTS_BASE}/ja_JP/main.qml"
    "${VKB_LAYOUTS_BASE}/ja_JP/numbers.fallback"
    "${VKB_LAYOUTS_BASE}/ja_JP/symbols.qml"
)

qt_internal_add_resource(qtvkbopenwnnplugin "qmake_virtualkeyboard_openwnn_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${VKB_LAYOUTS_BASE}"
    FILES
        ${qmake_virtualkeyboard_openwnn_layouts_resource_files}
)
