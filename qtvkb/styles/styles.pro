TEMPLATE = lib
TARGET = qtvkbstylesplugin
android-no-sdk {
    TARGETPATH = /system/qml/QtVkb/Styles
} else:!isEmpty(CROSS_COMPILE) {
    TARGETPATH = /usr/local/Qt-$$[QT_VERSION]/qml/QtVkb/Styles
} else {
    TARGETPATH = $$[QT_INSTALL_QML]/QtVkb/Styles
}
QT += qml quick
CONFIG += qt plugin

target.path = $$TARGETPATH
INSTALLS += target

SOURCES += \
    styles_plugin.cpp

HEADERS += \
    styles_plugin.h

OTHER_FILES += \
    KeyboardStyle.qml \
    KeyPanel.qml \
    KeyIcon.qml \
    SelectionListItem.qml \
    qmldir \
    plugins.qmltypes

other.files = $$OTHER_FILES
other.path = $$TARGETPATH
INSTALLS += other
