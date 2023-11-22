# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## BundledCerencecommon Generic Library:
#####################################################################

qt_internal_add_3rdparty_library(BundledCerencecommon
    QMAKE_LIB_NAME cerencecommon
    STATIC
    SOURCES
        xt9dbfile.cpp xt9dbfile.h
        xt9ldbmanager.cpp xt9ldbmanager.h
    PUBLIC_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::VirtualKeyboardPrivate
)

qt_internal_extend_target(BundledCerencecommon CONDITION FEATURE_vkb_bundle_cerence OR FEATURE_vkb_bundle_cerence_xt9
    PUBLIC_DEFINES
        HAVE_XT9_RESOURCE
)

qt_internal_extend_target(BundledCerencecommon CONDITION FEATURE_vkb_cerence_xt9_debug
    PUBLIC_DEFINES
        XT9_DEBUG
)

if(FEATURE_vkb_bundle_cerence OR FEATURE_vkb_bundle_cerence_xt9)

    set(qmake_cerencecommondata_db_resource_files)

    foreach(lang IN LISTS valid_languages)
        if(FEATURE_vkb_lang_${lang})
            if(${lang} STREQUAL "en_GB")
                set(ldb_glob "EN*UK*.ldb")
            elseif(${lang} STREQUAL "en_US")
                set(ldb_glob "EN*US*.ldb")
            elseif(${lang} STREQUAL "es_ES")
                set(ldb_glob "ESusUN_*.ldb")
            elseif(${lang} STREQUAL "es_MX")
                set(ldb_glob "ESusUNlatam_*.ldb")
            elseif(${lang} STREQUAL "fr_FR")
                set(ldb_glob "FRusUN_*.ldb")
            elseif(${lang} STREQUAL "fr_CA")
                set(ldb_glob "FRusUNCA_*.ldb")
            elseif(${lang} STREQUAL "ko_KR")
                set(ldb_glob "KOusUN_xt9_ALM3.ldb")
            elseif(${lang} STREQUAL "pt_PT")
                set(ldb_glob "PTusUN_*.ldb")
            elseif(${lang} STREQUAL "pt_BR")
                set(ldb_glob "PTusUNBR_*.ldb")
            elseif(${lang} STREQUAL "zh_CN")
                set(ldb_glob "ZHsbUNps_GB18030_*.ldb")
            elseif(${lang} STREQUAL "zh_TW")
                set(ldb_glob "ZHtbUNps_Big5_*.ldb")
            elseif(${lang} STREQUAL "zh_HK")
                set(ldb_glob "ZHtbUNps_Big5HKSCS_*.ldb")
            else()
                string(SUBSTRING ${lang} 0 2 lang_code)
                string(TOUPPER lang_code ${lang_code})
                set(ldb_glob "${lang_code}*.ldb")
            endif()
            file(GLOB resource_glob_0 RELATIVE "${CERENCE_XT9_DATAPATH}" "${CERENCE_XT9_DATAPATH}/${ldb_glob}")
            foreach(file IN LISTS resource_glob_0)
                set_source_files_properties("${CERENCE_XT9_DATAPATH}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
            endforeach()
            list(APPEND qmake_cerencecommondata_db_resource_files ${resource_glob_0})
        endif()
    endforeach()

    list(REMOVE_DUPLICATES qmake_cerencecommondata_db_resource_files)

    qt_internal_add_resource(BundledCerencecommon "qmake_cerencecommondata_db"
        PREFIX
            "/qt-project.org/imports/QtQuick/VirtualKeyboard/Cerence/Xt9"
        BASE
            "${CERENCE_XT9_DATAPATH}"
        FILES
            ${qmake_cerencecommondata_db_resource_files}
        OPTIONS
            -no-compress
    )
else()
    qt_copy_or_install(
        DIRECTORY "${CERENCE_XT9_DATAPATH}/"
        DESTINATION "${VKB_INSTALL_DATA}/cerence/xt9"
        FILES_MATCHING
        PATTERN "*.ldb"
    )
endif()
