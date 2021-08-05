# Generated from plugin.pro.

#####################################################################
## QtVirtualKeyboardHunspellPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardHunspellPlugin
    OUTPUT_NAME qtvirtualkeyboard_hunspell
    PLUGIN_TYPE virtualkeyboard
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

# special case begin
if(QT_FEATURE_3rdparty_hunspell)
    qt_copy_or_install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/hunspell/data/"
        DESTINATION "${VKB_INSTALL_DATA}/hunspell"
        FILES_MATCHING
        PATTERN "*.dic"
        PATTERN "*.aff"
    )
endif()
# special case end

#### Keys ignored in scope 3:.:.:plugin.pro:EXISTS ../3rdparty/hunspell/data:
# INSTALLS = "hunspell_data"
# hunspell_data.files = "$$PWD/../3rdparty/hunspell/data/*.dic" "$$PWD/../3rdparty/hunspell/data/*.aff"
# hunspell_data.path = "$$VIRTUALKEYBOARD_INSTALL_DATA/hunspell"

#### Keys ignored in scope 4:.:.:plugin.pro:NOT prefix_build:
# COPIES = "hunspell_data"

#### Keys ignored in scope 6:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Hunspell (Qt $$QT_VERSION)"
