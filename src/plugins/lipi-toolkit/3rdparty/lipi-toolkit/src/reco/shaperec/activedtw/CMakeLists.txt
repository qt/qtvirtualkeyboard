# Generated from activedtw.pro.

#####################################################################
## activedtw Generic Library:
#####################################################################

qt_internal_add_cmake_library(activedtw
    MODULE
    INSTALL_DIRECTORY "${INSTALL_PLUGINSDIR}/lipi_toolkit" # special case
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/plugins/lipi_toolkit"
    SOURCES
        ActiveDTW.cpp ActiveDTW.h
        ActiveDTWAdapt.cpp ActiveDTWAdapt.h
        ActiveDTWClusterModel.cpp ActiveDTWClusterModel.h
        ActiveDTWShapeModel.cpp ActiveDTWShapeModel.h
        ActiveDTWShapeRecognizer.cpp ActiveDTWShapeRecognizer.h
    INCLUDE_DIRECTORIES
        ../../../include
        ../../../util/lib
        ../common
        ../featureextractor/common
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(activedtw)

#### Keys ignored in scope 1:.:.:activedtw.pro:<TRUE>:
# LIPILIBS = "shaperecommon" "ltkcommon" "ltkutil" "featureextractorcommon"

## Scopes:
#####################################################################

qt_internal_extend_target(activedtw CONDITION WIN32
    DEFINES
        ACTIVEDTW_EXPORTS
    PUBLIC_LIBRARIES
        Advapi32.lib
)

qt_internal_extend_target(activedtw CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)

qt_autogen_tools_initial_setup(activedtw)
