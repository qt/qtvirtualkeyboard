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

TARGET = nn$$TARGET_SUFFIX

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

LIBS += -L$$OUT_PWD/../../../lib/$$SUBPATH -lshaperecommon -lltkcommon -lltkutil -lfeatureextractorcommon

win32 {
    DEFINES += NN_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = NN.def
}
