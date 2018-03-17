TARGET  = qtvirtualkeyboardplugin
DATAPATH = $$[QT_INSTALL_DATA]/qtvirtualkeyboard

QMAKE_DOCS = $$PWD/doc/qtvirtualkeyboard.qdocconf
include(doc/doc.pri)

QT += qml quick gui gui-private core-private
CONFIG += qtquickcompiler

win32 {
    CONFIG += no-pkg-config
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
}

!no-pkg-config: CONFIG += link_pkgconfig

include(../config.pri)

SOURCES += platforminputcontext.cpp \
    inputcontext.cpp \
    abstractinputmethod.cpp \
    plaininputmethod.cpp \
    inputengine.cpp \
    shifthandler.cpp \
    plugin.cpp \
    inputmethod.cpp \
    inputselectionhandle.cpp \
    selectionlistmodel.cpp \
    defaultinputmethod.cpp \
    abstractinputpanel.cpp \
    enterkeyaction.cpp \
    enterkeyactionattachedtype.cpp \
    settings.cpp \
    virtualkeyboardsettings.cpp \
    trace.cpp \
    desktopinputselectioncontrol.cpp \
    shadowinputcontext.cpp \
    gesturerecognizer.cpp \
    handwritinggesturerecognizer.cpp

HEADERS += platforminputcontext.h \
    inputcontext.h \
    abstractinputmethod.h \
    plaininputmethod.h \
    inputengine.h \
    shifthandler.h \
    inputmethod.h \
    inputselectionhandle.h \
    selectionlistmodel.h \
    defaultinputmethod.h \
    abstractinputpanel.h \
    virtualkeyboarddebug.h \
    enterkeyaction.h \
    enterkeyactionattachedtype.h \
    settings.h \
    virtualkeyboardsettings.h \
    plugin.h \
    trace.h \
    desktopinputselectioncontrol.h \
    shadowinputcontext.h \
    gesturerecognizer.h \
    handwritinggesturerecognizer.h

RESOURCES += \
    content/styles/default/default_style.qrc \
    content/styles/retro/retro_style.qrc \
    content/content.qrc

# Fallback for languages which don't have these special layouts
LAYOUT_FILES += \
    content/layouts/en_GB/dialpad.qml \
    content/layouts/en_GB/digits.qml \
    content/layouts/en_GB/numbers.qml
