TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += warn_off
CONFIG += staticlib

DESTDIR = ../../../lib

TARGET = shaperecommon

INCLUDEPATH += \
    ../../../include \
    ../../../util/lib \
    ../featureextractor/common \

SOURCES += \
    LTKShapeRecoConfig.cpp \
    LTKShapeRecognizer.cpp \
    LTKShapeRecoResult.cpp \
    LTKShapeRecoUtil.cpp \
    LTKShapeSample.cpp
