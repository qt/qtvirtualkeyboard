# Generated from dictionarymanager.pro.

#####################################################################
## tst_dictionarymanager Test:
#####################################################################

qt_internal_add_test(tst_dictionarymanager
    SOURCES
        tst_dictionarymanager.cpp
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::VirtualKeyboard
)

## Scopes:
#####################################################################

qt_internal_extend_target(tst_dictionarymanager CONDITION NOT QT_BUILD_SHARED_LIBS
    PUBLIC_LIBRARIES
        Qt::Svg
)

#### Keys ignored in scope 3:.:.:dictionarymanager.pro:static:
# QTPLUGIN = "qtvirtualkeyboardplugin"
