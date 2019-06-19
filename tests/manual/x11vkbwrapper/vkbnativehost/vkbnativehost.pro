TARGET = x11vkbnativehost

QT -= gui
QT += dbus

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    common_defs.h \
    sendertodbus.h

SOURCES += \
        main.cpp \
        sendertodbus.cpp

DISTFILES += \
    install_host.sh \
    x11vkb.host.json

