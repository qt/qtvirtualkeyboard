TARGET = qtvirtualkeyboard_openwnn
QT += qml virtualkeyboard

HEADERS += \
    openwnnplugin.h \
    openwnninputmethod_p.h
SOURCES += \
    openwnnplugin.cpp \
    openwnninputmethod.cpp
OTHER_FILES += \
    openwnn.json

include(../../../config.pri)

LAYOUT_FILES += \
    $$LAYOUTS_BASE/content/layouts/ja_JP/dialpad.fallback \
    $$LAYOUTS_BASE/content/layouts/ja_JP/digits.fallback \
    $$LAYOUTS_BASE/content/layouts/ja_JP/main.qml \
    $$LAYOUTS_BASE/content/layouts/ja_JP/numbers.fallback \
    $$LAYOUTS_BASE/content/layouts/ja_JP/symbols.qml

OTHER_FILES += \
    $$LAYOUT_FILES

layouts.files = $$LAYOUT_FILES
layouts.base = $$LAYOUTS_BASE
layouts.prefix = $$LAYOUTS_PREFIX
RESOURCES += layouts

QMAKE_USE += openwnn

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard OpenWNN (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
}

PLUGIN_TYPE = virtualkeyboard
PLUGIN_CLASS_NAME = OpenWnnPlugin
load(qt_plugin)
