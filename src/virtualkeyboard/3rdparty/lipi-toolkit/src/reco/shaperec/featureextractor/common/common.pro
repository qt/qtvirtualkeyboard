TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += warn_off
CONFIG += staticlib

DESTDIR = ../../../../lib

TARGET = featureextractorcommon

INCLUDEPATH += \
    ../../../../include \
    ../../../../util/lib \

SOURCES += \
    LTKShapeFeatureExtractorFactory.cpp \
    LTKShapeFeatureExtractor.cpp
