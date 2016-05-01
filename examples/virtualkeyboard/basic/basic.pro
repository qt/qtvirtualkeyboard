TEMPLATE = app
TARGET = basic
QT += qml quick
SOURCES += main.cpp
CONFIG += link_pkgconfig
static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}
android-no-sdk|!isEmpty(CROSS_COMPILE) {
    TARGETPATH = /data/user/qt/virtualkeyboard/basic
} else {
    TARGETPATH = $$[QT_INSTALL_EXAMPLES]/virtualkeyboard/basic
}
target.path = $$TARGETPATH
INSTALLS += target

RESOURCES += \
    demo.qrc

OTHER_FILES += \
    Basic.qml \
    basic-b2qt.qml \
    content/AutoScroller.qml \
    content/HandwritingModeButton.qml \
    content/ScrollBar.qml \
    content/TextArea.qml \
    content/TextBase.qml \
    content/TextField.qml \

disable-xcb {
    message("The disable-xcb option has been deprecated. Please use disable-desktop instead.")
    CONFIG += disable-desktop
}

disable-desktop|android-no-sdk|!isEmpty(CROSS_COMPILE)|qnx {
    DEFINES += MAIN_QML=\\\"basic-b2qt.qml\\\"
} else {
    DEFINES += MAIN_QML=\\\"Basic.qml\\\"
}
