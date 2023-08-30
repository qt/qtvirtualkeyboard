# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory(3rdparty/pinyin)

#####################################################################
## QtVirtualKeyboardPinyinPlugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtvkbpinyinplugin
    URI "QtQuick.VirtualKeyboard.Plugins.Pinyin"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbpinyinplugin
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick.VirtualKeyboard/auto
    SOURCES
        pinyindecoderservice.cpp pinyindecoderservice_p.h
        pinyininputmethod.cpp pinyininputmethod_p.h
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
        Qt::BundledPinyin
)

# Resources:
set(qmake_virtualkeyboard_pinyin_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/zh_CN/dialpad.fallback"
    "${VKB_LAYOUTS_BASE}/zh_CN/digits.fallback"
    "${VKB_LAYOUTS_BASE}/zh_CN/main.qml"
    "${VKB_LAYOUTS_BASE}/zh_CN/numbers.fallback"
    "${VKB_LAYOUTS_BASE}/zh_CN/symbols.qml"
)

qt_internal_add_resource(qtvkbpinyinplugin "qmake_virtualkeyboard_pinyin_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}" #special case
    BASE
        "${VKB_LAYOUTS_BASE}" #special case
    FILES
        ${qmake_virtualkeyboard_pinyin_layouts_resource_files}
)

if (NOT FEATURE_vkb_no_bundle_pinyin)
    # Resources:
    set(qmake_pinyin_resource_files
        "3rdparty/pinyin/data/dict_pinyin.dat"
    )

    qt_internal_add_resource(qtvkbpinyinplugin "qmake_pinyin"
        PREFIX
            "/qt-project.org/imports/QtQuick/VirtualKeyboard"
        BASE
            "${CMAKE_CURRENT_SOURCE_DIR}"
        FILES
            ${qmake_pinyin_resource_files}
    )
else()
    qt_copy_or_install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/pinyin/data/"
        DESTINATION "${VKB_INSTALL_DATA}/pinyin"
        FILES_MATCHING
        PATTERN "*.dat"
    )
endif()
