TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += plugin

DESTDIR = ../../../lib

TARGET = boxfld

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../../../include \
    ../../../util/lib \
    ../common \

HEADERS += \
    BoxFieldRecognizer.h \
    boxfld.h \

SOURCES += \
    BoxFieldRecognizer.cpp \
    boxfld.cpp \

LIBS += -L$$OUT_PWD/../../../lib -lshaperecommon -lltkcommon -lltkutil -lwordreccommon

win32 {
    DEFINES += BOXFLD_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = boxfld.def
}
