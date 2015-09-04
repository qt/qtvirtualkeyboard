TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += warn_off
CONFIG += staticlib

build_pass {
    CONFIG(debug, debug|release): SUBPATH = debug
    else: SUBPATH = release
} else {
    debug_and_release: CONFIG += build_all
}

DESTDIR = ../../../lib/$$SUBPATH

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
