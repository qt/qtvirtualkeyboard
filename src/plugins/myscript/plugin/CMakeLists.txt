# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QtVirtualKeyboardMyScriptPlugin Plugin:
#####################################################################

set(MYSCRIPT_INSTALL_DATA "${VKB_INSTALL_DATA}/myscript")

if(WIN32)
    set(MYSCRIPT_VOIM_NAME "voim.dll")
    set(MYSCRIPT_ENGINE_NAME "MyScriptEngine.dll")
    set(MYSCRIPT_INSTALL_BINDIR "${QT_BUILD_DIR}/${INSTALL_BINDIR}")
else() # only for Linux here, (UNIX OR LINUX) AND NOT ANDROID AND NOT APPLE
    set(MYSCRIPT_VOIM_NAME "libvoim.so")
    set(MYSCRIPT_ENGINE_NAME "libMyScriptEngine.so")
    set(MYSCRIPT_INSTALL_BINDIR "${QT_BUILD_DIR}/${INSTALL_LIBDIR}")
endif()
set(MYSCRIPT_VOIM_PROPERTY_NAME "voim/conf")
set(MYSCRIPT_LANGUAGE_CONF_NAME "conf")
set(MYSCRIPT_LANGUAGE_RESOURCES_NAME "resources")

qt_internal_add_qml_module(qtvkbmyscriptplugin
    URI "QtQuick.VirtualKeyboard.Plugins.MyScript"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbmyscriptplugin
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick.VirtualKeyboard.Core/auto
    SOURCES
        ${MyScript_ROOT_DIR}/voim/api/c/examples/common/Properties.c
        myscriptinputmethod.cpp myscriptinputmethod_p.h
        myscriptinputmethod_p_p.h
    DEFINES
        MYSCRIPT_CERTIFICATE="${MyScript_ROOT_DIR}/edk/c/examples/certificates/MyCertificate.c"
        MYSCRIPT_VOIM_PROPERTY_PATH="${MYSCRIPT_INSTALL_DATA}/${MYSCRIPT_VOIM_PROPERTY_NAME}"
        MYSCRIPT_LANGUAGE_CONF_PATH="${MYSCRIPT_INSTALL_DATA}/${MYSCRIPT_LANGUAGE_CONF_NAME}"
        MYSCRIPT_VOIM_NAME="${MYSCRIPT_VOIM_NAME}"
        MYSCRIPT_ENGINE_NAME="${MYSCRIPT_ENGINE_NAME}"
        # POSIX source must be required to use "strdup" for "Properties.c"
        _POSIX_C_SOURCE=200809L
    INCLUDE_DIRECTORIES
        ${MyScript_ROOT_DIR}/voim/api/c/examples
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboard
        MyScript::VOIM
    NO_GENERATE_CPP_EXPORTS
)

# MyScript Engine Binaries
qt_copy_or_install(
    FILES "${MyScript_BINARIES}"
    DESTINATION "${MYSCRIPT_INSTALL_BINDIR}"
)

# MyScript VoIM Properties
qt_copy_or_install(
    DIRECTORY "${MyScript_ROOT_DIR}/${MYSCRIPT_VOIM_PROPERTY_NAME}"
    DESTINATION "${MYSCRIPT_INSTALL_DATA}/voim"
)

# MyScript Language Conf
qt_copy_or_install(
    DIRECTORY "${MyScript_ROOT_DIR}/${MYSCRIPT_LANGUAGE_CONF_NAME}"
    DESTINATION "${MYSCRIPT_INSTALL_DATA}"
)

# MyScript Language Resources
qt_copy_or_install(
    DIRECTORY "${MyScript_ROOT_DIR}/${MYSCRIPT_LANGUAGE_RESOURCES_NAME}"
    DESTINATION "${MYSCRIPT_INSTALL_DATA}"
)

# Resources:
set(qmake_virtualkeyboard_myscript_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/fallback/handwriting.qml"
)

# special case begin
if (QT_FEATURE_vkb_lang_en_GB)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/en_GB/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_en_US)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/en_US/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ar_AR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ar_AR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_bg_BG)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/bg_BG/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_cs_CZ)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/cs_CZ/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_da_DK)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/da_DK/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_de_DE)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/de_DE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_el_GR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/el_GR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_es_ES)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/es_ES/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_es_MX)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/es_MX/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_et_EE)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/et_EE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fa_FA)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fa_FA/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_fi_FI)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fi_FI/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fr_CA)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fr_CA/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fr_FR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/fr_FR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_he_IL)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/he_IL/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_hi_IN)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/hi_IN/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_hr_HR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/hr_HR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_hu_HU)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/hu_HU/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_id_ID)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/id_ID/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_it_IT)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/it_IT/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_lv_LV)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/lv_LV/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ja_JP)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ja_JP/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_ko_KR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ko_KR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_ms_MY)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ms_MY/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nb_NO)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/nb_NO/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nl_NL)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/nl_NL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pl_PL)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/pl_PL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pt_BR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/pt_BR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pt_PT)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/pt_PT/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ro_RO)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ro_RO/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ru_RU)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/ru_RU/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_sk_SK)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sk_SK/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sl_SI)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sl_SI/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sq_AL)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sq_AL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sr_SP)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sr_SP/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_sv_SE)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/sv_SE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_th_TH)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/th_TH/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_tr_TR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/tr_TR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_uk_UA)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/uk_UA/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_vi_VN)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/vi_VN/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_zh_CN)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/zh_CN/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_zh_TW)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/zh_TW/handwriting.qml"
    )
endif()

qt_internal_add_resource(qtvkbmyscriptplugin "qmake_virtualkeyboard_myscript_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${VKB_LAYOUTS_BASE}"
    FILES
        ${qmake_virtualkeyboard_myscript_layouts_resource_files}
)
