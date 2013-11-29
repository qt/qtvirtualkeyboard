TEMPLATE = app
TARGET = virtualkeyboard
QT += qml quick
SOURCES += main.cpp
CONFIG += link_pkgconfig

android-no-sdk {
    TARGETPATH = /data/user/qt/virtualkeyboard
} else {
    TARGETPATH = $$[QT_INSTALL_EXAMPLES]/virtualkeyboard
}
target.path = $$TARGETPATH
INSTALLS += target

OTHER_FILES += \
    VirtualKeyboard.qml \
    content/ScrollBar.qml \
    content/TextArea.qml \
    content/TextBase.qml \
    content/TextField.qml \
    content/images/background.png
disable-xcb|!packagesExist(xcb) {
    OTHER_FILES += VirtualKeyboard-b2qt.qml
}

qml.files = \
    VirtualKeyboard.qml \
    content
disable-xcb|!packagesExist(xcb) {
    qml.files += VirtualKeyboard-b2qt.qml
    DEFINES += MAIN_QML=\\\"VirtualKeyboard-b2qt.qml\\\"
} else {
    DEFINES += MAIN_QML=\\\"VirtualKeyboard.qml\\\"
}
qml.path = $$TARGETPATH
INSTALLS += qml
