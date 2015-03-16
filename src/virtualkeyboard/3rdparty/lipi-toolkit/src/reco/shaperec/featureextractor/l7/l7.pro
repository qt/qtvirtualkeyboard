TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += plugin

DESTDIR = ../../../../lib

TARGET = l7

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../../../../include \
    ../../../../util/lib \
    ../common \

HEADERS += \
    l7.h \
    L7ShapeFeature.h \
    L7ShapeFeatureExtractor.h \

SOURCES += \
    l7.cpp \
    L7ShapeFeature.cpp \
    L7ShapeFeatureExtractor.cpp \

LIBS += -L$$OUT_PWD/../../../../lib -lltkcommon -lltkutil -lfeatureextractorcommon

win32 {
    DEFINES += L7_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = l7.def
}
