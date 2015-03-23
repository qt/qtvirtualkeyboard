TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += warn_off
CONFIG += staticlib

DESTDIR = ../../../lib

TARGET = wordreccommon

INCLUDEPATH += \
    ../../../include \
    ../../../util/lib \

SOURCES += \
    LTKRecognitionContext.cpp \
    LTKWordRecoConfig.cpp \
    LTKWordRecoResult.cpp
