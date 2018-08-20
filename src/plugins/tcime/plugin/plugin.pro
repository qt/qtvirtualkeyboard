TARGET = qtvirtualkeyboard_tcime
QT += qml virtualkeyboard

HEADERS += \
    tcinputmethod_p.h \
    tcimeplugin.h
SOURCES += \
    tcinputmethod.cpp \
    tcimeplugin.cpp
OTHER_FILES += \
    tcime.json

include(../../../config.pri)

LAYOUT_FILES += \
    $$LAYOUTS_BASE/content/layouts/zh_TW/dialpad.fallback \
    $$LAYOUTS_BASE/content/layouts/zh_TW/digits.fallback \
    $$LAYOUTS_BASE/content/layouts/zh_TW/main.qml \
    $$LAYOUTS_BASE/content/layouts/zh_TW/numbers.fallback \
    $$LAYOUTS_BASE/content/layouts/zh_TW/symbols.qml

layouts.files = $$LAYOUT_FILES
layouts.base = $$LAYOUTS_BASE
layouts.prefix = $$LAYOUTS_PREFIX
RESOURCES += layouts

cangjie: DEFINES += HAVE_TCIME_CANGJIE
zhuyin: DEFINES += HAVE_TCIME_ZHUYIN
QMAKE_USE += tcime
!no-bundle-tcime {
    TCIME_FILES += ../3rdparty/tcime/data/qt/dict_phrases.dat
    cangjie: TCIME_FILES += \
        ../3rdparty/tcime/data/qt/dict_cangjie.dat
    zhuyin: TCIME_FILES += \
        ../3rdparty/tcime/data/qt/dict_zhuyin.dat
    tcime.files = $$TCIME_FILES
    tcime.base = $$PWD/..
    tcime.prefix = /QtQuick/VirtualKeyboard
    RESOURCES += tcime
} else {
    tcime_data.files = \
        $$PWD/../3rdparty/tcime/data/qt/dict_phrases.dat
    cangjie: tcime_data.files += \
        $$PWD/../3rdparty/tcime/data/qt/dict_cangjie.dat
    zhuyin: tcime_data.files += \
        $$PWD/../3rdparty/tcime/data/qt/dict_zhuyin.dat
    tcime_data.path = $$VIRTUALKEYBOARD_INSTALL_DATA/tcime
    INSTALLS += tcime_data
    !prefix_build: COPIES += tcime_data
}

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard TCIME (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
}

PLUGIN_TYPE = virtualkeyboard
PLUGIN_CLASS_NAME = TCImePlugin
load(qt_plugin)
