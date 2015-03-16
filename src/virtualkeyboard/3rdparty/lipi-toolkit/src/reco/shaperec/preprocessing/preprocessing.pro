TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += plugin

DESTDIR = ../../../lib

TARGET = preproc

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../../../include \
    ../../../util/lib \
    ../common \

HEADERS += \
    preprocessing.h \

SOURCES += \
    LTKPreprocessor.cpp \
    preprocessing.cpp \

LIBS += -L$$OUT_PWD/../../../lib -lshaperecommon -lltkcommon -lltkutil

win32 {
    DEFINES += PREPROCESSING_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = preprocessing.def
}
