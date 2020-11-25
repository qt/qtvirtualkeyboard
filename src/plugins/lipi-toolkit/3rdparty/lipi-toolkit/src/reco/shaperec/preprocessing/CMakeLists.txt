# Generated from preprocessing.pro.

#####################################################################
## preproc Generic Library:
#####################################################################

qt_internal_add_cmake_library(preproc
    MODULE
    INSTALL_DIRECTORY "${INSTALL_PLUGINSDIR}/lipi_toolkit" # special case
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/plugins/lipi_toolkit"
    SOURCES
        LTKPreprocessor.cpp
        preprocessing.cpp preprocessing.h
    INCLUDE_DIRECTORIES
        ../../../include
        ../../../util/lib
        ../common
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(preproc)

#### Keys ignored in scope 1:.:.:preprocessing.pro:<TRUE>:
# LIPILIBS = "shaperecommon" "ltkcommon" "ltkutil"

## Scopes:
#####################################################################

qt_internal_extend_target(preproc CONDITION WIN32
    DEFINES
        PREPROCESSING_EXPORTS
    PUBLIC_LIBRARIES
        Advapi32.lib
)

qt_internal_extend_target(preproc CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)

qt_autogen_tools_initial_setup(preproc)
