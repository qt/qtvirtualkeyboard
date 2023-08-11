# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_qml_module(qtvkbexamplehwrplugin
    URI "QtQuick.VirtualKeyboard.Plugins.Example.HWR"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbexamplehwrplugin
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick.VirtualKeyboard.Core/auto
    SOURCES
        examplehwrinputmethod.cpp examplehwrinputmethod_p.h
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
    NO_GENERATE_CPP_EXPORTS
)

set(qt_virtualkeyboard_example_hwr_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/fallback/handwriting.qml"
)

if (QT_FEATURE_vkb_lang_en_GB)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/en_GB/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_en_US)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/en_US/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ar_AR)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ar_AR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_bg_BG)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/bg_BG/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_cs_CZ)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/cs_CZ/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_da_DK)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/da_DK/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_de_DE)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/de_DE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_el_GR)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/el_GR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_es_ES)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/es_ES/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_es_MX)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/es_MX/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_et_EE)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/et_EE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fa_FA)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fa_FA/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_fi_FI)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fi_FI/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fr_FR)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fr_FR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fr_CA)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fr_CA/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_he_IL)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/he_IL/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_hr_HR)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/hr_HR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_hu_HU)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/hu_HU/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_id_ID)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/id_ID/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_it_IT)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/it_IT/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_lv_LV)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/lv_LV/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ms_MY)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ms_MY/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nb_NO)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/nb_NO/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nl_NL)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/nl_NL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pl_PL)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/pl_PL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pt_BR)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/pt_BR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pt_PT)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/pt_PT/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ro_RO)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ro_RO/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ru_RU)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ru_RU/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_sk_SK)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sk_SK/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sl_SI)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sl_SI/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sq_AL)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sq_AL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sr_SP)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sr_SP/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_sv_SE)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sv_SE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_th_TH)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/th_TH/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_tr_TR)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/tr_TR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_uk_UA)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/uk_UA/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_vi_VN)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/vi_VN/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ja_JP)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ja_JP/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_ko_KR)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ko_KR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_zh_CN)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/zh_CN/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_zh_TW)
    list(APPEND qt_virtualkeyboard_example_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/zh_TW/handwriting.qml"
    )
endif()

qt_internal_add_resource(qtvkbexamplehwrplugin "qt_virtualkeyboard_example_hwr_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${VKB_LAYOUTS_BASE}"
    FILES
        ${qt_virtualkeyboard_example_hwr_layouts_resource_files}
)
