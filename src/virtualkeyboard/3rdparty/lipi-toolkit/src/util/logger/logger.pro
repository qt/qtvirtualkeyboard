TEMPLATE = lib

CONFIG -= qt
CONFIG += plugin

DESTDIR = ../../lib

TARGET = logger

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../../include \
    ../lib \

HEADERS += \
    logger.h \

SOURCES += \
    logger.cpp \
    LTKLogger.cpp \

LIBS += -L$$OUT_PWD/../../lib -lltkutil

win32 {
    DEFINES += LOGGER_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = logger.def
}
