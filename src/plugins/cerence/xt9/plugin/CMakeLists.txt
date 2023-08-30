# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QtVirtualKeyboardXt9Plugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtvkbcerencext9plugin
    URI "QtQuick.VirtualKeyboard.Plugins.Cerence.XT9"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbcerencext9plugin
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick.VirtualKeyboard/auto
    SOURCES
        xt9awinputmethod.cpp xt9awinputmethod_p.h
        xt9awinputmethodprivate.cpp xt9awinputmethodprivate_p.h
        xt9cpinputmethod.cpp xt9cpinputmethod_p.h
        xt9cpinputmethodprivate.cpp xt9cpinputmethodprivate_p.h
        xt9inputmethod.cpp xt9inputmethod_p.h
        xt9inputmethodprivate.cpp xt9inputmethodprivate_p.h
        xt9jinputmethod.cpp xt9jinputmethod_p.h
        xt9jinputmethodprivate.cpp xt9jinputmethodprivate_p.h
        xt9kinputmethod.cpp xt9kinputmethod_p.h
        xt9kinputmethodprivate.cpp xt9kinputmethodprivate_p.h
        xt9thaiinputmethod.cpp xt9thaiinputmethod_p.h
        xt9thaiinputmethodprivate.cpp xt9thaiinputmethodprivate_p.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::BundledCerencecommon
        Qt::BundledXt9Common
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboardPrivate
)

set(qmake_virtualkeyboard_xt9_layouts_resource_files)
if (QT_FEATURE_vkb_lang_ja_JP)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ja_JP/digits.fallback"
        "${VKB_LAYOUTS_BASE}/ja_JP/numbers.fallback"
        "${VKB_LAYOUTS_BASE}/ja_JP/symbols.qml"
        "${VKB_LAYOUTS_BASE}/ja_JP/dialpad.fallback"
    )
endif()
if (QT_FEATURE_vkb_lang_ko_KR)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ko_KR/digits.fallback"
        "${VKB_LAYOUTS_BASE}/ko_KR/main.qml"
        "${VKB_LAYOUTS_BASE}/ko_KR/numbers.fallback"
        "${VKB_LAYOUTS_BASE}/ko_KR/symbols.qml"
        "${VKB_LAYOUTS_BASE}/ko_KR/dialpad.fallback"
    )
endif()
if (QT_FEATURE_vkb_lang_th_TH)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/th_TH/digits.fallback"
        "${VKB_LAYOUTS_BASE}/th_TH/main.qml"
        "${VKB_LAYOUTS_BASE}/th_TH/numbers.fallback"
        "${VKB_LAYOUTS_BASE}/th_TH/symbols.qml"
        "${VKB_LAYOUTS_BASE}/th_TH/dialpad.fallback"
    )
endif()
if (QT_FEATURE_vkb_lang_zh_CN)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/zh_CN/digits.fallback"
        "${VKB_LAYOUTS_BASE}/zh_CN/numbers.fallback"
        "${VKB_LAYOUTS_BASE}/zh_CN/symbols.qml"
        "${VKB_LAYOUTS_BASE}/zh_CN/dialpad.fallback"
    )
endif()
if (NOT FEATURE_vkb_cerence_xt9_9key_layouts AND QT_FEATURE_vkb_lang_zh_CN)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/zh_CN/main.qml"
    )
endif()
if (QT_FEATURE_vkb_lang_zh_TW)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/zh_TW/digits.fallback"
        "${VKB_LAYOUTS_BASE}/zh_TW/numbers.fallback"
        "${VKB_LAYOUTS_BASE}/zh_TW/symbols.qml"
        "${VKB_LAYOUTS_BASE}/zh_TW/dialpad.fallback"
    )
endif()

qt_internal_add_resource(qtvkbcerencext9plugin "qmake_virtualkeyboard_xt9_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${VKB_LAYOUTS_BASE}"
    FILES
        ${qmake_virtualkeyboard_xt9_layouts_resource_files}
)


set(qmake_virtualkeyboard_xt9_custom_layouts_resource_files)
if (QT_FEATURE_vkb_lang_ja_JP AND NOT FEATURE_vkb_cerence_xt9_9key_layouts)
    list(APPEND qmake_virtualkeyboard_xt9_custom_layouts_resource_files
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/ja_JP/main.qml"
    )
endif()
if (QT_FEATURE_vkb_lang_zh_HK)
    list(APPEND qmake_virtualkeyboard_xt9_custom_layouts_resource_files
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/digits.fallback"
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/numbers.fallback"
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/symbols.qml"
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/main.qml"
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/dialpad.fallback"
    )
endif()

qt_internal_add_resource(qtvkbcerencext9plugin "qmake_virtualkeyboard_xt9_custom_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts"
    FILES
        ${qmake_virtualkeyboard_xt9_custom_layouts_resource_files}
)

if (QT_FEATURE_vkb_lang_zh_TW AND NOT FEATURE_vkb_cerence_xt9_9key_layouts)
    # Resources:
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/main.qml ${CMAKE_CURRENT_BINARY_DIR}/content/layouts/zh_TW/main.qml COPYONLY)
    set(qmake_virtualkeyboard_xt9_cangjie_layouts_resource_files
        "${CMAKE_CURRENT_BINARY_DIR}/content/layouts/zh_TW/main.qml"
    )

    qt_internal_add_resource(qtvkbcerencext9plugin "qmake_virtualkeyboard_xt9_cangjie_layouts"
        PREFIX
            "${VKB_LAYOUTS_PREFIX}"
        BASE
            "${CMAKE_CURRENT_BINARY_DIR}/content/layouts"
        FILES
            ${qmake_virtualkeyboard_xt9_cangjie_layouts_resource_files}
    )
endif()

if (FEATURE_vkb_cerence_xt9_9key_layouts)
    if (QT_FEATURE_vkb_lang_zh_CN)
        list(APPEND qmake_virtualkeyboard_xt9_9key_layouts_resource_files
            "${CMAKE_CURRENT_SOURCE_DIR}/9key_layouts/content/layouts/zh_CN/main.qml"
        )
    endif()

    if (QT_FEATURE_vkb_lang_zh_TW)
        list(APPEND qmake_virtualkeyboard_xt9_9key_layouts_resource_files
            "${CMAKE_CURRENT_SOURCE_DIR}/9key_layouts/content/layouts/zh_TW/main.qml"
        )
    endif()

    if (QT_FEATURE_vkb_lang_ja_JP)
        list(APPEND qmake_virtualkeyboard_xt9_9key_layouts_resource_files
            "${CMAKE_CURRENT_SOURCE_DIR}/9key_layouts/content/layouts/ja_JP/main.qml"
        )
    endif()

    qt_internal_add_resource(qtvkbcerencext9plugin "qmake_virtualkeyboard_xt9_9key_layouts"
        PREFIX
            "${VKB_LAYOUTS_PREFIX}"
        BASE
            "${CMAKE_CURRENT_SOURCE_DIR}/9key_layouts/content/layouts"
        FILES
            ${qmake_virtualkeyboard_xt9_9key_layouts_resource_files}
    )
endif()
