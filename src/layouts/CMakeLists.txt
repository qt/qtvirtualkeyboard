# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_qml_module(qtvkblayoutsplugin
    URI "QtQuick.VirtualKeyboard.Layouts"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2 1
    PLUGIN_TARGET qtvkblayoutsplugin
    NO_PLUGIN_OPTIONAL
    NO_GENERATE_CPP_EXPORTS
)

set(LAYOUT_FILES
    fallback/dialpad.qml
    fallback/digits.qml
    fallback/main.qml
    fallback/numbers.qml
    fallback/symbols.qml
)
if (FEATURE_vkb_lang_en_GB)
    list(APPEND LAYOUT_FILES
        en_GB/dialpad.fallback
        en_GB/digits.fallback
        en_GB/main.fallback
        en_GB/numbers.fallback
        en_GB/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_en_US)
    list(APPEND LAYOUT_FILES
        en_US/dialpad.fallback
        en_US/digits.fallback
        en_US/main.fallback
        en_US/numbers.fallback
        en_US/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_ar_AR)
    list(APPEND LAYOUT_FILES
        ar_AR/dialpad.fallback
        ar_AR/digits.qml
        ar_AR/main.qml
        ar_AR/numbers.qml
        ar_AR/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_bg_BG)
    list(APPEND LAYOUT_FILES
        bg_BG/dialpad.fallback
        bg_BG/digits.fallback
        bg_BG/main.qml
        bg_BG/numbers.fallback
        bg_BG/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_cs_CZ)
    list(APPEND LAYOUT_FILES
        cs_CZ/dialpad.fallback
        cs_CZ/digits.fallback
        cs_CZ/main.qml
        cs_CZ/numbers.fallback
        cs_CZ/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_da_DK)
    list(APPEND LAYOUT_FILES
        da_DK/dialpad.fallback
        da_DK/digits.fallback
        da_DK/main.qml
        da_DK/numbers.fallback
        da_DK/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_de_DE)
    list(APPEND LAYOUT_FILES
        de_DE/dialpad.fallback
        de_DE/digits.fallback
        de_DE/main.qml
        de_DE/numbers.fallback
        de_DE/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_el_GR)
    list(APPEND LAYOUT_FILES
        el_GR/dialpad.fallback
        el_GR/digits.fallback
        el_GR/main.qml
        el_GR/numbers.fallback
        el_GR/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_es_ES)
    list(APPEND LAYOUT_FILES
        es_ES/dialpad.fallback
        es_ES/digits.fallback
        es_ES/main.qml
        es_ES/numbers.fallback
        es_ES/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_es_MX)
    list(APPEND LAYOUT_FILES
        es_MX/dialpad.fallback
        es_MX/digits.fallback
        es_MX/main.qml
        es_MX/numbers.fallback
        es_MX/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_et_EE)
    list(APPEND LAYOUT_FILES
        et_EE/dialpad.fallback
        et_EE/digits.fallback
        et_EE/main.qml
        et_EE/numbers.fallback
        et_EE/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_fa_FA)
    list(APPEND LAYOUT_FILES
        fa_FA/dialpad.fallback
        fa_FA/digits.qml
        fa_FA/main.qml
        fa_FA/numbers.qml
        fa_FA/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_fi_FI)
    list(APPEND LAYOUT_FILES
        fi_FI/dialpad.fallback
        fi_FI/digits.fallback
        fi_FI/main.qml
        fi_FI/numbers.fallback
        fi_FI/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_fr_CA)
    list(APPEND LAYOUT_FILES
        fr_CA/dialpad.fallback
        fr_CA/digits.fallback
        fr_CA/main.qml
        fr_CA/numbers.fallback
        fr_CA/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_fr_FR)
    list(APPEND LAYOUT_FILES
        fr_FR/dialpad.fallback
        fr_FR/digits.fallback
        fr_FR/main.qml
        fr_FR/numbers.fallback
        fr_FR/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_he_IL)
    list(APPEND LAYOUT_FILES
        he_IL/dialpad.fallback
        he_IL/digits.fallback
        he_IL/main.qml
        he_IL/numbers.fallback
        he_IL/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_hi_IN)
    list(APPEND LAYOUT_FILES
        hi_IN/dialpad.fallback
        hi_IN/digits.fallback
        hi_IN/main.qml
        hi_IN/numbers.fallback
        hi_IN/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_hr_HR)
    list(APPEND LAYOUT_FILES
        hr_HR/dialpad.fallback
        hr_HR/digits.fallback
        hr_HR/main.qml
        hr_HR/numbers.fallback
        hr_HR/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_hu_HU)
    list(APPEND LAYOUT_FILES
        hu_HU/dialpad.fallback
        hu_HU/digits.fallback
        hu_HU/main.qml
        hu_HU/numbers.fallback
        hu_HU/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_id_ID)
    list(APPEND LAYOUT_FILES
        id_ID/dialpad.fallback
        id_ID/digits.fallback
        id_ID/main.fallback
        id_ID/numbers.fallback
        id_ID/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_it_IT)
    list(APPEND LAYOUT_FILES
        it_IT/dialpad.fallback
        it_IT/digits.fallback
        it_IT/main.qml
        it_IT/numbers.fallback
        it_IT/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_lv_LV)
    list(APPEND LAYOUT_FILES
        lv_LV/dialpad.fallback
        lv_LV/digits.fallback
        lv_LV/main.qml
        lv_LV/numbers.fallback
        lv_LV/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_nb_NO)
    list(APPEND LAYOUT_FILES
        nb_NO/dialpad.fallback
        nb_NO/digits.fallback
        nb_NO/main.qml
        nb_NO/numbers.fallback
        nb_NO/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_ms_MY)
    list(APPEND LAYOUT_FILES
        ms_MY/dialpad.fallback
        ms_MY/digits.fallback
        ms_MY/main.fallback
        ms_MY/numbers.fallback
        ms_MY/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_nl_NL)
    list(APPEND LAYOUT_FILES
        nl_NL/dialpad.fallback
        nl_NL/digits.fallback
        nl_NL/main.fallback
        nl_NL/numbers.fallback
        nl_NL/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_pl_PL)
    list(APPEND LAYOUT_FILES
        pl_PL/dialpad.fallback
        pl_PL/digits.fallback
        pl_PL/main.qml
        pl_PL/numbers.fallback
        pl_PL/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_pt_BR)
    list(APPEND LAYOUT_FILES
        pt_BR/dialpad.fallback
        pt_BR/digits.fallback
        pt_BR/main.qml
        pt_BR/numbers.fallback
        pt_BR/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_pt_PT)
    list(APPEND LAYOUT_FILES
        pt_PT/dialpad.fallback
        pt_PT/digits.fallback
        pt_PT/main.qml
        pt_PT/numbers.fallback
        pt_PT/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_ro_RO)
    list(APPEND LAYOUT_FILES
        ro_RO/dialpad.fallback
        ro_RO/digits.fallback
        ro_RO/main.qml
        ro_RO/numbers.fallback
        ro_RO/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_ru_RU)
    list(APPEND LAYOUT_FILES
        ru_RU/dialpad.fallback
        ru_RU/digits.fallback
        ru_RU/main.qml
        ru_RU/numbers.fallback
        ru_RU/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_sk_SK)
    list(APPEND LAYOUT_FILES
        sk_SK/dialpad.fallback
        sk_SK/digits.fallback
        sk_SK/main.qml
        sk_SK/numbers.fallback
        sk_SK/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_sl_SI)
    list(APPEND LAYOUT_FILES
        sl_SI/dialpad.fallback
        sl_SI/digits.fallback
        sl_SI/main.qml
        sl_SI/numbers.fallback
        sl_SI/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_sq_AL)
    list(APPEND LAYOUT_FILES
        sq_AL/dialpad.fallback
        sq_AL/digits.fallback
        sq_AL/main.qml
        sq_AL/numbers.fallback
        sq_AL/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_sr_SP)
    list(APPEND LAYOUT_FILES
        sr_SP/dialpad.fallback
        sr_SP/digits.fallback
        sr_SP/main.qml
        sr_SP/numbers.fallback
        sr_SP/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_sv_SE)
    list(APPEND LAYOUT_FILES
        sv_SE/dialpad.fallback
        sv_SE/digits.fallback
        sv_SE/main.qml
        sv_SE/numbers.fallback
        sv_SE/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_tr_TR)
    list(APPEND LAYOUT_FILES
        tr_TR/dialpad.fallback
        tr_TR/digits.fallback
        tr_TR/main.qml
        tr_TR/numbers.fallback
        tr_TR/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_uk_UA)
    list(APPEND LAYOUT_FILES
        uk_UA/dialpad.fallback
        uk_UA/digits.fallback
        uk_UA/main.qml
        uk_UA/numbers.fallback
        uk_UA/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_vi_VN)
    list(APPEND LAYOUT_FILES
        vi_VN/dialpad.fallback
        vi_VN/digits.fallback
        vi_VN/main.qml
        vi_VN/numbers.fallback
        vi_VN/symbols.qml
    )
endif()

if(QT_FEATURE_vkb_layouts)
    qt_internal_add_resource(qtvkblayoutsplugin "qmake_virtualkeyboard_layouts"
        PREFIX
            "${VKB_LAYOUTS_PREFIX}"
        FILES
            ${LAYOUT_FILES}
    )
endif()
