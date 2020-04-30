# Generated from neuralnet.pro.

#####################################################################
## neuralnet Generic Library:
#####################################################################

qt_add_cmake_library(neuralnet
    MODULE
    INSTALL_DIRECTORY "${INSTALL_PLUGINSDIR}/lipi_toolkit" # special case
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/plugins/lipi_toolkit"
    SOURCES
        NeuralNet.cpp NeuralNet.h
        NeuralNetShapeRecognizer.cpp NeuralNetShapeRecognizer.h
    INCLUDE_DIRECTORIES
        ../../../include
        ../../../util/lib
        ../common
        ../featureextractor/common
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(neuralnet)

#### Keys ignored in scope 1:.:.:neuralnet.pro:<TRUE>:
# LIPILIBS = "shaperecommon" "ltkcommon" "ltkutil" "featureextractorcommon"

## Scopes:
#####################################################################

qt_extend_target(neuralnet CONDITION WIN32
    DEFINES
        NEURALNET_EXPORTS
    PUBLIC_LIBRARIES
        Advapi32.lib
)

qt_extend_target(neuralnet CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)

qt_autogen_tools_initial_setup(neuralnet)
