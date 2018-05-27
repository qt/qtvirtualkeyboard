TARGET = qtvirtualkeyboardplugin
QT += virtualkeyboard-private

SOURCES += \
    plugin.cpp \
    extensionloader.cpp

HEADERS += \
    plugin.h \
    extensionloader.h

OTHER_FILES += \
    qtvirtualkeyboard.json

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
}

PLUGIN_TYPE = platforminputcontexts
PLUGIN_EXTENDS = -
PLUGIN_CLASS_NAME = QVirtualKeyboardPlugin
load(qt_plugin)
