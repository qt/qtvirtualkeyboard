#####################################################################
## qtquickvirtualkeyboardplugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtquickvirtualkeyboardplugin
    URI "QtQuick.VirtualKeyboard"
    VERSION "2.${PROJECT_VERSION_MINOR}"
    CLASS_NAME QtQuickVirtualKeyboardPlugin
    PLUGIN_TARGET qtquickvirtualkeyboardplugin
    NO_GENERATE_PLUGIN_SOURCE
    NO_PLUGIN_OPTIONAL
    NO_GENERATE_QMLTYPES
    INSTALL_SOURCE_QMLTYPES "plugins.qmltypes"
    DEPENDENCIES
        QtQuick/2.0
        QtQuick.Window/2.2
        QtQuick.Layouts/1.0
        Qt.labs.folderlistmodel/2.1
        QtQuick.VirtualKeyboard.Settings/2.2
        QtQuick.VirtualKeyboard.Styles/2.2
    SOURCES
        qtquickvirtualkeyboardplugin.cpp qtquickvirtualkeyboardplugin.h
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::VirtualKeyboardPrivate
)

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:import.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"
