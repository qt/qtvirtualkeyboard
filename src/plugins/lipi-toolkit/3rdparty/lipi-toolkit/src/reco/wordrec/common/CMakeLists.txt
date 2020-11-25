# Generated from common.pro.

#####################################################################
## wordreccommon Generic Library:
#####################################################################

qt_internal_add_cmake_library(wordreccommon
    STATIC
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/lib"
    SOURCES
        LTKRecognitionContext.cpp
        LTKWordRecoConfig.cpp
        LTKWordRecoResult.cpp
    INCLUDE_DIRECTORIES
        ../../../include
        ../../../util/lib
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(wordreccommon)

## Scopes:
#####################################################################

qt_internal_extend_target(wordreccommon CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)
