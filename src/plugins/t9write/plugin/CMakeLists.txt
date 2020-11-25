# Generated from plugin.pro.

#####################################################################
## QtVirtualKeyboardT9WritePlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardT9WritePlugin
    OUTPUT_NAME qtvirtualkeyboard_t9write
    TYPE virtualkeyboard
    SOURCES
        t9write_p.h
        t9writedictionary.cpp t9writedictionary_p.h
        t9writeinputmethod.cpp t9writeinputmethod_p.h
        t9writeplugin.cpp t9writeplugin.h
        t9writeworker.cpp t9writeworker_p.h
    DEFINES
        HAVE_T9WRITE
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    INCLUDE_DIRECTORIES
        api
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboardPrivate
        t9write_db
)

# Resources:
set(qmake_virtualkeyboard_t9write_layouts_resource_files
    "virtualkeyboard/content/layouts/fallback/handwriting.qml"
)

qt_internal_add_resource(QtVirtualKeyboardT9WritePlugin "qmake_virtualkeyboard_t9write_layouts"
    PREFIX
        "$$LAYOUTS_PREFIX"
    BASE
        "$$LAYOUTS_BASE"
    FILES
        ${qmake_virtualkeyboard_t9write_layouts_resource_files}
)


#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# OTHER_FILES = "t9write.json" "$$LAYOUT_FILES"

## Scopes:
#####################################################################

qt_internal_extend_target(QtVirtualKeyboardT9WritePlugin CONDITION QT_FEATURE_t9write_alphabetic
    DEFINES
        HAVE_T9WRITE_ALPHABETIC
)

#### Keys ignored in scope 4:.:.:plugin.pro:QT_FEATURE_vkb_lang_en_GB:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/en_GB/handwriting.fallback"

#### Keys ignored in scope 5:.:.:plugin.pro:QT_FEATURE_vkb_lang_en_US:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/en_US/handwriting.fallback"

#### Keys ignored in scope 6:.:.:plugin.pro:QT_FEATURE_vkb_lang_ar_AR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ar_AR/handwriting.qml"

#### Keys ignored in scope 7:.:.:plugin.pro:QT_FEATURE_vkb_lang_bg_BG:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/bg_BG/handwriting.qml"

#### Keys ignored in scope 8:.:.:plugin.pro:QT_FEATURE_vkb_lang_cs_CZ:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/cs_CZ/handwriting.qml"

#### Keys ignored in scope 9:.:.:plugin.pro:QT_FEATURE_vkb_lang_da_DK:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/da_DK/handwriting.fallback"

#### Keys ignored in scope 10:.:.:plugin.pro:QT_FEATURE_vkb_lang_de_DE:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/de_DE/handwriting.fallback"

#### Keys ignored in scope 11:.:.:plugin.pro:QT_FEATURE_vkb_lang_el_GR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/el_GR/handwriting.qml"

#### Keys ignored in scope 12:.:.:plugin.pro:QT_FEATURE_vkb_lang_es_ES:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/es_ES/handwriting.qml"

#### Keys ignored in scope 13:.:.:plugin.pro:QT_FEATURE_vkb_lang_es_MX:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/es_MX/handwriting.qml"

#### Keys ignored in scope 14:.:.:plugin.pro:QT_FEATURE_vkb_lang_et_EE:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/et_EE/handwriting.fallback"

#### Keys ignored in scope 15:.:.:plugin.pro:QT_FEATURE_vkb_lang_fa_FA:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/fa_FA/handwriting.qml"

#### Keys ignored in scope 16:.:.:plugin.pro:QT_FEATURE_vkb_lang_fi_FI:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/fi_FI/handwriting.fallback"

#### Keys ignored in scope 17:.:.:plugin.pro:QT_FEATURE_vkb_lang_fr_FR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/fr_FR/handwriting.fallback"

#### Keys ignored in scope 18:.:.:plugin.pro:QT_FEATURE_vkb_lang_fr_CA:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/fr_CA/handwriting.fallback"

#### Keys ignored in scope 19:.:.:plugin.pro:QT_FEATURE_vkb_lang_he_IL:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/he_IL/handwriting.qml"

#### Keys ignored in scope 20:.:.:plugin.pro:QT_FEATURE_vkb_lang_hr_HR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/hr_HR/handwriting.qml"

