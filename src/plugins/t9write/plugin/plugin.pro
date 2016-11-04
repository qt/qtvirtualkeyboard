TARGET = qtvirtualkeyboard_t9write
QT += qml virtualkeyboard-private

include(../../../shared.pri)

HEADERS += \
    t9write_p.h \
    t9writedictionary_p.h \
    t9writeinputmethod_p.h \
    t9writeplugin.h \
    t9writeworker_p.h
SOURCES += \
    t9writedictionary.cpp \
    t9writeinputmethod.cpp \
    t9writeplugin.cpp \
    t9writeworker.cpp
OTHER_FILES += \
    t9write.json

DEFINES += \
    QT_NO_CAST_TO_ASCII \
    QT_ASCII_CAST_WARNINGS \
    QT_NO_CAST_FROM_ASCII \
    QT_NO_CAST_FROM_BYTEARRAY

include(../3rdparty/t9write/t9write-build.pri)

!qtConfig(t9write-cjk): \
    error("T9Write SDK could not be found. For more information, see" \
          "the documentation in Building Qt Virtual Keyboard")

LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fallback/handwriting.qml
qtConfig(t9write-alphabetic) {
    qtConfig(vkb-lang-en_GB): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/en_GB/handwriting.fallback
    qtConfig(vkb-lang-en_US): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/en_US/handwriting.fallback
    qtConfig(vkb-lang-ar_AR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ar_AR/handwriting.qml
    qtConfig(vkb-lang-bg_BG): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/bg_BG/handwriting.qml
    qtConfig(vkb-lang-cs_CZ): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/cs_CZ/handwriting.qml
    qtConfig(vkb-lang-da_DK): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/da_DK/handwriting.fallback
    qtConfig(vkb-lang-de_DE): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/de_DE/handwriting.fallback
    qtConfig(vkb-lang-el_GR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/el_GR/handwriting.qml
    qtConfig(vkb-lang-es_ES): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/es_ES/handwriting.qml
    qtConfig(vkb-lang-es_MX): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/es_MX/handwriting.qml
    qtConfig(vkb-lang-et_EE): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/et_EE/handwriting.fallback
    qtConfig(vkb-lang-fa_FA): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fa_FA/handwriting.qml
    qtConfig(vkb-lang-fi_FI): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fi_FI/handwriting.fallback
    qtConfig(vkb-lang-fr_FR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fr_FR/handwriting.fallback
    qtConfig(vkb-lang-fr_CA): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fr_CA/handwriting.fallback
    qtConfig(vkb-lang-he_IL): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/he_IL/handwriting.qml
    qtConfig(vkb-lang-hr_HR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/hr_HR/handwriting.qml
    qtConfig(vkb-lang-hu_HU): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/hu_HU/handwriting.qml
    qtConfig(vkb-lang-id_ID): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/id_ID/handwriting.fallback
    qtConfig(vkb-lang-it_IT): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/it_IT/handwriting.fallback
    qtConfig(vkb-lang-ms_MY): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ms_MY/handwriting.fallback
    qtConfig(vkb-lang-nb_NO): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/nb_NO/handwriting.fallback
    qtConfig(vkb-lang-nl_NL): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/nl_NL/handwriting.fallback
    qtConfig(vkb-lang-pl_PL): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/pl_PL/handwriting.fallback
    qtConfig(vkb-lang-pt_BR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/pt_BR/handwriting.fallback
    qtConfig(vkb-lang-pt_PT): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/pt_PT/handwriting.fallback
    qtConfig(vkb-lang-ro_RO): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ro_RO/handwriting.qml
    qtConfig(vkb-lang-ru_RU): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ru_RU/handwriting.fallback
    qtConfig(vkb-lang-sk_SK): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sk_SK/handwriting.fallback
    qtConfig(vkb-lang-sl_SI): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sl_SI/handwriting.fallback
    qtConfig(vkb-lang-sq_AL): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sq_AL/handwriting.fallback
    qtConfig(vkb-lang-sr_SP): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sr_SP/handwriting.qml
    qtConfig(vkb-lang-sv_SE): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sv_SE/handwriting.fallback
    qtConfig(vkb-lang-th_TH): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/th_TH/handwriting.qml
    qtConfig(vkb-lang-tr_TR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/tr_TR/handwriting.fallback
    qtConfig(vkb-lang-uk_UA): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/uk_UA/handwriting.fallback
    qtConfig(vkb-lang-vi_VN): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/vi_VN/handwriting.fallback
}
qtConfig(t9write-cjk) {
    qtConfig(vkb-lang-ja_JP): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ja_JP/handwriting.qml
    qtConfig(vkb-lang-ko_KR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ko_KR/handwriting.qml
    qtConfig(vkb-lang-zh_CN): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/zh_CN/handwriting.qml
    qtConfig(vkb-lang-zh_TW): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/zh_TW/handwriting.qml
}

OTHER_FILES += \
    $$LAYOUT_FILES

virtualkeyboard_t9write_layouts.files = $$LAYOUT_FILES
virtualkeyboard_t9write_layouts.base = $$LAYOUTS_BASE
virtualkeyboard_t9write_layouts.prefix = $$LAYOUTS_PREFIX
RESOURCES += virtualkeyboard_t9write_layouts

DEFINES += HAVE_T9WRITE
QMAKE_USE += t9write_db
INCLUDEPATH += $$T9WRITE_INCLUDE_DIRS
qtConfig(t9write-alphabetic) {
    LIBS += $$T9WRITE_ALPHABETIC_LIBS
    DEFINES += HAVE_T9WRITE_ALPHABETIC
    !isEmpty(T9WRITE_ALPHABETIC_BINS) {
        t9write_alphabetic_bins.files = $$T9WRITE_ALPHABETIC_BINS
        t9write_alphabetic_bins.path = $$[QT_INSTALL_BINS]
        INSTALLS += t9write_alphabetic_bins
        !prefix_build: COPIES += t9write_alphabetic_bins
    }
}
qtConfig(t9write-cjk) {
    LIBS += $$T9WRITE_CJK_LIBS
    DEFINES += HAVE_T9WRITE_CJK
    !isEmpty(T9WRITE_CJK_BINS) {
        t9write_cjk_bins.files = $$T9WRITE_CJK_BINS
        t9write_cjk_bins.path = $$[QT_INSTALL_BINS]
        INSTALLS += t9write_cjk_bins
        !prefix_build: COPIES += t9write_cjk_bins
    }
}

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard T9 Write (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
}

PLUGIN_TYPE = virtualkeyboard
PLUGIN_CLASS_NAME = QtVirtualKeyboardT9WritePlugin
load(qt_plugin)
