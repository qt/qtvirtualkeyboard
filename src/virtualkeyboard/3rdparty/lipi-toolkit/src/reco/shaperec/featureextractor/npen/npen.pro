TEMPLATE = lib

CONFIG -= qt
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

DESTDIR = ../../../../lib/$$SUBPATH

TARGET = npen$$TARGET_SUFFIX

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

LIBS += -L$$OUT_PWD/../../../../lib/$$SUBPATH -lltkcommon -lltkutil -lfeatureextractorcommon

win32 {
    DEFINES += NPEN_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = NPen.def
}
