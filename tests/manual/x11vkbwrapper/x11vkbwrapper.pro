TEMPLATE = app
TARGET = x11vkbwrapper

QT += qml quick dbus virtualkeyboard svg widgets
CONFIG += c++11

static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# Uncomment below line and re-build before running tests.
# Enables writing of the current selected language to a json file for the test application to pick up.
#DEFINES += QT_TESTING_RUN

##### Skip Debug prints if Release build
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += \
    handlelanguagechange.cpp \
    main.cpp \
    handlekeyevents.cpp \
    handleatspievents.cpp \
    handledbusforchrome.cpp \
    vkbhidetimer.cpp

HEADERS += \
    handlekeyevents.h \
    handleatspievents.h \
    handledbusforchrome.h \
    common_defs.h \
    handlelanguagechange.h \
    keysymmapsforfakeinput.h \
    vkbhidetimer.h \
    xcbkeyboard.h

RESOURCES += qml.qrc

INCLUDEPATH += /usr/include/X11
INCLUDEPATH += /usr/include/at-spi-2.0
INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include
INCLUDEPATH += /usr/include/glib-2.0
INCLUDEPATH += /usr/include/dbus-1.0
INCLUDEPATH += /usr/lib/x86_64-linux-gnu/dbus-1.0/include

LIBS += -lXtst -lX11 -latspi -lxdo
