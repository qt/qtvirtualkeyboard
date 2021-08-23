# Generated from plugin.pro.

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

qt_internal_add_plugin(QtVirtualKeyboardMyScriptPlugin
    OUTPUT_NAME qtvirtualkeyboard_myscript
    PLUGIN_TYPE virtualkeyboard
    SOURCES
        ${MyScript_ROOT_DIR}/voim/api/c/examples/common/Properties.c
        myscriptinputmethod.cpp myscriptinputmethod_p.h
        myscriptinputmethod_p_p.h
        myscriptplugin.cpp myscriptplugin.h
    DEFINES
        MYSCRIPT_CERTIFICATE=\\\"${MyScript_ROOT_DIR}/edk/c/examples/certificates/MyCertificate.c\\\"
        MYSCRIPT_VOIM_PROPERTY_PATH=\\\"${MYSCRIPT_INSTALL_DATA}/${MYSCRIPT_VOIM_PROPERTY_NAME}\\\"
        MYSCRIPT_LANGUAGE_CONF_PATH=\\\"${MYSCRIPT_INSTALL_DATA}/${MYSCRIPT_LANGUAGE_CONF_NAME}\\\"
        MYSCRIPT_VOIM_NAME=\\\"${MYSCRIPT_VOIM_NAME}\\\"
        MYSCRIPT_ENGINE_NAME=\\\"${MYSCRIPT_ENGINE_NAME}\\\"
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
    "${VKB_LAYOUTS_BASE}/content/layouts/fallback/handwriting.qml"
)

# special case begin
if (QT_FEATURE_vkb_lang_en_GB)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/en_GB/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_en_US)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/en_US/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ar_AR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ar_AR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_bg_BG)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/bg_BG/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_cs_CZ)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/cs_CZ/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_da_DK)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/da_DK/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_de_DE)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/de_DE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_el_GR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/el_GR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_es_ES)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/es_ES/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_es_MX)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/es_MX/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_et_EE)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/et_EE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fa_FA)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/fa_FA/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_fi_FI)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/fi_FI/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fr_CA)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/fr_CA/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_fr_FR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/fr_FR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_he_IL)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/he_IL/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_hi_IN)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/hi_IN/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_hr_HR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/hr_HR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_hu_HU)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/hu_HU/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_id_ID)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/id_ID/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_it_IT)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/it_IT/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ja_JP)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_ko_KR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_ms_MY)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ms_MY/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nb_NO)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/nb_NO/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nl_NL)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/nl_NL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pl_PL)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/pl_PL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pt_BR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/pt_BR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_pt_PT)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/pt_PT/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ro_RO)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ro_RO/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_ru_RU)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ru_RU/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_sk_SK)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/sk_SK/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sl_SI)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/sl_SI/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sq_AL)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/sq_AL/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_sr_SP)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/sr_SP/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_sv_SE)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/sv_SE/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_th_TH)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_tr_TR)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/tr_TR/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_uk_UA)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/uk_UA/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_vi_VN)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/vi_VN/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_zh_CN)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/handwriting.qml"
    )
endif()

if (QT_FEATURE_vkb_lang_zh_TW)
    list(APPEND qmake_virtualkeyboard_myscript_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/handwriting.qml"
    )
endif()

# special case end

qt_internal_add_resource(QtVirtualKeyboardMyScriptPlugin "qmake_virtualkeyboard_myscript_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}" # special case
    BASE
        "${VKB_LAYOUTS_BASE}" # special case
    FILES
        ${qmake_virtualkeyboard_myscript_layouts_resource_files}
)


