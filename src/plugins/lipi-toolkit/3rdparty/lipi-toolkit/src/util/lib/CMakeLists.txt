# Generated from lib.pro.

#####################################################################
## ltkutil Generic Library:
#####################################################################

qt_add_cmake_library(ltkutil
    STATIC
    EXCEPTIONS
    OUTPUT_DIRECTORY "${QT_BUILD_DIR}/lib"
    SOURCES
        LTKCheckSumGenerate.cpp LTKCheckSumGenerate.h
        LTKConfigFileReader.cpp LTKConfigFileReader.h
        LTKDynamicTimeWarping.h
        LTKErrors.cpp LTKErrors.h
        LTKHierarchicalClustering.h
        LTKImageWriter.cpp LTKImageWriter.h
        LTKInkFileReader.cpp LTKInkFileReader.h
        LTKInkFileWriter.cpp LTKInkFileWriter.h
        LTKInkUtils.cpp LTKInkUtils.h
        LTKLinuxUtil.h
        LTKLoggerUtil.cpp LTKLoggerUtil.h
        LTKOSUtilFactory.cpp
        LTKStrEncoding.cpp LTKStrEncoding.h
        LTKStringUtil.cpp LTKStringUtil.h
        LTKVersionCompatibilityCheck.cpp LTKVersionCompatibilityCheck.h
        LTKWinCEUtil.h
        LTKWindowsUtil.h
    INCLUDE_DIRECTORIES
        ../../include
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
)
qt_disable_warnings(ltkutil)

## Scopes:
#####################################################################

qt_extend_target(ltkutil CONDITION WIN32
    SOURCES
        LTKWindowsUtil.cpp
    DEFINES
        # -UNICODE # special case remove
)

qt_extend_target(ltkutil CONDITION UNIX
    SOURCES
        LTKLinuxUtil.cpp
)

qt_extend_target(ltkutil CONDITION NOT LIPILIBS_ISEMPTY
    PUBLIC_LIBRARIES
        # Remove: L/lib
)
