TEMPLATE = lib
TARGET  = qtvkbplugin
android-no-sdk {
    TARGETPATH = /system/plugins/platforminputcontexts
    QMLPATH = /system/qml/QtVkb
} else:!isEmpty(CROSS_COMPILE) {
    TARGETPATH = /usr/local/Qt-$$[QT_VERSION]/plugins/platforminputcontexts
    QMLPATH = /usr/local/Qt-$$[QT_VERSION]/qml/QtVkb
} else {
    TARGETPATH = $$[QT_INSTALL_PLUGINS]/platforminputcontexts
    QMLPATH = $$[QT_INSTALL_QML]/QtVkb
}

target.path = $$TARGETPATH
INSTALLS += target

QT += quick gui gui-private

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
    abstractinputpanel.cpp

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
    vkbdebug.h

retro-style {
    RESOURCES += content/styles/retro/style.qrc
} else {
    RESOURCES += content/styles/default/style.qrc
}

OTHER_FILES += content/InputPanel.qml \
    content/qmldir \
    content/components/*.qml \
    content/layouts/*.qml \
    content/styles/default/*.qml \
    content/styles/retro/*.qml

OTHER += qtvkb.json

!disable-xcb:isEmpty(CROSS_COMPILE):packagesExist(xcb) {
    PKGCONFIG += xcb xcb-xfixes
    SOURCES += xcbinputpanel.cpp inputview.cpp
    HEADERS += xcbinputpanel.h inputview.h
    DEFINES += HAVE_XCB
} else {
    SOURCES += appinputpanel.cpp
    HEADERS += appinputpanel.h
}

DEFINES += QT_VKB_IMPORT_PATH=\\\"$$QMLPATH\\\"
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
        depends += hunspell
        INCLUDEPATH += hunspell/src
        LIBS += -Lhunspell -lhunspell
        POST_TARGETDEPS += hunspell
        isEmpty(hunspell_search_paths) hunspell_search_paths=$$QMLPATH/hunspell
        DEFINES += QT_VKB_HUNSPELL_DATA_PATH=\\\"$$join(hunspell_search_paths, :)\\\"
        exists(hunspell/data) {
            hunspell_data.files = hunspell/data/*
            hunspell_data.path = $$QMLPATH/hunspell
            INSTALLS += hunspell_data
        } else {
            error(Hunspell dictionaries are missing! Please copy .dic and .aff files to qtvkb/hunspell/data directory.)
        }
    } else:isEmpty(CROSS_COMPILE):packagesExist(hunspell) {
        message(Found Hunspell package from pkg-config!)
        SOURCES += hunspellinputmethod.cpp hunspellworker.cpp
        HEADERS += hunspellinputmethod.h hunspellworker.h
        DEFINES += HAVE_HUNSPELL
        PKGCONFIG += hunspell
        isEmpty(hunspell_search_paths) hunspell_search_paths=/usr/share/hunspell /usr/share/myspell
        DEFINES += QT_VKB_HUNSPELL_DATA_PATH=\\\"$$join(hunspell_search_paths, :)\\\"
    } else {
        message(Hunspell not found! Spell correction will not be available.)
    }
}
