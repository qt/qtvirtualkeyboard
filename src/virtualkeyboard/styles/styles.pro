TEMPLATE = lib
TARGET = qtvirtualkeyboardstylesplugin
INSTALL_PATH = $$[QT_INSTALL_QML]/QtQuick/Enterprise/VirtualKeyboard/Styles
QT += qml quick
CONFIG += plugin

target.path = $$INSTALL_PATH
INSTALLS += target

qtquickcompiler {
    TARGETPATH = QtQuick/Enterprise/VirtualKeyboard/Styles
    DEFINES += COMPILING_QML
}

SOURCES += \
    styles_plugin.cpp

HEADERS += \
    styles_plugin.h

QML_FILES += \
    qmldir \
    KeyboardStyle.qml \
    KeyPanel.qml \
    KeyIcon.qml \
    SelectionListItem.qml

qtquickcompiler {
    # generate qrc file, this should work out-of-box with later releases of qtquickcompiler
    include(../generateresource.prf)
    RESOURCES += $$generate_resource(styles.qrc, $$QML_FILES)
}

OTHER_FILES += \
    plugins.qmltypes

qtquickcompiler {
    other.files = $$OTHER_FILES qmldir
} else {
    other.files = $$OTHER_FILES $$QML_FILES
}
other.path = $$INSTALL_PATH
INSTALLS += other
