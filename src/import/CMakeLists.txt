# Generated from import.pro.

#####################################################################
## qtquickvirtualkeyboardplugin Plugin:
#####################################################################

qt_internal_add_qml_module(qtquickvirtualkeyboardplugin
    URI "QtQuick.VirtualKeyboard"
    VERSION "2.${PROJECT_VERSION_MINOR}"
    CLASSNAME QtQuickVirtualKeyboardPlugin
    DEPENDENCIES
        QtQuick/2.0
        QtQuick.Window/2.2
        QtQuick.Layouts/1.0
        Qt.labs.folderlistmodel/2.1
        QtQuick.VirtualKeyboard.Settings/2.2
        QtQuick.VirtualKeyboard.Styles/2.2
    SKIP_TYPE_REGISTRATION
    SOURCES
        qtquickvirtualkeyboardplugin.cpp qtquickvirtualkeyboardplugin.h
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::VirtualKeyboardPrivate
)

#### Keys ignored in scope 1:.:.:import.pro:<TRUE>:
# IMPORT_VERSION = "2.$$QT_MINOR_VERSION"
# OTHER_FILES = "dependencies.json" "plugins.qmltypes" "qmldir"
# TARGETPATH = "QtQuick/VirtualKeyboard"

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:import.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"

#### Keys ignored in scope 3:.:.:import.pro:NOT CMAKE_CROSSCOMPILING AND ( build_pass OR NOT debug_and_release ):
# QMAKE_EXTRA_TARGETS = "qmltypes"
# qmltypes.commands = "$$QMPPLUGINDUMP_ENV" "$$QMLPLUGINDUMP" "-defaultplatform" "-nonrelocatable" "-dependencies" "$$PWD/dependencies.json" "QtQuick.VirtualKeyboard" "$$IMPORT_VERSION" ">" "$$PWD/plugins.qmltypes"

#### Keys ignored in scope 4:.:.:import.pro:NOT WIN32:
# QMPPLUGINDUMP_ENV = "QT_IM_MODULE=qtvirtualkeyboard"
