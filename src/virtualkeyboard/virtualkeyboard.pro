TEMPLATE = lib
TARGET  = qtvirtualkeyboardplugin
INSTALL_PATH = $$[QT_INSTALL_PLUGINS]/platforminputcontexts
DATAPATH = $$[QT_INSTALL_DATA]/qtvirtualkeyboard

QMAKE_DOCS = $$PWD/doc/qtvirtualkeyboard.qdocconf
include(doc/doc.pri)

target.path = $$INSTALL_PATH
INSTALLS += target

QT += quick gui gui-private core-private

CONFIG += plugin
win32 {
    CONFIG += no-pkg-config skip_target_version_ext
    VERSION = $$QT_VERSION
}

!contains(CONFIG, no-pkg-config): CONFIG += link_pkgconfig

SOURCES += platforminputcontext.cpp \
    declarativeinputcontext.cpp \
    abstractinputmethod.cpp \
    plaininputmethod.cpp \
    declarativeinputengine.cpp \
    declarativeshifthandler.cpp \
    plugin.cpp \
    declarativeinputmethod.cpp \
    declarativeselectionlistmodel.cpp \
    defaultinputmethod.cpp \
    abstractinputpanel.cpp \
    enterkeyaction.cpp \
    enterkeyactionattachedtype.cpp \
    settings.cpp \
    declarativesettings.cpp

HEADERS += platforminputcontext.h \
    declarativeinputcontext.h \
    abstractinputmethod.h \
    plaininputmethod.h \
    declarativeinputengine.h \
    declarativeshifthandler.h \
    declarativeinputmethod.h \
    declarativeselectionlistmodel.h \
    defaultinputmethod.h \
    abstractinputpanel.h \
    virtualkeyboarddebug.h \
    enterkeyaction.h \
    enterkeyactionattachedtype.h \
    settings.h \
    declarativesettings.h \
    plugin.h

RESOURCES += \
    content/styles/default/default_style.qrc \
    content/styles/retro/retro_style.qrc \
    content/content.qrc

pinyin: RESOURCES += content/layouts_pinyin.qrc
hangul: RESOURCES += content/layouts_hangul.qrc
openwnn: RESOURCES += content/layouts_japanese.qrc
!pinyin:!hangul:!openwnn: RESOURCES += content/layouts.qrc

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

!disable-hunspell {
    exists(3rdparty/hunspell/src/hunspell/hunspell.h) {
        message(Found Hunspell library!)
        SOURCES += hunspellinputmethod.cpp hunspellworker.cpp
        HEADERS += hunspellinputmethod.h hunspellworker.h
        DEFINES += HAVE_HUNSPELL
        INCLUDEPATH += 3rdparty/hunspell/src
        DEPENDPATH += 3rdparty/hunspell/src
        win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/3rdparty/hunspell/release/ -lhunspell1
        else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/3rdparty/hunspell/debug/ -lhunspell1
        else: LIBS += -L$$OUT_PWD/3rdparty/hunspell/ -lhunspell
        exists(3rdparty/hunspell/data) {
            hunspell_data.files = 3rdparty/hunspell/data/*.dic 3rdparty/hunspell/data/*.aff
            hunspell_data.path = $$DATAPATH/hunspell
            INSTALLS += hunspell_data
        } else {
            error(Hunspell dictionaries are missing! Please copy .dic and .aff files to src/virtualkeyboard/3rdparty/hunspell/data directory.)
        }
    } else:!contains(CONFIG, no-pkg-config):packagesExist(hunspell) {
        message(Found Hunspell package from pkg-config!)
        SOURCES += hunspellinputmethod.cpp hunspellworker.cpp
        HEADERS += hunspellinputmethod.h hunspellworker.h
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
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/3rdparty/pinyin/release/ -lpinyin
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/3rdparty/pinyin/debug/ -lpinyin
    else: LIBS += -L$$OUT_PWD/3rdparty/pinyin/ -lpinyin
    pinyin_data.files = $$PWD/3rdparty/pinyin/data/dict_pinyin.dat
    pinyin_data.path = $$DATAPATH/pinyin
    INSTALLS += pinyin_data
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
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/3rdparty/openwnn/release/ -lopenwnn
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/3rdparty/openwnn/debug/ -lopenwnn
    else: LIBS += -L$$OUT_PWD/3rdparty/openwnn/ -lopenwnn
}

arrow-key-navigation: DEFINES += QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