contains(CONFIG, lang-en.*) {
    LAYOUT_FILES += \
        content/layouts/en_GB/main.qml \
        content/layouts/en_GB/symbols.qml
t9write-alphabetic|lipi-toolkit: LAYOUT_FILES += \
        content/layouts/en_GB/handwriting.qml
}
contains(CONFIG, lang-ar.*) {
    LAYOUT_FILES += \
        content/layouts/ar_AR/digits.qml \
        content/layouts/ar_AR/main.qml \
        content/layouts/ar_AR/numbers.qml \
        content/layouts/ar_AR/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/ar_AR/handwriting.qml
}
contains(CONFIG, lang-bg.*) {
    LAYOUT_FILES += \
        content/layouts/bg_BG/main.qml \
        content/layouts/bg_BG/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/bg_BG/handwriting.qml
}
contains(CONFIG, lang-cs.*) {
    LAYOUT_FILES += \
        content/layouts/cs_CZ/main.qml \
        content/layouts/cs_CZ/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/cs_CZ/handwriting.qml
}
contains(CONFIG, lang-da.*) {
    LAYOUT_FILES += \
        content/layouts/da_DK/main.qml \
        content/layouts/da_DK/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/da_DK/handwriting.qml
}
contains(CONFIG, lang-de.*) {
    LAYOUT_FILES += \
        content/layouts/de_DE/main.qml \
        content/layouts/de_DE/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/de_DE/handwriting.qml
}
contains(CONFIG, lang-el.*) {
    LAYOUT_FILES += \
        content/layouts/el_GR/main.qml \
        content/layouts/el_GR/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/el_GR/handwriting.qml
}
contains(CONFIG, lang-es.*) {
    LAYOUT_FILES += \
        content/layouts/es_ES/main.qml \
        content/layouts/es_ES/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/es_ES/handwriting.qml
}
contains(CONFIG, lang-et.*) {
    LAYOUT_FILES += \
        content/layouts/et_EE/main.qml \
        content/layouts/et_EE/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/et_EE/handwriting.qml
}
contains(CONFIG, lang-fa.*) {
    LAYOUT_FILES += \
        content/layouts/fa_FA/digits.qml \
        content/layouts/fa_FA/main.qml \
        content/layouts/fa_FA/numbers.qml \
        content/layouts/fa_FA/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/fa_FA/handwriting.qml
}
contains(CONFIG, lang-fi.*) {
    LAYOUT_FILES += \
        content/layouts/fi_FI/main.qml \
        content/layouts/fi_FI/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/fi_FI/handwriting.qml
}
contains(CONFIG, lang-fr.*) {
    LAYOUT_FILES += \
        content/layouts/fr_FR/main.qml \
        content/layouts/fr_FR/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/fr_FR/handwriting.qml
}
contains(CONFIG, lang-he.*) {
    LAYOUT_FILES += \
        content/layouts/he_IL/main.qml \
        content/layouts/he_IL/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/he_IL/handwriting.qml
}
contains(CONFIG, lang-hi.*) {
    LAYOUT_FILES += \
        content/layouts/hi_IN/main.qml \
        content/layouts/hi_IN/symbols.qml
}
contains(CONFIG, lang-hr.*) {
    LAYOUT_FILES += \
        content/layouts/hr_HR/main.qml \
        content/layouts/hr_HR/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/hr_HR/handwriting.qml
}
contains(CONFIG, lang-hu.*) {
    LAYOUT_FILES += \
        content/layouts/hu_HU/main.qml \
        content/layouts/hu_HU/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/hu_HU/handwriting.qml
}
contains(CONFIG, lang-it.*) {
    LAYOUT_FILES += \
        content/layouts/it_IT/main.qml \
        content/layouts/it_IT/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/it_IT/handwriting.qml
}
contains(CONFIG, lang-ja.*) {
    LAYOUT_FILES += \
        content/layouts/ja_JP/main.qml \
        content/layouts/ja_JP/symbols.qml
t9write-cjk: LAYOUT_FILES += \
        content/layouts/ja_JP/handwriting.qml
}
contains(CONFIG, lang-ko.*) {
    LAYOUT_FILES += \
        content/layouts/ko_KR/main.qml \
        content/layouts/ko_KR/symbols.qml
t9write-cjk: LAYOUT_FILES += \
        content/layouts/ko_KR/handwriting.qml
}
contains(CONFIG, lang-nb.*) {
    LAYOUT_FILES += \
        content/layouts/nb_NO/main.qml \
        content/layouts/nb_NO/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/nb_NO/handwriting.qml
}
contains(CONFIG, lang-nl.*) {
    LAYOUT_FILES += \
        content/layouts/nl_NL/main.qml \
        content/layouts/nl_NL/symbols.qml
t9write-alphabetic|lipi-toolkit: LAYOUT_FILES += \
        content/layouts/nl_NL/handwriting.qml
}
contains(CONFIG, lang-pl.*) {
    LAYOUT_FILES += \
        content/layouts/pl_PL/main.qml \
        content/layouts/pl_PL/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/pl_PL/handwriting.qml
}
contains(CONFIG, lang-pt.*) {
    LAYOUT_FILES += \
        content/layouts/pt_PT/main.qml \
        content/layouts/pt_PT/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/pt_PT/handwriting.qml
}
contains(CONFIG, lang-ro.*) {
    LAYOUT_FILES += \
        content/layouts/ro_RO/main.qml \
        content/layouts/ro_RO/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/ro_RO/handwriting.qml
}
contains(CONFIG, lang-ru.*) {
    LAYOUT_FILES += \
        content/layouts/ru_RU/main.qml \
        content/layouts/ru_RU/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/ru_RU/handwriting.qml
}
contains(CONFIG, lang-sr.*) {
    LAYOUT_FILES += \
        content/layouts/sr_SP/main.qml \
        content/layouts/sr_SP/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/sr_SP/handwriting.qml
}
contains(CONFIG, lang-sv.*) {
    LAYOUT_FILES += \
        content/layouts/sv_SE/main.qml \
        content/layouts/sv_SE/symbols.qml
t9write-alphabetic: LAYOUT_FILES += \
        content/layouts/sv_SE/handwriting.qml
}
contains(CONFIG, lang-zh(_CN)?) {
    LAYOUT_FILES += \
        content/layouts/zh_CN/main.qml \
        content/layouts/zh_CN/symbols.qml
t9write-cjk: LAYOUT_FILES += \
        content/layouts/zh_CN/handwriting.qml
}
contains(CONFIG, lang-zh(_TW)?) {
    LAYOUT_FILES += \
        content/layouts/zh_TW/main.qml \
        content/layouts/zh_TW/symbols.qml
t9write-cjk: LAYOUT_FILES += \
        content/layouts/zh_TW/handwriting.qml
}

