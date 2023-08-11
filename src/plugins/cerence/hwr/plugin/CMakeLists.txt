# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QtVirtualKeyboardCerenceHwrPlugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtvkbcerencehwrplugin
    URI "QtQuick.VirtualKeyboard.Plugins.Cerence.HWR"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbcerencehwrplugin
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick.VirtualKeyboard.Core/auto
    SOURCES
        cerence_hwr_p.h
        t9writeabstractdictionary_p.h
        t9writedictionary.cpp t9writedictionary_p.h
        t9writeinputmethod.cpp t9writeinputmethod_p.h
        t9writewordcandidate.cpp t9writewordcandidate_p.h
        t9writeworker.cpp t9writeworker_p.h
    DEFINES
        HAVE_CERENCE_HWR
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::BundledCerencecommon
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboardPrivate
    NO_GENERATE_CPP_EXPORTS
)

# Resources:
set(qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/fallback/handwriting.qml"
)

if (QT_FEATURE_vkb_lang_en_GB)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/en_GB/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_en_US)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/en_US/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ar_AR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ar_AR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_bg_BG)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/bg_BG/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_cs_CZ)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/cs_CZ/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_da_DK)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/da_DK/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_de_DE)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/de_DE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_el_GR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/el_GR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_es_ES)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/es_ES/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_es_MX)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/es_MX/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_et_EE)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/et_EE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fa_FA)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fa_FA/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_fi_FI)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fi_FI/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fr_FR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fr_FR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fr_CA)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fr_CA/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_he_IL)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/he_IL/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_hr_HR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/hr_HR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_hu_HU)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/hu_HU/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_id_ID)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/id_ID/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_it_IT)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/it_IT/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_lv_LV)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/lv_LV/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ms_MY)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ms_MY/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nb_NO)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/nb_NO/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nl_NL)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/nl_NL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pl_PL)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/pl_PL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pt_BR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/pt_BR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pt_PT)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/pt_PT/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ro_RO)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ro_RO/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ru_RU)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ru_RU/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_sk_SK)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sk_SK/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sl_SI)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sl_SI/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sq_AL)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sq_AL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sr_SP)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sr_SP/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_sv_SE)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sv_SE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_th_TH)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/th_TH/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_tr_TR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/tr_TR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_uk_UA)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/uk_UA/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_vi_VN)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/vi_VN/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ja_JP)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ja_JP/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_ko_KR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ko_KR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_zh_CN)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/zh_CN/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_zh_TW)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/zh_TW/handwriting.qml"
    )
endif()

qt_internal_add_resource(qtvkbcerencehwrplugin "qmake_virtualkeyboard_cerence_hwr_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${VKB_LAYOUTS_BASE}"
    FILES
        ${qmake_virtualkeyboard_cerence_hwr_layouts_resource_files}
)

set(qmake_virtualkeyboard_cerence_hwr_custom_layouts_resource_files)
if (QT_FEATURE_vkb_lang_zh_HK)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_custom_layouts_resource_files
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/handwriting.qml"
    )
endif()

qt_internal_add_resource(qtvkbcerencehwrplugin "qmake_virtualkeyboard_cerence_hwr_custom_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts"
    FILES
        ${qmake_virtualkeyboard_cerence_hwr_custom_layouts_resource_files}
)

qt_internal_extend_target(qtvkbcerencehwrplugin CONDITION QT_FEATURE_cerence_xt9
    DEFINES
        HAVE_XT9
    LIBRARIES
        Qt::BundledXt9Common
)

qt_internal_extend_target(qtvkbcerencehwrplugin CONDITION QT_FEATURE_cerence_hwr_alphabetic
    DEFINES
        HAVE_CERENCE_HWR_ALPHABETIC
    LIBRARIES
        Cerence::HWR::Alphabetic
)

qt_internal_extend_target(qtvkbcerencehwrplugin CONDITION QT_FEATURE_cerence_hwr_cjk
    DEFINES
        HAVE_CERENCE_HWR_CJK
    LIBRARIES
        Cerence::HWR::CJK
)

