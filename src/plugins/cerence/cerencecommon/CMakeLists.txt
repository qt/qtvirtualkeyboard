# Generated from cerencecommon.pro.

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

## Scopes:
#####################################################################

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
            "/QtQuick/VirtualKeyboard/Cerence/Xt9"
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

#### Keys ignored in scope 2:.:.:cerencecommon.pro:FEATURE_vkb_bundle_cerence OR FEATURE_vkb_bundle_cerence_xt9:
# QMAKE_RESOURCE_FLAGS = "-no-compress"

#### Keys ignored in scope 3:.:.:cerencecommon.pro:COMMON_RESOURCE_FILES_ISEMPTY:
# COMMON_RESOURCE_FILES = "dummy.txt"

#### Keys ignored in scope 5:.:..:../cerence.pri:CERENCE_SDK_ROOT_ISEMPTY:
# EXT_CERENCE_SDK_ROOT = "$$(CERENCE_SDK_ROOT)"

#### Keys ignored in scope 6:.:..:../cerence.pri:NOT EXT_CERENCE_SDK_ROOT_ISEMPTY:
# CERENCE_SDK_ROOT = "$$EXT_CERENCE_SDK_ROOT"

#### Keys ignored in scope 8:.:..:../cerence.pri:CERENCE_SDK_ROOT_ISEMPTY:
# CERENCE_SDK_ROOT = "$$PWD/sdk"

#### Keys ignored in scope 11:.:..:../cerence.pri:QT_ARCH___equals___arm:
# CERENCE_SHARED_LIB_PATH = "lib/linux/arm/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/arm/static"

#### Keys ignored in scope 13:.:..:../cerence.pri:QT_ARCH___equals___arm64:
# CERENCE_SHARED_LIB_PATH = "lib/linux/arm64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/arm64/static"

#### Keys ignored in scope 15:.:..:../cerence.pri:QT_ARCH___equals___x86_64:
# CERENCE_SHARED_LIB_PATH = "lib/linux/x86_64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/x86_64/static"

#### Keys ignored in scope 17:.:..:../cerence.pri:QT_ARCH___equals___x86 OR QT_ARCH___equals___i386:
# CERENCE_SHARED_LIB_PATH = "lib/linux/x86/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/x86/static"

#### Keys ignored in scope 20:.:..:../cerence.pri:QT_ARCH___equals___x86_64:
# CERENCE_SHARED_LIB_PATH = "lib/win32/x86_64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/win32/x86_64/static"

#### Keys ignored in scope 21:.:..:../cerence.pri:else:
# CERENCE_SHARED_LIB_PATH = "lib/win32/x86/shared"
# CERENCE_STATIC_LIB_PATH = "lib/win32/x86/static"

#### Keys ignored in scope 23:.:..:../cerence.pri:WIN32:
# result = "$$1/*.obj"

#### Keys ignored in scope 24:.:..:../cerence.pri:result_ISEMPTY:
# result = "$$1/*.lib"

#### Keys ignored in scope 25:.:..:../cerence.pri:else:
# result = "$$1/*.o"

#### Keys ignored in scope 26:.:..:../cerence.pri:result_ISEMPTY:
# result = "$$1/*.a"

#### Keys ignored in scope 28:.:..:../cerence.pri:WIN32:
# result = "$$1/*.lib"

#### Keys ignored in scope 29:.:..:../cerence.pri:else:
# result = "$$1/*.so"

#### Keys ignored in scope 31:.:..:../cerence.pri:WIN32:
# result = "$$1/*.dll"

#### Keys ignored in scope 32:.:..:../cerence.pri:else:
# result = "$$1/*.so"

#### Keys ignored in scope 33:.:..:../cerence.pri:EXISTS _ss_CERENCE_HWR_INCLUDEPATH/decuma_hwr.h:
# CERENCE_HWR_ALPHABETIC_FOUND = "1"

#### Keys ignored in scope 34:.:..:../cerence.pri:EXISTS _ss_CERENCE_HWR_INCLUDEPATH/decuma_hwr_cjk.h:
# CERENCE_HWR_CJK_FOUND = "1"

#### Keys ignored in scope 37:.:..:../cerence.pri:NOT cerence-hwr-static:
# CERENCE_HWR_ALPHABETIC_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/alphabetic)"

#### Keys ignored in scope 38:.:..:../cerence.pri:NOT CERENCE_HWR_ALPHABETIC_LIBS_ISEMPTY:
# CERENCE_HWR_ALPHABETIC_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/alphabetic)"

#### Keys ignored in scope 39:.:..:../cerence.pri:else:
# CERENCE_HWR_ALPHABETIC_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_STATIC_LIB_PATH/alphabetic)"

#### Keys ignored in scope 41:.:..:../cerence.pri:NOT cerence-hwr-static:
# CERENCE_HWR_CJK_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/cjk)"

#### Keys ignored in scope 42:.:..:../cerence.pri:NOT CERENCE_HWR_CJK_LIBS_ISEMPTY:
# CERENCE_HWR_CJK_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/cjk)"

#### Keys ignored in scope 43:.:..:../cerence.pri:else:
# CERENCE_HWR_CJK_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_STATIC_LIB_PATH/cjk)"

#### Keys ignored in scope 44:.:..:../cerence.pri:(CERENCE_HWR_ALPHABETIC_FOUND EQUAL 1) AND NOT CERENCE_HWR_ALPHABETIC_LIBS_ISEMPTY:
# CERENCE_HWR_FOUND = "1"

#### Keys ignored in scope 45:.:..:../cerence.pri:(CERENCE_HWR_CJK_FOUND EQUAL 1) AND NOT CERENCE_HWR_CJK_LIBS_ISEMPTY:
# CERENCE_HWR_FOUND = "1"

#### Keys ignored in scope 46:.:..:../cerence.pri:EXISTS _ss_XT9_INCLUDEPATH/et9api.h:
# XT9_FOUND = "1"

#### Keys ignored in scope 48:.:..:../cerence.pri:NOT QT_FEATURE_xt9_static:
# XT9_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_SHARED_LIB_PATH)"

#### Keys ignored in scope 49:.:..:../cerence.pri:NOT XT9_LIBS_ISEMPTY:
# XT9_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_SHARED_LIB_PATH)"

#### Keys ignored in scope 50:.:..:../cerence.pri:else:
# XT9_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_STATIC_LIB_PATH)"