#### Keys ignored in scope 21:.:.:plugin.pro:QT_FEATURE_vkb_lang_hu_HU:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/hu_HU/handwriting.qml"

#### Keys ignored in scope 22:.:.:plugin.pro:QT_FEATURE_vkb_lang_id_ID:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/id_ID/handwriting.fallback"

#### Keys ignored in scope 23:.:.:plugin.pro:QT_FEATURE_vkb_lang_it_IT:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/it_IT/handwriting.fallback"

#### Keys ignored in scope 24:.:.:plugin.pro:QT_FEATURE_vkb_lang_ms_MY:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ms_MY/handwriting.fallback"

#### Keys ignored in scope 25:.:.:plugin.pro:QT_FEATURE_vkb_lang_nb_NO:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/nb_NO/handwriting.fallback"

#### Keys ignored in scope 26:.:.:plugin.pro:QT_FEATURE_vkb_lang_nl_NL:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/nl_NL/handwriting.fallback"

#### Keys ignored in scope 27:.:.:plugin.pro:QT_FEATURE_vkb_lang_pl_PL:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/pl_PL/handwriting.fallback"

#### Keys ignored in scope 28:.:.:plugin.pro:QT_FEATURE_vkb_lang_pt_BR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/pt_BR/handwriting.fallback"

#### Keys ignored in scope 29:.:.:plugin.pro:QT_FEATURE_vkb_lang_pt_PT:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/pt_PT/handwriting.fallback"

#### Keys ignored in scope 30:.:.:plugin.pro:QT_FEATURE_vkb_lang_ro_RO:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ro_RO/handwriting.qml"

#### Keys ignored in scope 31:.:.:plugin.pro:QT_FEATURE_vkb_lang_ru_RU:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ru_RU/handwriting.fallback"

#### Keys ignored in scope 32:.:.:plugin.pro:QT_FEATURE_vkb_lang_sk_SK:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/sk_SK/handwriting.fallback"

#### Keys ignored in scope 33:.:.:plugin.pro:QT_FEATURE_vkb_lang_sl_SI:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/sl_SI/handwriting.fallback"

#### Keys ignored in scope 34:.:.:plugin.pro:QT_FEATURE_vkb_lang_sq_AL:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/sq_AL/handwriting.fallback"

#### Keys ignored in scope 35:.:.:plugin.pro:QT_FEATURE_vkb_lang_sr_SP:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/sr_SP/handwriting.qml"

#### Keys ignored in scope 36:.:.:plugin.pro:QT_FEATURE_vkb_lang_sv_SE:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/sv_SE/handwriting.fallback"

#### Keys ignored in scope 37:.:.:plugin.pro:QT_FEATURE_vkb_lang_th_TH:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/th_TH/handwriting.qml"

#### Keys ignored in scope 38:.:.:plugin.pro:QT_FEATURE_vkb_lang_tr_TR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/tr_TR/handwriting.fallback"

#### Keys ignored in scope 39:.:.:plugin.pro:QT_FEATURE_vkb_lang_uk_UA:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/uk_UA/handwriting.fallback"

#### Keys ignored in scope 40:.:.:plugin.pro:QT_FEATURE_vkb_lang_vi_VN:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/vi_VN/handwriting.fallback"

qt_internal_extend_target(QtVirtualKeyboardT9WritePlugin CONDITION QT_FEATURE_t9write_cjk
    DEFINES
        HAVE_T9WRITE_CJK
)

#### Keys ignored in scope 42:.:.:plugin.pro:QT_FEATURE_vkb_lang_ja_JP:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ja_JP/handwriting.qml"

#### Keys ignored in scope 43:.:.:plugin.pro:QT_FEATURE_vkb_lang_ko_KR:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ko_KR/handwriting.qml"

#### Keys ignored in scope 44:.:.:plugin.pro:QT_FEATURE_vkb_lang_zh_CN:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/zh_CN/handwriting.qml"

#### Keys ignored in scope 45:.:.:plugin.pro:QT_FEATURE_vkb_lang_zh_TW:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/zh_TW/handwriting.qml"

#### Keys ignored in scope 47:.:.:plugin.pro:NOT T9WRITE_ALPHABETIC_BINS_ISEMPTY:
# INSTALLS = "t9write_alphabetic_bins"
# t9write_alphabetic_bins.files = "$$T9WRITE_ALPHABETIC_BINS"
# t9write_alphabetic_bins.path = "$$[QT_INSTALL_BINS]"

