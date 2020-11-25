# Generated from layoutresources.pro.

#####################################################################
## tst_layoutresources Test:
#####################################################################

qt_internal_add_test(tst_layoutresources
    SOURCES
        ../shared/layouttesthelper.cpp ../shared/layouttesthelper.h
        tst_layoutresources.cpp
    DEFINES
        SRC_DIR=\\\"${CMAKE_CURRENT_SOURCE_DIR}\\\"
    INCLUDE_DIRECTORIES
        ../shared
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::Quick
)

# Resources:
set(resourceslayout_resource_files
    "layouts/en_GB/main.qml"
)

qt_internal_add_resource(tst_layoutresources "resourceslayout"
    PREFIX
        "/resource"
    BASE
        "data"
    FILES
        ${resourceslayout_resource_files}
)


## Scopes:
#####################################################################

qt_internal_extend_target(tst_layoutresources CONDITION static
    PUBLIC_LIBRARIES
        Qt::Svg
)

#### Keys ignored in scope 3:.:.:layoutresources.pro:static:
# QTPLUGIN = "qtvirtualkeyboardplugin"