retro-style {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"retro\\\"
} else {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"default\\\"
}

DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_LAYOUTS_DIR=\\\"qrc:/QtQuick/VirtualKeyboard/content/layouts\\\"

OTHER_FILES += \
    content/styles/default/*.qml \
    content/styles/retro/*.qml \
    content/*.qml \
    content/components/*.qml \
    qtvirtualkeyboard.json

!disable-desktop:isEmpty(CROSS_COMPILE):!android-embedded:!qnx {
    SOURCES += desktopinputpanel.cpp inputview.cpp
    HEADERS += desktopinputpanel.h inputview.h
    DEFINES += QT_VIRTUALKEYBOARD_DESKTOP
    !no-pkg-config:packagesExist(xcb) {
        PKGCONFIG += xcb xcb-xfixes
        DEFINES += QT_VIRTUALKEYBOARD_HAVE_XCB
    }
}
SOURCES += appinputpanel.cpp
HEADERS += appinputpanel.h

!disable-hunspell {
    exists(3rdparty/hunspell/src/hunspell/hunspell.h) {
        SOURCES += hunspellinputmethod.cpp hunspellinputmethod_p.cpp hunspellworker.cpp
        HEADERS += hunspellinputmethod.h hunspellinputmethod_p.h hunspellworker.h
        DEFINES += HAVE_HUNSPELL
        QMAKE_USE += hunspell
        exists(3rdparty/hunspell/data) {
            hunspell_data.files = 3rdparty/hunspell/data/*.dic 3rdparty/hunspell/data/*.aff
            hunspell_data.path = $$DATAPATH/hunspell
            INSTALLS += hunspell_data
            !prefix_build: COPIES += hunspell_data
        } else {
            error("Hunspell dictionaries are missing! Please copy .dic and .aff" \
                  "files to src/virtualkeyboard/3rdparty/hunspell/data directory.")
        }
    } else:!no-pkg-config:packagesExist(hunspell) {
        SOURCES += hunspellinputmethod.cpp hunspellinputmethod_p.cpp hunspellworker.cpp
        HEADERS += hunspellinputmethod.h hunspellinputmethod_p.h hunspellworker.h
        DEFINES += HAVE_HUNSPELL
        PKGCONFIG += hunspell
    } else {
        message("Hunspell not found! Spell correction will not be available.")
    }
}

pinyin {
    SOURCES += \
        pinyininputmethod.cpp \
        pinyindecoderservice.cpp
    HEADERS += \
        pinyininputmethod.h \
        pinyindecoderservice.h
    DEFINES += HAVE_PINYIN
    QMAKE_USE += pinyin
    pinyin_data.files = $$PWD/3rdparty/pinyin/data/dict_pinyin.dat
    pinyin_data.path = $$DATAPATH/pinyin
    INSTALLS += pinyin_data
    !prefix_build: COPIES += pinyin_data
}

tcime {
    SOURCES += \
        tcinputmethod.cpp
    HEADERS += \
        tcinputmethod.h
    DEFINES += HAVE_TCIME
    cangjie: DEFINES += HAVE_TCIME_CANGJIE
    zhuyin: DEFINES += HAVE_TCIME_ZHUYIN
    QMAKE_USE += tcime
    tcime_data.files = \
        $$PWD/3rdparty/tcime/data/qt/dict_phrases.dat
    cangjie: tcime_data.files += \
        $$PWD/3rdparty/tcime/data/qt/dict_cangjie.dat
    zhuyin: tcime_data.files += \
        $$PWD/3rdparty/tcime/data/qt/dict_zhuyin.dat
    tcime_data.path = $$DATAPATH/tcime
    INSTALLS += tcime_data
    !prefix_build: COPIES += tcime_data
}

hangul {
    SOURCES += \
        hangulinputmethod.cpp \
        hangul.cpp
    HEADERS += \
        hangulinputmethod.h \
        hangul.h
    DEFINES += HAVE_HANGUL
}

openwnn {
    SOURCES += openwnninputmethod.cpp
    HEADERS += openwnninputmethod.h
    DEFINES += HAVE_OPENWNN
    QMAKE_USE += openwnn
}

lipi-toolkit:t9write: \
    error("Conflicting configuration flags: lipi-toolkit and t9write." \
          "Please use either one, but not both at the same time.")

lipi-toolkit {
    CONFIG += exceptions
    SOURCES += \
        lipiinputmethod.cpp \
        lipisharedrecognizer.cpp \
        lipiworker.cpp
    HEADERS += \
        lipiinputmethod.h \
        lipisharedrecognizer.h \
        lipiworker.h
    DEFINES += HAVE_LIPI_TOOLKIT
    INCLUDEPATH += \
        3rdparty/lipi-toolkit/src/include \
        3rdparty/lipi-toolkit/src/util/lib
    LIBS += -L$$OUT_PWD/../../lib \
        -lshaperecommon$$qtPlatformTargetSuffix() \
        -lltkcommon$$qtPlatformTargetSuffix() \
        -lltkutil$$qtPlatformTargetSuffix()
    win32: LIBS += Advapi32.lib
    else: QMAKE_USE += libdl
    ltk_projects.files = $$PWD/3rdparty/lipi-toolkit/projects
    ltk_projects.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit
    INSTALLS += ltk_projects
    !prefix_build: COPIES += ltk_projects
}

t9write {
    include(3rdparty/t9write/t9write-build.pri)
    equals(T9WRITE_FOUND, 0): \
        error("T9Write SDK could not be found. For more information, see" \
              "the documentation in Building Qt Virtual Keyboard")
    SOURCES += \
        t9writeinputmethod.cpp \
        t9writeworker.cpp \
        t9writedictionary.cpp
    HEADERS += \
        t9writeinputmethod.h \
        t9writeworker.h \
        t9writedictionary.h \
        t9write.h
    DEFINES += HAVE_T9WRITE
    QMAKE_USE += t9write_db
    INCLUDEPATH += $$T9WRITE_INCLUDE_DIRS
    t9write-alphabetic {
        LIBS += $$T9WRITE_ALPHABETIC_LIBS
        DEFINES += HAVE_T9WRITE_ALPHABETIC
        !isEmpty(T9WRITE_ALPHABETIC_BINS) {
            t9write_alphabetic_bins.files = $$T9WRITE_ALPHABETIC_BINS
            t9write_alphabetic_bins.path = $$[QT_INSTALL_BINS]
            INSTALLS += t9write_alphabetic_bins
            !prefix_build: COPIES += t9write_alphabetic_bins
        }
    }
    t9write-cjk {
        LIBS += $$T9WRITE_CJK_LIBS
        DEFINES += HAVE_T9WRITE_CJK
        !isEmpty(T9WRITE_CJK_BINS) {
            t9write_cjk_bins.files = $$T9WRITE_CJK_BINS
            t9write_cjk_bins.path = $$[QT_INSTALL_BINS]
            INSTALLS += t9write_cjk_bins
            !prefix_build: COPIES += t9write_cjk_bins
        }
    }
    DEFINES += QT_VIRTUALKEYBOARD_DEBUG
}

record-trace-input {
    SOURCES += unipentrace.cpp
    HEADERS += unipentrace.h
    DEFINES += QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
}

arrow-key-navigation: DEFINES += QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION

include(generateresource.pri)

!disable-layouts {
    RESOURCES += $$generate_resource(layouts.qrc, $$LAYOUT_FILES, /QtQuick/VirtualKeyboard)
    DEFINES += HAVE_LAYOUTS
}

PLUGIN_TYPE = platforminputcontexts
PLUGIN_EXTENDS = -
PLUGIN_CLASS_NAME = QVirtualKeyboardPlugin
load(qt_plugin)
