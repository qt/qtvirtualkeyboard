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
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/plugins/hunspell/3rdparty/hunspell/src/hunspell/hunspell.h" AND
            EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/plugins/hunspell/3rdparty/hunspell/data")
        set(VKB_HAVE_3RDPARTY_HUNSPELL TRUE CACHE BOOL "Detection of local Hunspell source code" FORCE)
    else()
        set(VKB_HAVE_3RDPARTY_HUNSPELL FALSE CACHE BOOL "Detection of local Hunspell source code" FORCE)
    endif()
endfunction()

set(__t9write_base_dir "src/plugins/t9write/3rdparty/t9write")
function(t9write_find_library output_found name)
    if (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm")
        set(lib_dir "${__t9write_base_dir}/lib/arm/shared")
    elseif(UNIX AND NOT APPLE)
        set(lib_dir "${__t9write_base_dir}/lib/linux-x86/shared")
    elseif(WIN32)
        set(lib_dir "${__t9write_base_dir}/lib/win32/shared")
    else()
        set(${output_found} FALSE PARENT_SCOPE)
        return()
    endif()

    if (WIN32)
        file(GLOB result "${lib_dir}/${mame}/*.obj")
        if (NOT result)
            file(GLOB result "${lib_dir}/${mame}/*.lib")
        endif()
        if (NOT result)
            set(${output_found} FALSE PARENT_SCOPE)
            return()
        endif()
    else()
        file(GLOB result "${lib_dir}/${mame}/*.o")
        if (NOT result)
            file(GLOB result "${lib_dir}/${mame}/*.a")
        endif()
        if (NOT result)
            file(GLOB result "${lib_dir}/${mame}/*.so")
        endif()
        if (NOT result)
            set(${output_found} FALSE PARENT_SCOPE)
            return()
        endif()
    endif()
    set(${output_found} TRUE PARENT_SCOPE)
endfunction()

function(check_t9write_alpha)
    t9write_find_library(found_alpha "alphabetic")
    if (EXISTS "${__t9write_base_dir}/api/decuma_hwr.h" AND found_alpha)
        set(VKB_HAVE_T9WRITE_ALPHA TRUE CACHE STRING "" FORCE)
    else()
        set(VKB_HAVE_T9WRITE_ALPHA FALSE CACHE STRING "" FORCE)
    endif()
endfunction()

function(check_t9write_cjk)
    t9write_find_library(found_alpha "cjk")
    if (EXISTS "${__t9write_base_dir}/api/decuma_hwr_cjk.h" AND found_alpha)
        set(VKB_HAVE_T9WRITE_CJK TRUE CACHE STRING "" FORCE)
    else()
        set(VKB_HAVE_T9WRITE_CJK FALSE CACHE STRING "" FORCE)
    endif()
endfunction()

function(process_vkb_style)
    set(INPUT_vkb_style "${vkb-style}" CACHE STRING "" FORCE)
endfunction()

function(process_vkb_handwriting)
    set(INPUT_vkb_handwriting "${vkb-handwriting}" CACHE STRING "" FORCE)
endfunction()

function(process_vkb_hunspell)
    set(INPUT_vkb_hunspell "${vkb-hunspell}" CACHE STRING "" FORCE)
endfunction()

process_vkb_hunspell()
process_vkb_style()
process_vkb_enable()
process_vkb_handwriting()
check_3rdparty_hunspell()
check_t9write_alpha()
check_t9write_cjk()

