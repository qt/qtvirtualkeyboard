TARGET = QtHunspellInputMethod
MODULE = hunspellinputmethod

CONFIG += internal_module
QT += virtualkeyboard-private

DEFINES += QHUNSPELLINPUTMETHOD_LIBRARY

SOURCES += \
    hunspellinputmethod.cpp \
    hunspellinputmethod_p.cpp \
    hunspellworker.cpp
HEADERS += \
    hunspellinputmethod_p.h \
    hunspellinputmethod_p_p.h \
    hunspellworker_p.h \
    qhunspellinputmethod_global.h

include(../../../config.pri)

hunspell-library: QMAKE_USE += hunspell
else:hunspell-package: PKGCONFIG += hunspell

load(qt_module)
