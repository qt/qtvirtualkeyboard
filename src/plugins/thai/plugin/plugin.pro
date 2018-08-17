TARGET = qtvirtualkeyboard_thai
QT += qml virtualkeyboard

HEADERS += \
    thaiinputmethod_p.h \
    thaiplugin.h
SOURCES += \
    thaiinputmethod.cpp \
    thaiplugin.cpp
OTHER_FILES += \
    thai.json

include(../../../config.pri)

!disable-hunspell {
    QT += hunspellinputmethod-private
}

LAYOUT_FILES += \
    $$LAYOUTS_BASE/content/layouts/th_TH/dialpad.fallback \
    $$LAYOUTS_BASE/content/layouts/th_TH/digits.fallback \
    $$LAYOUTS_BASE/content/layouts/th_TH/main.qml \
    $$LAYOUTS_BASE/content/layouts/th_TH/numbers.fallback \
    $$LAYOUTS_BASE/content/layouts/th_TH/symbols.qml

layouts.files = $$LAYOUT_FILES
layouts.base = $$LAYOUTS_BASE
layouts.prefix = $$LAYOUTS_PREFIX
RESOURCES += layouts

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Thai (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
}

PLUGIN_TYPE = virtualkeyboard
PLUGIN_CLASS_NAME = ThaiPlugin
load(qt_plugin)
