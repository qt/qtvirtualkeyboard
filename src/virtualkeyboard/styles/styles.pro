TEMPLATE = lib
TARGET = qtvirtualkeyboardstylesplugin
INSTALL_PATH = $$[QT_INSTALL_QML]/QtQuick/Enterprise/VirtualKeyboard/Styles
QT += qml quick
CONFIG += plugin

target.path = $$INSTALL_PATH
INSTALLS += target

SOURCES += \
    styles_plugin.cpp

HEADERS += \
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

win32 {
    CONFIG += skip_target_version_ext
    VERSION = $$QT_VERSION
}
