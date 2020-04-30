# Generated from substroke.pro.

#####################################################################
## substroke Generic Library:
#####################################################################

qt_add_cmake_library(substroke
    MODULE
    INSTALL_DIRECTORY "${INSTALL_PLUGINSDIR}/lipi_toolkit" # special case
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/plugins/lipi_toolkit"
    SOURCES
        SubStroke.cpp SubStroke.h
        SubStrokeShapeFeature.cpp SubStrokeShapeFeature.h
        SubStrokeShapeFeatureExtractor.cpp SubStrokeShapeFeatureExtractor.h
    INCLUDE_DIRECTORIES
        ../../../../include
        ../../../../util/lib
        ../common
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(substroke)

#### Keys ignored in scope 1:.:.:substroke.pro:<TRUE>:
# LIPILIBS = "ltkcommon" "ltkutil" "featureextractorcommon"

## Scopes:
#####################################################################

qt_extend_target(substroke CONDITION WIN32
    DEFINES
        SUBSTROKE_EXPORTS
    PUBLIC_LIBRARIES
        Advapi32.lib
)

qt_extend_target(substroke CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)

qt_autogen_tools_initial_setup(substroke)
