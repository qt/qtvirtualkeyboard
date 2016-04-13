TEMPLATE = lib
TARGET = qtvirtualkeyboardstylesplugin
TARGETPATH = QtQuick/Enterprise/VirtualKeyboard/Styles
QT += qml quick svg
CONFIG += plugin

CONFIG += no_cxx_module

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
other.path = $$[QT_INSTALL_QML]/$$TARGETPATH
INSTALLS += other

RESOURCES += \
    styles.qrc

win32 {
    CONFIG += skip_target_version_ext
    VERSION = $$QT_VERSION
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
}

load(qml_plugin)
