TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += warn_off
CONFIG += staticlib

DESTDIR = ../lib

TARGET = ltkcommon

INCLUDEPATH += \
    ../include \
    ../util/lib

SOURCES += \
    LTKCaptureDevice.cpp \
    LTKChannel.cpp \
    LTKException.cpp \
    LTKScreenContext.cpp \
    LTKTrace.cpp \
    LTKTraceFormat.cpp \
    LTKTraceGroup.cpp