qt_internal_extend_target(qtvkbcerencehwrplugin CONDITION FEATURE_vkb_bundle_cerence OR FEATURE_vkb_bundle_cerence_hwr
    DEFINES
        HAVE_CERENCE_HWR_RESOURCE
)

if(FEATURE_vkb_bundle_cerence OR FEATURE_vkb_bundle_cerence_hwr)
    set(resource_glob_0)
    if(FEATURE_vkb_lang_ar_AR OR FEATURE_vkb_lang_fa_FA)
        file(GLOB resource_glob_0 RELATIVE "${CERENCE_HWR_DATAPATH}" "${CERENCE_HWR_DATAPATH}/arabic/*.bin")
        foreach(file IN LISTS resource_glob_0)
            set_source_files_properties("${CERENCE_HWR_DATAPATH}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
        endforeach()
    endif()

    set(resource_glob_1)
    if(FEATURE_vkb_lang_he_IL)
        file(GLOB resource_glob_1 RELATIVE "${CERENCE_HWR_DATAPATH}" "${CERENCE_HWR_DATAPATH}/hebrew/*.bin")
        foreach(file IN LISTS resource_glob_1)
            set_source_files_properties("${CERENCE_HWR_DATAPATH}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
        endforeach()
    endif()

    set(resource_glob_2)
    if(FEATURE_vkb_lang_th_TH)
        file(GLOB resource_glob_2 RELATIVE "${CERENCE_HWR_DATAPATH}" "${CERENCE_HWR_DATAPATH}/thai/*.bin")
        foreach(file IN LISTS resource_glob_2)
            set_source_files_properties("${CERENCE_HWR_DATAPATH}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
        endforeach()
    endif()

    file(GLOB resource_glob_3 RELATIVE "${CERENCE_HWR_DATAPATH}" "${CERENCE_HWR_DATAPATH}/*.bin")
    foreach(file IN LISTS resource_glob_3)
        set_source_files_properties("${CERENCE_HWR_DATAPATH}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
    endforeach()

    file(GLOB resource_glob_4 RELATIVE "${CERENCE_HWR_DATAPATH}" "${CERENCE_HWR_DATAPATH}/*.hdb")
    foreach(file IN LISTS resource_glob_4)
        set_source_files_properties("${CERENCE_HWR_DATAPATH}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
    endforeach()

    file(GLOB resource_glob_5 RELATIVE "${CERENCE_HWR_DATAPATH}" "${CERENCE_HWR_DATAPATH}/*.phd")
    foreach(file IN LISTS resource_glob_5)
        set_source_files_properties("${CERENCE_HWR_DATAPATH}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
    endforeach()

    # Resources:
    set(qmake_cerencehwrdata_db_resource_files
        ${resource_glob_0}
        ${resource_glob_1}
        ${resource_glob_2}
        ${resource_glob_3}
        ${resource_glob_4}
        ${resource_glob_5}
    )

    qt_internal_add_resource(qtvkbcerencehwrplugin "qmake_cerencehwrdata_db"
        PREFIX
            "/qt-project.org/imports/QtQuick/VirtualKeyboard/Cerence/Handwriting"
        BASE
            "${CERENCE_HWR_DATAPATH}"
        FILES
            ${qmake_cerencehwrdata_db_resource_files}
        OPTIONS
            -no-compress
    )
else()
    qt_copy_or_install(
        DIRECTORY "${CERENCE_HWR_DATAPATH}/"
        DESTINATION "${VKB_INSTALL_DATA}/cerence/handwriting"
    )
endif()

if(QT_FEATURE_cerence_hwr_alphabetic AND NOT FEATURE_vkb_cerence_static)
    qt_copy_or_install(
        FILES "${CERENCE_HWR_ALPHABETIC_BINARIES}"
        DESTINATION "${QT_BUILD_DIR}/${INSTALL_BINDIR}"
    )
endif()

if(QT_FEATURE_cerence_hwr_cjk AND NOT FEATURE_vkb_cerence_static)
    qt_copy_or_install(
        FILES "${CERENCE_HWR_CJK_BINARIES}"
        DESTINATION "${QT_BUILD_DIR}/${INSTALL_BINDIR}"
    )
endif()