#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# INSTALLS = "myscript_engine_bins" "myscript_voim_conf" "myscript_language_conf" "myscript_resources"
# OTHER_FILES = "myscript.json" "$$LAYOUT_FILES"
# myscript_engine_bins.files = "$$MYSCRIPT_ENGINE_BINS"
# myscript_engine_bins.path = "$$[QT_INSTALL_BINS]"
# myscript_language_conf.files = "$$MYSCRIPT_PATH/$$MYSCRIPT_LANGUAGE_CONF"
# myscript_language_conf.path = "$$[QT_INSTALL_DATA]/$$MYSCRIPT_DATA"
# myscript_resources.files = "$$MYSCRIPT_PATH/$$MYSCRIPT_RESOURCES"
# myscript_resources.path = "$$[QT_INSTALL_DATA]/$$MYSCRIPT_DATA"
# myscript_voim_conf.files = "$$MYSCRIPT_PATH/$$MYSCRIPT_VOIM_CONF"
# myscript_voim_conf.path = "$$[QT_INSTALL_DATA]/$$MYSCRIPT_DATA/voim"

## Scopes:
#####################################################################

#### Keys ignored in scope 3:.:.:plugin.pro:UNIX AND LINUX AND NOT ANDROID:
# QMAKE_RPATHDIR = "$$MYSCRIPT_PATH/$$MYSCRIPT_VOIM_PATH"

#### Keys ignored in scope 4:.:.:plugin.pro:NOT prefix_build:
# COPIES = "myscript_engine_bins" "myscript_voim_conf" "myscript_language_conf" "myscript_resources"

#### Keys ignored in scope 5:.:.:plugin.pro:QT_FEATURE_vkb_lang_en_GB:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/en_GB/handwriting.fallback"

#### Keys ignored in scope 6:.:.:plugin.pro:QT_FEATURE_vkb_lang_en_US:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/en_US/handwriting.fallback"

#### Keys ignored in scope 7:.:.:plugin.pro:QT_FEATURE_vkb_lang_ar_AR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ar_AR/handwriting.qml"

#### Keys ignored in scope 8:.:.:plugin.pro:QT_FEATURE_vkb_lang_bg_BG:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/bg_BG/handwriting.qml"

#### Keys ignored in scope 9:.:.:plugin.pro:QT_FEATURE_vkb_lang_cs_CZ:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/cs_CZ/handwriting.qml"

#### Keys ignored in scope 10:.:.:plugin.pro:QT_FEATURE_vkb_lang_da_DK:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/da_DK/handwriting.fallback"

#### Keys ignored in scope 11:.:.:plugin.pro:QT_FEATURE_vkb_lang_de_DE:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/de_DE/handwriting.fallback"

#### Keys ignored in scope 12:.:.:plugin.pro:QT_FEATURE_vkb_lang_el_GR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/el_GR/handwriting.qml"

#### Keys ignored in scope 13:.:.:plugin.pro:QT_FEATURE_vkb_lang_es_ES:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/es_ES/handwriting.qml"

#### Keys ignored in scope 14:.:.:plugin.pro:QT_FEATURE_vkb_lang_es_MX:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/es_MX/handwriting.qml"

#### Keys ignored in scope 15:.:.:plugin.pro:QT_FEATURE_vkb_lang_et_EE:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/et_EE/handwriting.fallback"

#### Keys ignored in scope 16:.:.:plugin.pro:QT_FEATURE_vkb_lang_fa_FA:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/fa_FA/handwriting.qml"

#### Keys ignored in scope 17:.:.:plugin.pro:QT_FEATURE_vkb_lang_fi_FI:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/fi_FI/handwriting.fallback"

#### Keys ignored in scope 18:.:.:plugin.pro:QT_FEATURE_vkb_lang_fr_FR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/fr_FR/handwriting.fallback"

#### Keys ignored in scope 19:.:.:plugin.pro:QT_FEATURE_vkb_lang_fr_CA:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/fr_CA/handwriting.fallback"

#### Keys ignored in scope 20:.:.:plugin.pro:QT_FEATURE_vkb_lang_he_IL:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/he_IL/handwriting.qml"

#### Keys ignored in scope 21:.:.:plugin.pro:QT_FEATURE_vkb_lang_hi_IN:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/hi_IN/handwriting.qml"

#### Keys ignored in scope 22:.:.:plugin.pro:QT_FEATURE_vkb_lang_hr_HR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/hr_HR/handwriting.qml"

