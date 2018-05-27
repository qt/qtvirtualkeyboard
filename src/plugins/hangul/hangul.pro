TARGET = qtvirtualkeyboard_hangul
QT += qml virtualkeyboard

HEADERS += \
    hangul_p.h \
    hangulplugin.h \
    hangulinputmethod_p.h
SOURCES += \
    hangul.cpp \
    hangulplugin.cpp \
    hangulinputmethod.cpp
OTHER_FILES += \
    hangul.json

include(../../config.pri)

LAYOUT_FILES += \
    $$LAYOUTS_BASE/content/layouts/ko_KR/main.qml \
    $$LAYOUTS_BASE/content/layouts/ko_KR/symbols.qml

layouts.files = $$LAYOUT_FILES
layouts.base = $$LAYOUTS_BASE
layouts.prefix = $$LAYOUTS_PREFIX
RESOURCES += layouts

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Hangul (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
}

PLUGIN_TYPE = virtualkeyboard
PLUGIN_CLASS_NAME = HangulPlugin
load(qt_plugin)
