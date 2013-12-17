TEMPLATE = app
TARGET = virtualkeyboard
QT += qml quick
SOURCES += main.cpp
CONFIG += link_pkgconfig
android-no-sdk|!isEmpty(CROSS_COMPILE) {
    TARGETPATH = /data/user/qt/virtualkeyboard
} else {
    TARGETPATH = $$[QT_INSTALL_EXAMPLES]/virtualkeyboard
}
target.path = $$TARGETPATH
INSTALLS += target

RESOURCES += \
    demo.qrc

OTHER_FILES += \
    VirtualKeyboard.qml \
    VirtualKeyboard-b2qt.qml \
    content/ScrollBar.qml \
    content/TextArea.qml \
    content/TextBase.qml \
    content/TextField.qml \
    content/images/background.png

disable-xcb|android-no-sdk|!isEmpty(CROSS_COMPILE) {
    DEFINES += MAIN_QML=\\\"VirtualKeyboard-b2qt.qml\\\"
} else {
    DEFINES += MAIN_QML=\\\"VirtualKeyboard.qml\\\"
}