#### Keys ignored in scope 48:.:.:plugin.pro:NOT prefix_build:
# COPIES = "t9write_alphabetic_bins"

#### Keys ignored in scope 50:.:.:plugin.pro:NOT T9WRITE_CJK_BINS_ISEMPTY:
# INSTALLS = "t9write_cjk_bins"
# t9write_cjk_bins.files = "$$T9WRITE_CJK_BINS"
# t9write_cjk_bins.path = "$$[QT_INSTALL_BINS]"

#### Keys ignored in scope 51:.:.:plugin.pro:NOT prefix_build:
# COPIES = "t9write_cjk_bins"

#### Keys ignored in scope 52:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard T9 Write (Qt $$QT_VERSION)"

#### Keys ignored in scope 55:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:QT_ARCH___contains___arm:
# T9WRITE_BUILD_SHARED_DIR = "lib/arm/shared"
# T9WRITE_BUILD_STATIC_DIR = "lib/arm/static"

#### Keys ignored in scope 57:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:LINUX:
# T9WRITE_BUILD_SHARED_DIR = "lib/linux/shared"
# T9WRITE_BUILD_STATIC_DIR = "lib/linux/static"

#### Keys ignored in scope 59:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:WIN32:
# T9WRITE_BUILD_SHARED_DIR = "lib/win32/shared"
# T9WRITE_BUILD_STATIC_DIR = "lib/win32/static"

#### Keys ignored in scope 61:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:WIN32:
# result = "$$1/*.obj"

#### Keys ignored in scope 62:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:result_ISEMPTY:
# result = "$$1/*.lib"

#### Keys ignored in scope 63:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:else:
# result = "$$1/*.o"

#### Keys ignored in scope 64:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:result_ISEMPTY:
# result = "$$1/*.a"

#### Keys ignored in scope 66:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:WIN32:
# result = "$$1/*.lib"

#### Keys ignored in scope 67:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:else:
# result = "$$1/*.so"

#### Keys ignored in scope 69:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:WIN32:
# result = "$$1/*.dll"

#### Keys ignored in scope 70:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:else:
# result = "$$1/*.so"

#### Keys ignored in scope 72:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:(T9WRITE_ALPHABETIC_FOUND EQUAL 1):
# T9WRITE_ALPHABETIC_LIBS = "$$findSharedLibrary($$PWD/$$T9WRITE_BUILD_SHARED_DIR/alphabetic)"

#### Keys ignored in scope 73:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:NOT T9WRITE_ALPHABETIC_LIBS_ISEMPTY:
# T9WRITE_ALPHABETIC_BINS = "$$findSharedBinary($$PWD/$$T9WRITE_BUILD_SHARED_DIR/alphabetic)"

#### Keys ignored in scope 74:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:else:
# T9WRITE_ALPHABETIC_LIBS = "$$findStaticLibrary($$PWD/$$T9WRITE_BUILD_STATIC_DIR/alphabetic)"

#### Keys ignored in scope 75:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:(T9WRITE_CJK_FOUND EQUAL 1):
# T9WRITE_CJK_LIBS = "$$findSharedLibrary($$PWD/$$T9WRITE_BUILD_SHARED_DIR/cjk)"

#### Keys ignored in scope 76:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:NOT T9WRITE_CJK_LIBS_ISEMPTY:
# T9WRITE_CJK_BINS = "$$findSharedBinary($$PWD/$$T9WRITE_BUILD_SHARED_DIR/cjk)"

#### Keys ignored in scope 77:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:else:
# T9WRITE_CJK_LIBS = "$$findStaticLibrary($$PWD/$$T9WRITE_BUILD_STATIC_DIR/cjk)"

#### Keys ignored in scope 78:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:(T9WRITE_ALPHABETIC_FOUND EQUAL 1) AND NOT T9WRITE_ALPHABETIC_LIBS_ISEMPTY:
# T9WRITE_FOUND = "1"

#### Keys ignored in scope 79:.:../3rdparty/t9write:../3rdparty/t9write/t9write-build.pri:(T9WRITE_CJK_FOUND EQUAL 1) AND NOT T9WRITE_CJK_LIBS_ISEMPTY:
# T9WRITE_FOUND = "1"
