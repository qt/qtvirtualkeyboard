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

DESTDIR = ../lib/$$SUBPATH

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

include(../include/headers.pri)
