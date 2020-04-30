# Generated from common.pro.

#####################################################################
## featureextractorcommon Generic Library:
#####################################################################

qt_add_cmake_library(featureextractorcommon
    STATIC
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/lib"
    SOURCES
        LTKShapeFeatureExtractor.cpp
        LTKShapeFeatureExtractorFactory.cpp
    INCLUDE_DIRECTORIES
        ../../../../include
        ../../../../util/lib
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(featureextractorcommon)

## Scopes:
#####################################################################

qt_extend_target(featureextractorcommon CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)
