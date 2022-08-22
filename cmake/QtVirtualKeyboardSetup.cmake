# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

get_filename_component(VKB_LAYOUTS_BASE "${CMAKE_CURRENT_LIST_DIR}/../src/layouts" REALPATH CACHE)
set(VKB_LAYOUTS_PREFIX "/qt-project.org/imports/QtQuick/VirtualKeyboard/Layouts" CACHE STRING "" FORCE)

set(valid_languages
    ar_AR
    bg_BG
    cs_CZ
    da_DK
    de_DE
    el_GR
    en_GB
    en_US
    es_ES
    es_MX
    et_EE
    fa_FA
    fi_FI
    fr_CA
    fr_FR
    he_IL
    hi_IN
    hr_HR
    hu_HU
    id_ID
    it_IT
    ja_JP
    ko_KR
    ms_MY
    nb_NO
    nl_NL
    pl_PL
    pt_BR
    pt_PT
    ro_RO
    ru_RU
    sk_SK
    sl_SI
    sq_AL
    sr_SP
    sv_SE
    th_TH
    tr_TR
    uk_UA
    vi_VN
    zh_CN
    zh_TW
    zh_HK
)

function(process_vkb_enable)
    if (INPUT_vkb_enable)
        foreach(lang IN LISTS INPUT_vkb_enable)
            if (NOT lang IN_LIST valid_languages)
                message(FATAL_ERROR
                    "Language '${lang}' is not supported by the Qt Virtual Keyboard."
                    "The list of valid languages is:"
                    "${valid_languages}")
            endif()
            set(INPUT_lang_${lang} TRUE)
        endforeach()
    else()
        foreach(lang IN LISTS valid_languages)
            set(INPUT_lang_${lang} TRUE)
        endforeach()
    endif()
endfunction()

function(check_3rdparty_hunspell)
    if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/../src/plugins/hunspell/3rdparty/hunspell/hunspell/src/hunspell/hunspell.h")
        set(VKB_HAVE_3RDPARTY_HUNSPELL TRUE CACHE BOOL "Detection of local Hunspell source code" FORCE)
    else()
        set(VKB_HAVE_3RDPARTY_HUNSPELL FALSE CACHE BOOL "Detection of local Hunspell source code" FORCE)
    endif()
endfunction()

function(process_vkb_style)
    set(INPUT_vkb_style "${vkb-style}" CACHE STRING "" FORCE)
endfunction()

function(process_vkb_hunspell)
    set(INPUT_vkb_hunspell "${vkb-hunspell}" CACHE STRING "" FORCE)
endfunction()

function(process_vkb_cerence_sdk)
    set(INPUT_vkb_cerence_sdk "${vkb-cerence-sdk}" CACHE STRING "" FORCE)
endfunction()

process_vkb_hunspell()
process_vkb_style()
process_vkb_enable()
process_vkb_cerence_sdk()
check_3rdparty_hunspell()
