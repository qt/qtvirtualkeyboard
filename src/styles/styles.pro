TARGET = qtquickvirtualkeyboardstylesplugin
TARGETPATH = QtQuick/VirtualKeyboard/Styles
IMPORT_VERSION = 2.2
QT += qml quick svg virtualkeyboard-private

CONFIG += no_cxx_module

SOURCES += \
    svgimageprovider.cpp \
    qtquickvirtualkeyboardstylesplugin.cpp

HEADERS += \
    svgimageprovider.h \
    qtquickvirtualkeyboardstylesplugin.h

RESOURCES += \
    styles.qrc

OTHER_FILES += \
    plugins.qmltypes \
    qmldir

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard for Qt."
}

load(qml_plugin)
