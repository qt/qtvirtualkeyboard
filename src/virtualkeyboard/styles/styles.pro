TARGET = qtvirtualkeyboardstylesplugin
TARGETPATH = QtQuick/VirtualKeyboard/Styles
QT += qml quick svg

CONFIG += no_cxx_module

SOURCES += \
    svgimageprovider.cpp \
    styles_plugin.cpp

HEADERS += \
    svgimageprovider.h \
    styles_plugin.h

RESOURCES += \
    styles.qrc

load(qml_plugin)
