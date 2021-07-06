#####################################################################
## qtquickvirtualkeyboardstylesplugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtquickvirtualkeyboardstylesplugin
    URI "QtQuick.VirtualKeyboard.Styles"
    VERSION "2.${PROJECT_VERSION_MINOR}"
    CLASS_NAME QtQuickVirtualKeyboardStylesPlugin
    PLUGIN_TARGET qtquickvirtualkeyboardstylesplugin
    NO_GENERATE_PLUGIN_SOURCE
    NO_PLUGIN_OPTIONAL
    NO_GENERATE_QMLTYPES
    INSTALL_SOURCE_QMLTYPES "plugins.qmltypes"
    DEPENDENCIES
        QtQuick/2.0
    SOURCES
        qtquickvirtualkeyboardstylesplugin.cpp qtquickvirtualkeyboardstylesplugin.h
        svgimageprovider.cpp svgimageprovider.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::Svg
        Qt::VirtualKeyboardPrivate
)

# Resources:
set(styles_resource_files
    "KeyIcon.qml"
    "KeyPanel.qml"
    "KeyboardStyle.qml"
    "SelectionListItem.qml"
    "TraceCanvas.qml"
    "TraceInputKeyPanel.qml"
    "TraceUtils.js"
)

qt_internal_add_resource(qtquickvirtualkeyboardstylesplugin "styles"
    PREFIX
        "/QtQuick/VirtualKeyboard/Styles/content"
    FILES
        ${styles_resource_files}
)

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:styles.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"
