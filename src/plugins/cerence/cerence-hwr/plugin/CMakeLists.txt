# Generated from plugin.pro.

#####################################################################
## QtVirtualKeyboardCerenceHwrPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardCerenceHwrPlugin
    OUTPUT_NAME qtvirtualkeyboard_cerence_hwr
    PLUGIN_TYPE virtualkeyboard
    SOURCES
        cerence_hwr_p.h
        qtvirtualkeyboardcerencehwrplugin.cpp qtvirtualkeyboardcerencehwrplugin.h
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
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboardPrivate
)

# Resources:
set(qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/content/layouts/fallback/handwriting.qml"
)

if (QT_FEATURE_vkb_lang_en_GB)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/en_GB/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_en_US)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/en_US/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ar_AR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ar_AR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_bg_BG)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/bg_BG/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_cs_CZ)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/cs_CZ/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_da_DK)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/da_DK/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_de_DE)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/de_DE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_el_GR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/el_GR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_es_ES)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/es_ES/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_es_MX)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/es_MX/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_et_EE)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/et_EE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fa_FA)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/fa_FA/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_fi_FI)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/fi_FI/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fr_FR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/fr_FR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fr_CA)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/fr_CA/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_he_IL)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/he_IL/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_hr_HR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/hr_HR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_hu_HU)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/hu_HU/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_id_ID)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/id_ID/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_it_IT)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/it_IT/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ms_MY)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ms_MY/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nb_NO)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/nb_NO/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nl_NL)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/nl_NL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pl_PL)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/pl_PL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pt_BR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/pt_BR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pt_PT)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/pt_PT/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ro_RO)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ro_RO/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_ru_RU)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ru_RU/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_sk_SK)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/sk_SK/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sl_SI)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/sl_SI/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sq_AL)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/sq_AL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sr_SP)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/sr_SP/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_sv_SE)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/sv_SE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_th_TH)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_tr_TR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/tr_TR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_uk_UA)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/uk_UA/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_vi_VN)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/vi_VN/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ja_JP)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_ko_KR)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_zh_CN)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_zh_TW)
    list(APPEND qmake_virtualkeyboard_cerence_hwr_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/handwriting.qml"
    )
endif()

