# Generated from plugin.pro.

#####################################################################
## QtVirtualKeyboardHunspellPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardHunspellPlugin
    OUTPUT_NAME qtvirtualkeyboard_hunspell
    TYPE virtualkeyboard
    SOURCES
        hunspellplugin.cpp hunspellplugin.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::HunspellInputMethodPrivate
        Qt::Qml
        Qt::VirtualKeyboard
)

#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# OTHER_FILES = "hunspell.json"

## Scopes:
#####################################################################

#### Keys ignored in scope 3:.:.:plugin.pro:EXISTS ../3rdparty/hunspell/data:
# INSTALLS = "hunspell_data"
# hunspell_data.files = "$$PWD/../3rdparty/hunspell/data/*.dic" "$$PWD/../3rdparty/hunspell/data/*.aff"
# hunspell_data.path = "$$VIRTUALKEYBOARD_INSTALL_DATA/hunspell"

#### Keys ignored in scope 4:.:.:plugin.pro:NOT prefix_build:
# COPIES = "hunspell_data"

#### Keys ignored in scope 6:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Hunspell (Qt $$QT_VERSION)"
