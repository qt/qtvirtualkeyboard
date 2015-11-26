TEMPLATE = lib

CONFIG -= qt static
CONFIG += exceptions
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

DESTDIR = ../../../lib/$$SUBPATH

TARGET = activedtw$$TARGET_SUFFIX

target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target

INCLUDEPATH += \
    ../../../include \
    ../../../util/lib \
    ../featureextractor/common \
    ../common \

HEADERS += \
    ActiveDTW.h \
    ActiveDTWAdapt.h \
    ActiveDTWClusterModel.h \
    ActiveDTWShapeModel.h \
    ActiveDTWShapeRecognizer.h \

SOURCES += \
    ActiveDTW.cpp \
    ActiveDTWShapeRecognizer.cpp\
    ActiveDTWClusterModel.cpp \
    ActiveDTWShapeModel.cpp \
    ActiveDTWAdapt.cpp \

LIBS += -L$$OUT_PWD/../../../lib/$$SUBPATH -lshaperecommon -lltkcommon -lltkutil -lfeatureextractorcommon

win32 {
    DEFINES += ACTIVEDTW_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = ActiveDTW.def
}
