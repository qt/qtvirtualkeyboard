TEMPLATE = lib
TARGET  = qtvirtualkeyboardplugin
DATAPATH = $$[QT_INSTALL_DATA]/qtvirtualkeyboard

QMAKE_DOCS = $$PWD/doc/qtvirtualkeyboard.qdocconf
include(doc/doc.pri)

QT += quick gui gui-private core-private

CONFIG += plugin
win32 {
    CONFIG += no-pkg-config skip_target_version_ext
    VERSION = $$QT_VERSION
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
}

!contains(CONFIG, no-pkg-config): CONFIG += link_pkgconfig

SOURCES += platforminputcontext.cpp \
    inputcontext.cpp \
    abstractinputmethod.cpp \
    plaininputmethod.cpp \
    inputengine.cpp \
    shifthandler.cpp \
    plugin.cpp \
    inputmethod.cpp \
    selectionlistmodel.cpp \
    defaultinputmethod.cpp \
    abstractinputpanel.cpp \
    enterkeyaction.cpp \
    enterkeyactionattachedtype.cpp \
    settings.cpp \
    virtualkeyboardsettings.cpp \
    trace.cpp \

HEADERS += platforminputcontext.h \
    inputcontext.h \
    abstractinputmethod.h \
    plaininputmethod.h \
    inputengine.h \
    shifthandler.h \
    inputmethod.h \
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

RESOURCES += \
    content/styles/default/default_style.qrc \
    content/styles/retro/retro_style.qrc \
    content/content.qrc

pinyin: RESOURCES += content/layouts_pinyin.qrc
tcime: RESOURCES += content/layouts_traditional_chinese.qrc
hangul: RESOURCES += content/layouts_hangul.qrc
openwnn: RESOURCES += content/layouts_japanese.qrc
!tcime:!pinyin:!hangul:!openwnn: RESOURCES += content/layouts.qrc

retro-style {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"retro\\\"
} else {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"default\\\"
}

OTHER_FILES += \
    content/styles/default/*.qml \
    content/styles/retro/*.qml \
    content/*.qml \
    content/components/*.qml \
    qtvirtualkeyboard.json

disable-xcb {
    message(The disable-xcb option has been deprecated. Please use disable-desktop instead.)
    CONFIG += disable-desktop
}

!disable-desktop:isEmpty(CROSS_COMPILE):!android-no-sdk:!qnx {
    SOURCES += desktopinputpanel.cpp inputview.cpp
    HEADERS += desktopinputpanel.h inputview.h
    DEFINES += QT_VIRTUALKEYBOARD_DESKTOP
    !contains(CONFIG, no-pkg-config):packagesExist(xcb) {
        PKGCONFIG += xcb xcb-xfixes
        DEFINES += QT_VIRTUALKEYBOARD_HAVE_XCB
    }
}
SOURCES += appinputpanel.cpp
HEADERS += appinputpanel.h

qtquickcompiler: DEFINES += COMPILING_QML

build_pass {
    CONFIG(debug, debug|release) {
        SUBPATH = debug
        win32: TARGET_SUFFIX = d
    } else {
        SUBPATH = release
    }
} else {
    !debug_and_release:win32:CONFIG(debug, debug|release): TARGET_SUFFIX = d
}

!disable-hunspell {
    exists(3rdparty/hunspell/src/hunspell/hunspell.h) {
        message(Found Hunspell library!)
        SOURCES += hunspellinputmethod.cpp hunspellinputmethod_p.cpp hunspellworker.cpp
        HEADERS += hunspellinputmethod.h hunspellinputmethod_p.h hunspellworker.h
        DEFINES += HAVE_HUNSPELL
        INCLUDEPATH += 3rdparty/hunspell/src
        DEPENDPATH += 3rdparty/hunspell/src
        LIBS += -L$$OUT_PWD/3rdparty/hunspell/$$SUBPATH -lhunspell$$TARGET_SUFFIX
        exists(3rdparty/hunspell/data) {
            hunspell_data.files = 3rdparty/hunspell/data/*.dic 3rdparty/hunspell/data/*.aff
            hunspell_data.path = $$DATAPATH/hunspell
            INSTALLS += hunspell_data
        } else {
            error(Hunspell dictionaries are missing! Please copy .dic and .aff files to src/virtualkeyboard/3rdparty/hunspell/data directory.)
        }
    } else:!contains(CONFIG, no-pkg-config):packagesExist(hunspell) {
        message(Found Hunspell package from pkg-config!)
        SOURCES += hunspellinputmethod.cpp hunspellinputmethod_p.cpp hunspellworker.cpp
        HEADERS += hunspellinputmethod.h hunspellinputmethod_p.h hunspellworker.h
        DEFINES += HAVE_HUNSPELL
        PKGCONFIG += hunspell
    } else {
        message(Hunspell not found! Spell correction will not be available.)
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
    INCLUDEPATH += 3rdparty/pinyin/include
    DEPENDPATH += 3rdparty/pinyin/include
    LIBS += -L$$OUT_PWD/3rdparty/pinyin/$$SUBPATH -lpinyin
    pinyin_data.files = $$PWD/3rdparty/pinyin/data/dict_pinyin.dat
    pinyin_data.path = $$DATAPATH/pinyin
    INSTALLS += pinyin_data
}

tcime {
    SOURCES += \
        tcinputmethod.cpp
    HEADERS += \
        tcinputmethod.h
    DEFINES += HAVE_TCIME
    INCLUDEPATH += 3rdparty/tcime
    DEPENDPATH += 3rdparty/tcime
    LIBS += -L$$OUT_PWD/3rdparty/tcime/$$SUBPATH -ltcime
    tcime_data.files = \
        $$PWD/3rdparty/tcime/data/qt/dict_cangjie.dat \
        $$PWD/3rdparty/tcime/data/qt/dict_phrases.dat
    tcime_data.path = $$DATAPATH/tcime
    INSTALLS += tcime_data
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
    INCLUDEPATH += 3rdparty/openwnn/wnnEngine/include
    DEPENDPATH += 3rdparty/openwnn/wnnEngine/include
    # OpenWNN engine
    LIBS += -L$$OUT_PWD/3rdparty/openwnn/$$SUBPATH -lopenwnn
}

lipi-toolkit:t9write: error("Conflicting configuration flags: lipi-toolkit and t9write. Please use either one, but not both at the same time.")

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
    LIBS += -L$$OUT_PWD/3rdparty/lipi-toolkit/src/lib/$$SUBPATH -lshaperecommon -lltkcommon -lltkutil
    win32: LIBS += Advapi32.lib
    else: LIBS += -ldl
    record-trace-input: DEFINES += QT_VIRTUALKEYBOARD_LIPI_RECORD_TRACE_INPUT
}

t9write {
    include(3rdparty/t9write/t9write-build.pri)
    SOURCES += \
        t9writeinputmethod.cpp \
        t9writeworker.cpp
    HEADERS += \
        t9writeinputmethod.h \
        t9writeworker.h
    DEFINES += HAVE_T9WRITE
    INCLUDEPATH += \
        3rdparty/t9write/$$T9WRITE_BUILD_DIR/api \
        3rdparty/t9write/$$T9WRITE_BUILD_DIR/public
    LIBS += -L$$OUT_PWD/3rdparty/t9write/$$SUBPATH -lt9write_db
    LIBS += $$T9WRITE_ALPHABETIC_OBJ
}

arrow-key-navigation: DEFINES += QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION

PLUGIN_TYPE = platforminputcontexts
load(qt_plugin)
