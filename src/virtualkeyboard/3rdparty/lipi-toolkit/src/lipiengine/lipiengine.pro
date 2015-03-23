TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += warn_off
CONFIG += plugin

DESTDIR = ../lib

TARGET = lipiengine

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../include \
    ../util/lib

HEADERS += \
    lipiengine.h \
    LipiEngineModule.h

SOURCES += \
    lipiengine.cpp \
    LipiEngineModule.cpp

LIBS += -L$$OUT_PWD/../lib -lshaperecommon -lltkcommon -lltkutil -lwordreccommon

win32 {
    DEFINES += LIPIENGINE_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = lipiengine.def
}
