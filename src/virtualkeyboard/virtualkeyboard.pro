TEMPLATE = lib
TARGET  = qtvirtualkeyboardplugin
INSTALL_PATH = $$[QT_INSTALL_PLUGINS]/platforminputcontexts
QMLPATH = $$[QT_INSTALL_QML]/QtQuick/Enterprise/VirtualKeyboard
DATAPATH = $$[QT_INSTALL_DATA]/qtvirtualkeyboard

QMAKE_DOCS = $$PWD/doc/qtvirtualkeyboard.qdocconf
include(doc/doc.pri)

target.path = $$INSTALL_PATH
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
    content/styles/retro/retro_style.qrc
retro-style {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"retro\\\"
} else {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"default\\\"
}

OTHER_FILES += content/layouts \
    content/styles/default/*.qml \
    content/styles/retro/*.qml \
    generateresource.prf

OTHER += qtvirtualkeyboard.json

!disable-xcb:isEmpty(CROSS_COMPILE):!android-no-sdk {
    PKGCONFIG += xcb xcb-xfixes
    SOURCES += xcbinputpanel.cpp inputview.cpp
    HEADERS += xcbinputpanel.h inputview.h
    DEFINES += HAVE_XCB
} else {
    SOURCES += appinputpanel.cpp
    HEADERS += appinputpanel.h
}

qtquickcompiler {
    TARGETPATH = QtQuick/Enterprise/VirtualKeyboard
    DEFINES += COMPILING_QML
}

qml.files = \
    content/*.qml \
    content/components
qml.path = $$QMLPATH

pinyin: qml_layouts.files = \
    content/layouts/en_GB \
    content/layouts/zh_CN
else: qml_layouts.files = \
    content/layouts/ar_AR \
    content/layouts/fa_FA \
    content/layouts/da_DK \
    content/layouts/de_DE \
    content/layouts/en_GB \
    content/layouts/es_ES \
    content/layouts/hi_IN \
    content/layouts/fi_FI \
    content/layouts/fr_FR \
    content/layouts/it_IT \
    content/layouts/nb_NO \
    content/layouts/pl_PL \
    content/layouts/pt_PT \
    content/layouts/ru_RU \
    content/layouts/sv_SE
qml_layouts.path = $$QMLPATH/layouts

qtquickcompiler {
    QML_FILES += content/InputPanel.qml \
        content/qmldir \
        content/components/AlternativeKeys.qml \
        content/components/AutoScroller.qml \
        content/components/BackspaceKey.qml \
        content/components/BaseKey.qml \
        content/components/ChangeLanguageKey.qml \
        content/components/CharacterPreviewBubble.qml \
        content/components/EnterKey.qml \
        content/components/FillerKey.qml \
        content/components/HideKeyboardKey.qml \
        content/components/KeyboardColumn.qml \
        content/components/KeyboardLayoutLoader.qml \
        content/components/KeyboardLayout.qml \
        content/components/Keyboard.qml \
        content/components/KeyboardRow.qml \
        content/components/Key.qml \
        content/components/MultiSoundEffect.qml \
        content/components/MultitapInputMethod.qml \
        content/components/NumberKey.qml \
        content/components/ShiftKey.qml \
        content/components/SpaceKey.qml \
        content/components/SymbolModeKey.qml

    # generate qrc file, this should work out-of-box with later releases of qtquickcompiler
    include(generateresource.prf)
    resource_files = $$QML_FILES
    for (layoutdir, qml_layouts.files) {
        resource_files += $$files($$absolute_path($$layoutdir/*), $$_PRO_FILE_PWD_)
    }
    RESOURCES += $$generate_resource(content.qrc, $$resource_files)

    # workaround that qtquickcompiler removes *.qml file paths from qrc file (QTRD-3268)
    LAYOUTS_INDEX_FILE = $$OUT_PWD/qrclayoutsindex.h
    LAYOUTS_INDEX_CONTENT = "const QStringList layoutsDir = QStringList() " \
        "<< \"qrc:/content/layouts\""

    for (layoutdir, qml_layouts.files) {
        layoutfiles = $$files($$absolute_path($$layoutdir/*), $$_PRO_FILE_PWD_)
        for (qmlfile, layoutfiles) {
            relativepath = $$relative_path($$qmlfile, $$_PRO_FILE_PWD_)
            LAYOUTS_INDEX_CONTENT += "<< \"qrc:/$$relativepath\""
        }
    }

    LAYOUTS_INDEX_CONTENT += ";"
    write_file($$LAYOUTS_INDEX_FILE, LAYOUTS_INDEX_CONTENT)|error("Failed to write resource file!")

    qml.files = content/qmldir
    QMAKE_CLEAN += $$GENERATED_FILE $$LAYOUTS_INDEX_FILE
} else {
    qml.files += content/qmldir
    INSTALLS += qml_layouts
}
INSTALLS += qml

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
    } else:packagesExist(hunspell) {
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
    LIBS += -L$$OUT_PWD/3rdparty/pinyin/ -lpinyin
    pinyin_data.files = $$PWD/3rdparty/pinyin/data/dict_pinyin.dat
    pinyin_data.path = $$DATAPATH/pinyin
    INSTALLS += pinyin_data
}

arrow-key-navigation: DEFINES += QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
