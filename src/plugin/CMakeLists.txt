# Generated from plugin.pro.

#####################################################################
## QVirtualKeyboardPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QVirtualKeyboardPlugin
    OUTPUT_NAME qtvirtualkeyboardplugin
    TYPE platforminputcontexts
    SOURCES
        extensionloader.cpp extensionloader.h
        plugin.cpp plugin.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboardPrivate
)

#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# OTHER_FILES = "qtvirtualkeyboard.json"
# PLUGIN_EXTENDS = "-"

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"
