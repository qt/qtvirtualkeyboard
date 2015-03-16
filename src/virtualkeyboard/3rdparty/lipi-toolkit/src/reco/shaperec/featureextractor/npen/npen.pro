TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += plugin

DESTDIR = ../../../../lib

TARGET = npen

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../../../../include \
    ../../../../util/lib \
    ../common \

HEADERS += \
    NPen.h \
    NPenShapeFeature.h \
    NPenShapeFeatureExtractor.h \

SOURCES += \
    NPen.cpp \
    NPenShapeFeature.cpp \
    NPenShapeFeatureExtractor.cpp \

LIBS += -L$$OUT_PWD/../../../../lib -lltkcommon -lltkutil -lfeatureextractorcommon

win32 {
    DEFINES += NPEN_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = NPen.def
}
