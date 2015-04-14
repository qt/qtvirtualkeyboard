TEMPLATE = lib
TARGET = qtvirtualkeyboardstylesplugin
INSTALL_PATH = $$[QT_INSTALL_QML]/QtQuick/Enterprise/VirtualKeyboard/Styles
QT += qml quick svg
CONFIG += plugin

target.path = $$INSTALL_PATH
INSTALLS += target

SOURCES += \
    svgimageprovider.cpp \
    styles_plugin.cpp

HEADERS += \
    svgimageprovider.h \
    styles_plugin.h

OTHER_FILES += \
    *.qml

other.files = \
    plugins.qmltypes \
    qmldir
other.path = $$INSTALL_PATH
INSTALLS += other

RESOURCES += \
    styles.qrc
