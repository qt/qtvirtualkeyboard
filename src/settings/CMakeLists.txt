# Generated from settings.pro.

#####################################################################
## qtquickvirtualkeyboardsettingsplugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtquickvirtualkeyboardsettingsplugin
    URI "QtQuick.VirtualKeyboard.Settings"
    VERSION "2.${CMAKE_PROJECT_VERSION_MINOR}"
    CLASSNAME QtQuickVirtualKeyboardSettingsPlugin
    DEPENDENCIES
        QtQuick/2.0
    SKIP_TYPE_REGISTRATION
    SOURCES
        qtquickvirtualkeyboardsettingsplugin.cpp qtquickvirtualkeyboardsettingsplugin.h
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::VirtualKeyboardPrivate
)

#### Keys ignored in scope 1:.:.:settings.pro:<TRUE>:
# IMPORT_VERSION = "2.$$QT_MINOR_VERSION"
# OTHER_FILES = "plugins.qmltypes" "qmldir"
# TARGETPATH = "QtQuick/VirtualKeyboard/Settings"

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:settings.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"
