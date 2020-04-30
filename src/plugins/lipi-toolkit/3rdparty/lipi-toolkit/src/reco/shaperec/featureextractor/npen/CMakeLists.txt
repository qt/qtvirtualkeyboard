# Generated from npen.pro.

#####################################################################
## npen Generic Library:
#####################################################################

qt_add_cmake_library(npen
    MODULE
    INSTALL_DIRECTORY "${INSTALL_PLUGINSDIR}/lipi_toolkit" # special case
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/plugins/lipi_toolkit"
    SOURCES
        NPen.cpp NPen.h
        NPenShapeFeature.cpp NPenShapeFeature.h
        NPenShapeFeatureExtractor.cpp NPenShapeFeatureExtractor.h
    INCLUDE_DIRECTORIES
        ../../../../include
        ../../../../util/lib
        ../common
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(npen)

#### Keys ignored in scope 1:.:.:npen.pro:<TRUE>:
# LIPILIBS = "ltkcommon" "ltkutil" "featureextractorcommon"

## Scopes:
#####################################################################

qt_extend_target(npen CONDITION WIN32
    DEFINES
        NPEN_EXPORTS
    PUBLIC_LIBRARIES
        Advapi32.lib
)

qt_extend_target(npen CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)

qt_autogen_tools_initial_setup(npen)
