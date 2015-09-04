TEMPLATE = lib

CONFIG -= qt
CONFIG += warn_off
CONFIG += plugin

build_pass {
    CONFIG(debug, debug|release) {
        SUBPATH = debug
        win32: TARGET_SUFFIX = d
    } else {
        SUBPATH = release
    }
} else {
    debug_and_release: CONFIG += build_all
    else:win32:CONFIG(debug, debug|release): TARGET_SUFFIX = d
}

DESTDIR = ../../lib/$$SUBPATH

TARGET = logger$$TARGET_SUFFIX

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

LIBS += -L$$OUT_PWD/../../lib/$$SUBPATH -lltkutil

win32 {
    DEFINES += LOGGER_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = logger.def
}
