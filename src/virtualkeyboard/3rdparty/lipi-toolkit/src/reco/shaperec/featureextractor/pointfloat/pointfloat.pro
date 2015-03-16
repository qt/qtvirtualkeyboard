TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += plugin

DESTDIR = ../../../../lib

TARGET = pointfloat

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../../../../include \
    ../../../../util/lib \
    ../common \

HEADERS += \
    PointFloat.h \
    PointFloatShapeFeature.h \
    PointFloatShapeFeatureExtractor.h \

SOURCES += \
    PointFloat.cpp \
    PointFloatShapeFeature.cpp \
    PointFloatShapeFeatureExtractor.cpp \

LIBS += -L$$OUT_PWD/../../../../lib -lltkcommon -lltkutil -lfeatureextractorcommon

win32 {
    DEFINES += POINTFLOAT_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = PointFloat.def
}
