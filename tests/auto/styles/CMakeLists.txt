# Generated from styles.pro.

#####################################################################
## tst_styles Test:
#####################################################################

# Collect test data
file(GLOB_RECURSE test_data_glob
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/data/*)
list(APPEND test_data ${test_data_glob})

qt_internal_add_test(tst_styles
    QMLTEST
    SOURCES
        tst_styles.cpp
    DEFINES
        TESTDATA_DIR=\\\"${CMAKE_CURRENT_SOURCE_DIR}/data\\\"
    PUBLIC_LIBRARIES
        Qt::Gui
    TESTDATA ${test_data}
)

#### Keys ignored in scope 1:.:.:styles.pro:<TRUE>:
# DISTFILES = "data/tst_styles.qml" "data/QtQuick/VirtualKeyboard/Styles/test/style.qml"
# OTHER_FILES = "$$PWD/data/tst_styles.qml"
# TEMPLATE = "app"

## Scopes:
#####################################################################

qt_internal_extend_target(tst_styles CONDITION NOT QT_BUILD_SHARED_LIBS
    PUBLIC_LIBRARIES
        Qt::Svg
)

#### Keys ignored in scope 2:.:.:styles.pro:static:
# QTPLUGIN = "qtvirtualkeyboardplugin"
