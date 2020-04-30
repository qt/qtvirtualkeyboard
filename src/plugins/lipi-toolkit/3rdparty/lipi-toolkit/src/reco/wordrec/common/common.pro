BASE_TARGET_NAME = wordreccommon
include(../../../lipilib.pri)

INCLUDEPATH += \
    ../../../util/lib \

SOURCES += \
    LTKRecognitionContext.cpp \
    LTKWordRecoConfig.cpp \
    LTKWordRecoResult.cpp
