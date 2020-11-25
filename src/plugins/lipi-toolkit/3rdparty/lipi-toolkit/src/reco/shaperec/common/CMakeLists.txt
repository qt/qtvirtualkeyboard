# Generated from common.pro.

#####################################################################
## shaperecommon Generic Library:
#####################################################################

qt_internal_add_cmake_library(shaperecommon
    STATIC
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/lib"
    SOURCES
        LTKShapeRecoConfig.cpp
        LTKShapeRecoResult.cpp
        LTKShapeRecoUtil.cpp
        LTKShapeRecognizer.cpp
        LTKShapeSample.cpp
    INCLUDE_DIRECTORIES
        ../../../include
        ../../../util/lib
        ../featureextractor/common
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(shaperecommon)

## Scopes:
#####################################################################

qt_internal_extend_target(shaperecommon CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)
