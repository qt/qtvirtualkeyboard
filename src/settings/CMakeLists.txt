#####################################################################
## qtquickvirtualkeyboardsettingsplugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtquickvirtualkeyboardsettingsplugin
    URI "QtQuick.VirtualKeyboard.Settings"
    VERSION "2.${PROJECT_VERSION_MINOR}"
    CLASS_NAME QtQuickVirtualKeyboardSettingsPlugin
    PLUGIN_TARGET qtquickvirtualkeyboardsettingsplugin
    NO_GENERATE_PLUGIN_SOURCE
    NO_PLUGIN_OPTIONAL
    NO_GENERATE_QMLTYPES
    INSTALL_SOURCE_QMLTYPES "plugins.qmltypes"
    DEPENDENCIES
        QtQuick/2.0
    SOURCES
        qtquickvirtualkeyboardsettingsplugin.cpp qtquickvirtualkeyboardsettingsplugin.h
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::VirtualKeyboardPrivate
)

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:settings.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"
