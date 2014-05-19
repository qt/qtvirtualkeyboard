TEMPLATE = lib
TARGET  = qtvirtualkeyboardplugin
android-no-sdk {
    TARGETPATH = /system/plugins/platforminputcontexts
    QMLPATH = /system/qml/QtQuick/Enterprise/VirtualKeyboard
    DATAPATH = /system/qtvirtualkeyboard
} else:!isEmpty(CROSS_COMPILE) {
    TARGETPATH = /usr/local/Qt-$$[QT_VERSION]/plugins/platforminputcontexts
    QMLPATH = /usr/local/Qt-$$[QT_VERSION]/qml/QtQuick/Enterprise/VirtualKeyboard
    DATAPATH = /usr/local/Qt-$$[QT_VERSION]/qtvirtualkeyboard
} else {
    TARGETPATH = $$[QT_INSTALL_PLUGINS]/platforminputcontexts
    QMLPATH = $$[QT_INSTALL_QML]/QtQuick/Enterprise/VirtualKeyboard
    DATAPATH = $$[QT_INSTALL_DATA]/qtvirtualkeyboard
}

QMAKE_DOCS = $$PWD/doc/qtvirtualkeyboard.qdocconf
include(doc/doc.pri)

target.path = $$TARGETPATH
INSTALLS += target

QT += quick gui gui-private core-private

CONFIG += plugin
CONFIG += link_pkgconfig

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
    enterkeyactionattachedtype.cpp

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
    enterkeyactionattachedtype.h

retro-style {
    RESOURCES += content/styles/retro/style.qrc
} else {
    RESOURCES += content/styles/default/style.qrc
}

OTHER_FILES += content/InputPanel.qml \
    content/qmldir \
    content/components/*.qml \
    content/layouts \
    content/styles/default/*.qml \
    content/styles/retro/*.qml

OTHER += qtvirtualkeyboard.json

!disable-xcb:isEmpty(CROSS_COMPILE):packagesExist(xcb) {
    PKGCONFIG += xcb xcb-xfixes
    SOURCES += xcbinputpanel.cpp inputview.cpp
    HEADERS += xcbinputpanel.h inputview.h
    DEFINES += HAVE_XCB
} else {
    SOURCES += appinputpanel.cpp
    HEADERS += appinputpanel.h
}

DEFINES += QT_VIRTUALKEYBOARD_IMPORT_PATH=\\\"$$QMLPATH\\\"
qml.files = content/*.qml \
    content/qmldir \
    content/components \
    content/layouts
qml.path = $$QMLPATH
INSTALLS += qml

!disable-hunspell {
    exists(hunspell/src/hunspell/hunspell.h) {
        message(Found Hunspell library!)
        SOURCES += hunspellinputmethod.cpp hunspellworker.cpp
        HEADERS += hunspellinputmethod.h hunspellworker.h
        DEFINES += HAVE_HUNSPELL
        INCLUDEPATH += hunspell/src
        DEPENDPATH += hunspell/src
        LIBS += -L$$OUT_PWD/hunspell/ -lhunspell
        isEmpty(hunspell_search_paths) hunspell_search_paths=$$DATAPATH/hunspell
        DEFINES += QT_VIRTUALKEYBOARD_HUNSPELL_DATA_PATH=\\\"$$join(hunspell_search_paths, :)\\\"
        exists(hunspell/data) {
            hunspell_data.files = hunspell/data/*.dic hunspell/data/*.aff
            hunspell_data.path = $$DATAPATH/hunspell
            INSTALLS += hunspell_data
        } else {
            error(Hunspell dictionaries are missing! Please copy .dic and .aff files to src/virtualkeyboard/hunspell/data directory.)
        }
    } else:packagesExist(hunspell) {
        message(Found Hunspell package from pkg-config!)
        SOURCES += hunspellinputmethod.cpp hunspellworker.cpp
        HEADERS += hunspellinputmethod.h hunspellworker.h
        DEFINES += HAVE_HUNSPELL
        PKGCONFIG += hunspell
        isEmpty(hunspell_search_paths) hunspell_search_paths=/usr/share/hunspell /usr/share/myspell/dicts
        DEFINES += QT_VIRTUALKEYBOARD_HUNSPELL_DATA_PATH=\\\"$$join(hunspell_search_paths, :)\\\"
    } else {
        message(Hunspell not found! Spell correction will not be available.)
    }
}
