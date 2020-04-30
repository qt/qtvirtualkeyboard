# Generated from boxfld.pro.

#####################################################################
## boxfld Generic Library:
#####################################################################

qt_add_cmake_library(boxfld
    MODULE
    INSTALL_DIRECTORY "${INSTALL_PLUGINSDIR}/lipi_toolkit" # special case
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/plugins/lipi_toolkit"
    SOURCES
        BoxFieldRecognizer.cpp BoxFieldRecognizer.h
        boxfld.cpp boxfld.h
    INCLUDE_DIRECTORIES
        ../../../include
        ../../../util/lib
        ../common
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(boxfld)

#### Keys ignored in scope 1:.:.:boxfld.pro:<TRUE>:
# LIPILIBS = "shaperecommon" "ltkcommon" "ltkutil" "wordreccommon"

## Scopes:
#####################################################################

qt_extend_target(boxfld CONDITION WIN32
    DEFINES
        BOXFLD_EXPORTS
    PUBLIC_LIBRARIES
        Advapi32.lib
)

qt_extend_target(boxfld CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)

qt_autogen_tools_initial_setup(boxfld)
