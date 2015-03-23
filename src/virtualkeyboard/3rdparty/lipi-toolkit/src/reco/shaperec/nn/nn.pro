TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += warn_off
CONFIG += plugin

DESTDIR = ../../../lib

TARGET = nn

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../../../include \
    ../../../util/lib \
    ../featureextractor/common \
    ../common \

HEADERS += \
    NN.h \
    NNAdapt.h \
    NNShapeRecognizer.h \

SOURCES += \
    NN.cpp \
    NNAdapt.cpp \
    NNShapeRecognizer.cpp \

LIBS += -L$$OUT_PWD/../../../lib -lshaperecommon -lltkcommon -lltkutil -lfeatureextractorcommon

win32 {
    DEFINES += NN_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = NN.def
}
