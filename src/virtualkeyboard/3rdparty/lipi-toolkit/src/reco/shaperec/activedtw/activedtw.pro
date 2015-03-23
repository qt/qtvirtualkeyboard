TEMPLATE = lib

CONFIG -= qt
CONFIG += exceptions
CONFIG += warn_off
CONFIG += plugin

DESTDIR = ../../../lib

TARGET = activedtw

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

LIBS += -L$$OUT_PWD/../../../lib -lshaperecommon -lltkcommon -lltkutil -lfeatureextractorcommon

win32 {
    DEFINES += ACTIVEDTW_EXPORTS
    LIBS += Advapi32.lib
    #DEF_FILE = ActiveDTW.def
}
