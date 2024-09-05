# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory(3rdparty/tcime)

#####################################################################
## QtVirtualKeyboardTCImePlugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtvkbtcimeplugin
    URI "QtQuick.VirtualKeyboard.Plugins.TCIme"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbtcimeplugin
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick.VirtualKeyboard.Core/auto
    SOURCES
        tcinputmethod.cpp tcinputmethod_p.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboardPrivate
        Qt::BundledTcime
    NO_GENERATE_CPP_EXPORTS
)

set(qmake_virtualkeyboard_tcime_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/zh_TW/dialpad.fallback"
    "${VKB_LAYOUTS_BASE}/zh_TW/digits.fallback"
    "${VKB_LAYOUTS_BASE}/zh_TW/main.qml"
    "${VKB_LAYOUTS_BASE}/zh_TW/numbers.fallback"
    "${VKB_LAYOUTS_BASE}/zh_TW/symbols.qml"
)

qt_internal_add_resource(qtvkbtcimeplugin "qmake_virtualkeyboard_tcime_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${VKB_LAYOUTS_BASE}"
    FILES
        ${qmake_virtualkeyboard_tcime_layouts_resource_files}
)

if (NOT FEATURE_vkb_no_bundle_tcime)
    # Resources:
    set(qmake_tcime_resource_files
        "3rdparty/tcime/data/qt/dict_cangjie.dat"
        "3rdparty/tcime/data/qt/dict_phrases.dat"
        "3rdparty/tcime/data/qt/dict_zhuyin.dat"
    )

    qt_internal_add_resource(qtvkbtcimeplugin "qmake_tcime"
        PREFIX
            "/qt-project.org/imports/QtQuick/VirtualKeyboard"
        BASE
            "${CMAKE_CURRENT_SOURCE_DIR}"
        FILES
            ${qmake_tcime_resource_files}
    )
else()
    qt_copy_or_install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/tcime/data/qt/"
        DESTINATION "${VKB_INSTALL_DATA}/tcime"
        FILES_MATCHING
        PATTERN "*.dat"
    )
endif()