#### Keys ignored in scope 23:.:.:plugin.pro:QT_FEATURE_vkb_lang_hu_HU:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/hu_HU/handwriting.qml"

#### Keys ignored in scope 24:.:.:plugin.pro:QT_FEATURE_vkb_lang_id_ID:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/id_ID/handwriting.fallback"

#### Keys ignored in scope 25:.:.:plugin.pro:QT_FEATURE_vkb_lang_it_IT:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/it_IT/handwriting.fallback"

#### Keys ignored in scope 26:.:.:plugin.pro:QT_FEATURE_vkb_lang_ja_JP:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ja_JP/handwriting.qml"

#### Keys ignored in scope 27:.:.:plugin.pro:QT_FEATURE_vkb_lang_ko_KR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ko_KR/handwriting.qml"

#### Keys ignored in scope 28:.:.:plugin.pro:QT_FEATURE_vkb_lang_ms_MY:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ms_MY/handwriting.fallback"

#### Keys ignored in scope 29:.:.:plugin.pro:QT_FEATURE_vkb_lang_nb_NO:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/nb_NO/handwriting.fallback"

#### Keys ignored in scope 30:.:.:plugin.pro:QT_FEATURE_vkb_lang_nl_NL:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/nl_NL/handwriting.fallback"

#### Keys ignored in scope 31:.:.:plugin.pro:QT_FEATURE_vkb_lang_pl_PL:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/pl_PL/handwriting.fallback"

#### Keys ignored in scope 32:.:.:plugin.pro:QT_FEATURE_vkb_lang_pt_BR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/pt_BR/handwriting.fallback"

#### Keys ignored in scope 33:.:.:plugin.pro:QT_FEATURE_vkb_lang_pt_PT:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/pt_PT/handwriting.fallback"

#### Keys ignored in scope 34:.:.:plugin.pro:QT_FEATURE_vkb_lang_ro_RO:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ro_RO/handwriting.qml"

#### Keys ignored in scope 35:.:.:plugin.pro:QT_FEATURE_vkb_lang_ru_RU:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ru_RU/handwriting.fallback"

#### Keys ignored in scope 36:.:.:plugin.pro:QT_FEATURE_vkb_lang_sk_SK:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/sk_SK/handwriting.fallback"

#### Keys ignored in scope 37:.:.:plugin.pro:QT_FEATURE_vkb_lang_sl_SI:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/sl_SI/handwriting.fallback"

#### Keys ignored in scope 38:.:.:plugin.pro:QT_FEATURE_vkb_lang_sq_AL:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/sq_AL/handwriting.fallback"

#### Keys ignored in scope 39:.:.:plugin.pro:QT_FEATURE_vkb_lang_sr_SP:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/sr_SP/handwriting.qml"

#### Keys ignored in scope 40:.:.:plugin.pro:QT_FEATURE_vkb_lang_sv_SE:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/sv_SE/handwriting.fallback"

#### Keys ignored in scope 41:.:.:plugin.pro:QT_FEATURE_vkb_lang_th_TH:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/th_TH/handwriting.fallback"

#### Keys ignored in scope 42:.:.:plugin.pro:QT_FEATURE_vkb_lang_tr_TR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/tr_TR/handwriting.fallback"

#### Keys ignored in scope 43:.:.:plugin.pro:QT_FEATURE_vkb_lang_uk_UA:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/uk_UA/handwriting.fallback"

#### Keys ignored in scope 44:.:.:plugin.pro:QT_FEATURE_vkb_lang_vi_VN:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/vi_VN/handwriting.fallback"

#### Keys ignored in scope 45:.:.:plugin.pro:QT_FEATURE_vkb_lang_zh_CN:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/zh_CN/handwriting.qml"

#### Keys ignored in scope 46:.:.:plugin.pro:QT_FEATURE_vkb_lang_zh_TW:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/zh_TW/handwriting.qml"

#### Keys ignored in scope 47:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard MyScript (Qt $$QT_VERSION)"
