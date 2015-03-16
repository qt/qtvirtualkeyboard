TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += plugin

DESTDIR = ../../../lib

TARGET = neuralnet

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../../../include \
    ../../../util/lib \
    ../featureextractor/common \
    ../common \

HEADERS += \
    NeuralNet.h \
    NeuralNetShapeRecognizer.h \

SOURCES += \
    NeuralNet.cpp \
    NeuralNetShapeRecognizer.cpp \

LIBS += -L$$OUT_PWD/../../../lib -lshaperecommon -lltkcommon -lltkutil -lfeatureextractorcommon

win32 {
    DEFINES += NEURALNET_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = NeuralNet.def
}
