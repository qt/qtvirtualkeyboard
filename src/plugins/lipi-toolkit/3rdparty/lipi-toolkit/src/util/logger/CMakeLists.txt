# Generated from logger.pro.

#####################################################################
## logger Generic Library:
#####################################################################

qt_internal_add_cmake_library(logger
    MODULE
    INSTALL_DIRECTORY "${INSTALL_PLUGINSDIR}/lipi_toolkit" # special case
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/plugins/lipi_toolkit"
    SOURCES
        LTKLogger.cpp
        logger.cpp logger.h
    INCLUDE_DIRECTORIES
        ../../include
        ../lib
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(logger)

#### Keys ignored in scope 1:.:.:logger.pro:<TRUE>:
# LIPILIBS = "ltkutil"

## Scopes:
#####################################################################

qt_internal_extend_target(logger CONDITION WIN32
    DEFINES
        LOGGER_EXPORTS
    PUBLIC_LIBRARIES
        Advapi32.lib
)

qt_internal_extend_target(logger CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
        lkutil # special case
)

qt_autogen_tools_initial_setup(logger)
