TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += plugin

DESTDIR = ../../../../lib

TARGET = substroke

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../../../../include \
    ../../../../util/lib \
    ../common \

HEADERS += \
    SubStroke.h \
    SubStrokeShapeFeature.h \
    SubStrokeShapeFeatureExtractor.h \

SOURCES += \
    SubStroke.cpp \
    SubStrokeShapeFeature.cpp \
    SubStrokeShapeFeatureExtractor.cpp \

LIBS += -L$$OUT_PWD/../../../../lib -lltkcommon -lltkutil -lfeatureextractorcommon

win32 {
    DEFINES += SUBSTROKE_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = SubStroke.def
}