qt_internal_add_resource(QtVirtualKeyboardCerenceHwrPlugin "qmake_virtualkeyboard_cerence_hwr_layouts"
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

qt_internal_add_resource(QtVirtualKeyboardCerenceHwrPlugin "qmake_virtualkeyboard_cerence_hwr_custom_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES
        ${qmake_virtualkeyboard_cerence_hwr_custom_layouts_resource_files}
)

#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# DISTFILES = "cerence_hwr.json"
# OTHER_FILES = "$$LAYOUT_FILES"
# virtualkeyboard_cerence_hwr_custom_layouts.base = "$$PWD"
# virtualkeyboard_cerence_hwr_custom_layouts.prefix = "$$LAYOUTS_PREFIX"

## Scopes:
#####################################################################

qt_internal_extend_target(QtVirtualKeyboardCerenceHwrPlugin CONDITION QT_FEATURE_cerence_xt9
    DEFINES
        HAVE_XT9
    LIBRARIES
        Qt::BundledXt9Common
)

qt_internal_extend_target(QtVirtualKeyboardCerenceHwrPlugin CONDITION QT_FEATURE_cerence_hwr_alphabetic
    DEFINES
        HAVE_CERENCE_HWR_ALPHABETIC
    LIBRARIES
        Cerence::HWR::Alphabetic
)

qt_internal_extend_target(QtVirtualKeyboardCerenceHwrPlugin CONDITION QT_FEATURE_cerence_hwr_cjk
    DEFINES
        HAVE_CERENCE_HWR_CJK
    LIBRARIES
        Cerence::HWR::CJK
)

qt_internal_extend_target(QtVirtualKeyboardCerenceHwrPlugin CONDITION FEATURE_vkb_bundle_cerence OR FEATURE_vkb_bundle_cerence_hwr
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

    qt_internal_add_resource(QtVirtualKeyboardCerenceHwrPlugin "qmake_cerencehwrdata_db"
        PREFIX
            "/QtQuick/VirtualKeyboard/Cerence/Handwriting"
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

#### Keys ignored in scope 48:.:.:plugin.pro:FEATURE_vkb_bundle_cerence OR FEATURE_vkb_bundle_cerence_hwr:
# QMAKE_RESOURCE_FLAGS = "-no-compress"

#### Keys ignored in scope 50:.:.:plugin.pro:NOT CERENCE_HWR_ALPHABETIC_BINS_ISEMPTY:
# INSTALLS = "t9write_alphabetic_bins"
# t9write_alphabetic_bins.files = "$$CERENCE_HWR_ALPHABETIC_BINS"

#### Keys ignored in scope 51:.:.:plugin.pro:WIN32 OR win64:
# t9write_alphabetic_bins.path = "$$[QT_INSTALL_BINS]"

#### Keys ignored in scope 52:.:.:plugin.pro:else:
# t9write_alphabetic_bins.path = "$$[QT_INSTALL_LIBS]"

#### Keys ignored in scope 53:.:.:plugin.pro:NOT prefix_build:
# COPIES = "t9write_alphabetic_bins"

#### Keys ignored in scope 55:.:.:plugin.pro:NOT CERENCE_HWR_CJK_BINS_ISEMPTY:
# INSTALLS = "t9write_cjk_bins"
# t9write_cjk_bins.files = "$$CERENCE_HWR_CJK_BINS"

#### Keys ignored in scope 56:.:.:plugin.pro:WIN32 OR win64:
# t9write_cjk_bins.path = "$$[QT_INSTALL_BINS]"

#### Keys ignored in scope 57:.:.:plugin.pro:else:
# t9write_cjk_bins.path = "$$[QT_INSTALL_LIBS]"

#### Keys ignored in scope 58:.:.:plugin.pro:NOT prefix_build:
# COPIES = "t9write_cjk_bins"

#### Keys ignored in scope 59:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Cerence Handwriting (Qt $$QT_VERSION)"

#### Keys ignored in scope 105:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:MYSCRIPT_PATH_ISEMPTY:
# MYSCRIPT_PATH = "$$PWD"

#### Keys ignored in scope 106:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:UNIX AND LINUX AND NOT ANDROID:
# MYSCRIPT_LIB_PREFIX = "lib"
# MYSCRIPT_LIB_SUFFIX = ".so"
# MYSCRIPT_VOIM_LIB_NAME = "libvoim.so"
# MYSCRIPT_VOIM_LIB_PATH = "$$MYSCRIPT_PATH/$$MYSCRIPT_VOIM_PATH/$$MYSCRIPT_VOIM_LIB_NAME"

#### Keys ignored in scope 107:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___arm64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-arm64"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-arm64"

#### Keys ignored in scope 109:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___arm:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-armv7"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-armv7"

#### Keys ignored in scope 111:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86_64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-x64"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-x64"

#### Keys ignored in scope 113:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86 OR QT_ARCH___equals___i386:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-x86"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-x86"

#### Keys ignored in scope 114:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:else:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-$$QT_ARCH"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-$$QT_ARCH"

#### Keys ignored in scope 116:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:WIN32 OR win64:
# MYSCRIPT_LIB_PREFIX = ""
# MYSCRIPT_LIB_SUFFIX = ".dll"
# MYSCRIPT_VOIM_LIB_NAME = "voim.lib"
# MYSCRIPT_VOIM_LIB_PATH = "$$MYSCRIPT_PATH/voim/api/c/lib/$$MYSCRIPT_VOIM_LIB_NAME"

#### Keys ignored in scope 117:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86_64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/win-x64"
# MYSCRIPT_VOIM_PATH = "voim/bin/win-x64"

#### Keys ignored in scope 118:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:else:
# MYSCRIPT_ENGINE_PATH = "engine/bin/win-x86"
# MYSCRIPT_VOIM_PATH = "voim/bin/win-x86"

#### Keys ignored in scope 120:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:EXISTS _ss_MYSCRIPT_VOIM_LIB_PATH:
# MYSCRIPT_FOUND = "1"

#### Keys ignored in scope 122:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:MYSCRIPT_PATH_ISEMPTY:
# MYSCRIPT_PATH = "$$PWD"

#### Keys ignored in scope 123:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:UNIX AND LINUX AND NOT ANDROID:
# MYSCRIPT_LIB_PREFIX = "lib"
# MYSCRIPT_LIB_SUFFIX = ".so"
# MYSCRIPT_VOIM_LIB_NAME = "libvoim.so"
# MYSCRIPT_VOIM_LIB_PATH = "$$MYSCRIPT_PATH/$$MYSCRIPT_VOIM_PATH/$$MYSCRIPT_VOIM_LIB_NAME"

#### Keys ignored in scope 124:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___arm64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-arm64"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-arm64"

#### Keys ignored in scope 126:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___arm:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-armv7"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-armv7"

#### Keys ignored in scope 128:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86_64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-x64"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-x64"

#### Keys ignored in scope 130:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86 OR QT_ARCH___equals___i386:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-x86"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-x86"

#### Keys ignored in scope 131:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:else:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-$$QT_ARCH"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-$$QT_ARCH"

#### Keys ignored in scope 133:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:WIN32 OR win64:
# MYSCRIPT_LIB_PREFIX = ""
# MYSCRIPT_LIB_SUFFIX = ".dll"
# MYSCRIPT_VOIM_LIB_NAME = "voim.lib"
# MYSCRIPT_VOIM_LIB_PATH = "$$MYSCRIPT_PATH/voim/api/c/lib/$$MYSCRIPT_VOIM_LIB_NAME"

#### Keys ignored in scope 134:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86_64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/win-x64"
# MYSCRIPT_VOIM_PATH = "voim/bin/win-x64"

#### Keys ignored in scope 135:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:else:
# MYSCRIPT_ENGINE_PATH = "engine/bin/win-x86"
# MYSCRIPT_VOIM_PATH = "voim/bin/win-x86"

#### Keys ignored in scope 137:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:EXISTS _ss_MYSCRIPT_VOIM_LIB_PATH:
# MYSCRIPT_FOUND = "1"

#### Keys ignored in scope 139:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:CERENCE_SDK_ROOT_ISEMPTY:
# EXT_CERENCE_SDK_ROOT = "$$(CERENCE_SDK_ROOT)"

#### Keys ignored in scope 140:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:NOT EXT_CERENCE_SDK_ROOT_ISEMPTY:
# CERENCE_SDK_ROOT = "$$EXT_CERENCE_SDK_ROOT"

#### Keys ignored in scope 142:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:CERENCE_SDK_ROOT_ISEMPTY:
# CERENCE_SDK_ROOT = "$$PWD/sdk"

#### Keys ignored in scope 145:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:QT_ARCH___equals___arm:
# CERENCE_SHARED_LIB_PATH = "lib/linux/arm/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/arm/static"

#### Keys ignored in scope 147:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:QT_ARCH___equals___arm64:
# CERENCE_SHARED_LIB_PATH = "lib/linux/arm64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/arm64/static"

#### Keys ignored in scope 149:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:QT_ARCH___equals___x86_64:
# CERENCE_SHARED_LIB_PATH = "lib/linux/x86_64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/x86_64/static"

#### Keys ignored in scope 151:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:QT_ARCH___equals___x86 OR QT_ARCH___equals___i386:
# CERENCE_SHARED_LIB_PATH = "lib/linux/x86/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/x86/static"

#### Keys ignored in scope 154:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:QT_ARCH___equals___x86_64:
# CERENCE_SHARED_LIB_PATH = "lib/win32/x86_64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/win32/x86_64/static"

#### Keys ignored in scope 155:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:else:
# CERENCE_SHARED_LIB_PATH = "lib/win32/x86/shared"
# CERENCE_STATIC_LIB_PATH = "lib/win32/x86/static"

#### Keys ignored in scope 157:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:WIN32:
# result = "$$1/*.obj"

#### Keys ignored in scope 158:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:result_ISEMPTY:
# result = "$$1/*.lib"

#### Keys ignored in scope 159:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:else:
# result = "$$1/*.o"

#### Keys ignored in scope 160:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:result_ISEMPTY:
# result = "$$1/*.a"

#### Keys ignored in scope 162:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:WIN32:
# result = "$$1/*.lib"

#### Keys ignored in scope 163:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:else:
# result = "$$1/*.so"

#### Keys ignored in scope 165:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:WIN32:
# result = "$$1/*.dll"

#### Keys ignored in scope 166:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:else:
# result = "$$1/*.so"

#### Keys ignored in scope 167:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:EXISTS _ss_CERENCE_HWR_INCLUDEPATH/decuma_hwr.h:
# CERENCE_HWR_ALPHABETIC_FOUND = "1"

#### Keys ignored in scope 168:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:EXISTS _ss_CERENCE_HWR_INCLUDEPATH/decuma_hwr_cjk.h:
# CERENCE_HWR_CJK_FOUND = "1"

#### Keys ignored in scope 171:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:NOT cerence-hwr-static:
# CERENCE_HWR_ALPHABETIC_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/alphabetic)"

#### Keys ignored in scope 172:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:NOT CERENCE_HWR_ALPHABETIC_LIBS_ISEMPTY:
# CERENCE_HWR_ALPHABETIC_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/alphabetic)"

#### Keys ignored in scope 173:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:else:
# CERENCE_HWR_ALPHABETIC_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_STATIC_LIB_PATH/alphabetic)"

#### Keys ignored in scope 175:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:NOT cerence-hwr-static:
# CERENCE_HWR_CJK_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/cjk)"

#### Keys ignored in scope 176:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:NOT CERENCE_HWR_CJK_LIBS_ISEMPTY:
# CERENCE_HWR_CJK_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/cjk)"

#### Keys ignored in scope 177:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:else:
# CERENCE_HWR_CJK_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_STATIC_LIB_PATH/cjk)"

#### Keys ignored in scope 178:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:(CERENCE_HWR_ALPHABETIC_FOUND EQUAL 1) AND NOT CERENCE_HWR_ALPHABETIC_LIBS_ISEMPTY:
# CERENCE_HWR_FOUND = "1"

#### Keys ignored in scope 179:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:(CERENCE_HWR_CJK_FOUND EQUAL 1) AND NOT CERENCE_HWR_CJK_LIBS_ISEMPTY:
# CERENCE_HWR_FOUND = "1"

#### Keys ignored in scope 180:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:EXISTS _ss_XT9_INCLUDEPATH/et9api.h:
# XT9_FOUND = "1"

#### Keys ignored in scope 182:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:NOT QT_FEATURE_xt9_static:
# XT9_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_SHARED_LIB_PATH)"

#### Keys ignored in scope 183:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:NOT XT9_LIBS_ISEMPTY:
# XT9_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_SHARED_LIB_PATH)"

#### Keys ignored in scope 184:.:../../../../plugins/cerence:../../../../plugins/cerence/cerence.pri:else:
# XT9_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_STATIC_LIB_PATH)"
