# Generated from l7.pro.

#####################################################################
## l7 Generic Library:
#####################################################################

qt_internal_add_cmake_library(l7
    MODULE
    INSTALL_DIRECTORY "${INSTALL_PLUGINSDIR}/lipi_toolkit" # special case
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/plugins/lipi_toolkit"
    SOURCES
        L7ShapeFeature.cpp L7ShapeFeature.h
        L7ShapeFeatureExtractor.cpp L7ShapeFeatureExtractor.h
        l7.cpp l7.h
    INCLUDE_DIRECTORIES
        ../../../../include
        ../../../../util/lib
        ../common
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(l7)

#### Keys ignored in scope 1:.:.:l7.pro:<TRUE>:
# LIPILIBS = "ltkcommon" "ltkutil" "featureextractorcommon"

## Scopes:
#####################################################################

qt_internal_extend_target(l7 CONDITION WIN32
    DEFINES
        L7_EXPORTS
    PUBLIC_LIBRARIES
        Advapi32.lib
)

qt_internal_extend_target(l7 CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)

qt_autogen_tools_initial_setup(l7)
