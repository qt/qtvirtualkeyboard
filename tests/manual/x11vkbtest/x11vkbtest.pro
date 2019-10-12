TARGET = x11vkbtest

QT += charts

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        filehelper.cpp \
        main.cpp \
        memorymonitor.cpp \
        mousesimulator.cpp \
        processhandler.cpp \
        startclose.cpp \
        testbase.cpp \
        testenglishletters.cpp \
        testlanguagechange.cpp \
        testreporter.cpp \
        testthread.cpp \
        windowhelper.cpp

HEADERS += \
    colors.h \
    filehelper.h \
    memorymonitor.h \
    mousesimulator.h \
    processhandler.h \
    startclose.h \
    testbase.h \
    testenglishletters.h \
    testlanguagechange.h \
    testreporter.h \
    testthread.h \
    windowhelper.h

LIBS += -lXtst -lX11 -lxdo
