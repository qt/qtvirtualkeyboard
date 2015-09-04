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

DESTDIR = ../../lib/$$SUBPATH

TARGET = ltkutil

INCLUDEPATH += \
    ../../include \

win32: DEFINES -= UNICODE

HEADERS += \
    LTKCheckSumGenerate.h \
    LTKConfigFileReader.h \
    LTKDynamicTimeWarping.h \
    LTKErrors.h \
    LTKHierarchicalClustering.h \
    LTKImageWriter.h \
    LTKInkFileReader.h \
    LTKInkFileWriter.h \
    LTKInkUtils.h \
    LTKLinuxUtil.h \
    LTKLoggerUtil.h \
    LTKStrEncoding.h \
    LTKStringUtil.h \
    LTKVersionCompatibilityCheck.h \
    LTKWinCEUtil.h \
    LTKWindowsUtil.h

SOURCES += \
    LTKCheckSumGenerate.cpp \
    LTKConfigFileReader.cpp \
    LTKInkFileReader.cpp \
    LTKInkFileWriter.cpp \
    LTKLoggerUtil.cpp \
    LTKInkUtils.cpp \
    LTKStrEncoding.cpp \
    LTKErrors.cpp \
    LTKStringUtil.cpp \
    LTKVersionCompatibilityCheck.cpp \
    LTKOSUtilFactory.cpp \
    LTKImageWriter.cpp
    
win32: SOURCES += LTKWindowsUtil.cpp
else: SOURCES += LTKLinuxUtil.cpp
