CONFIG += testcase
TARGET = tst_dictionarymanager

macos:CONFIG -= app_bundle

QT += testlib qml quick virtualkeyboard

static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}

SOURCES += tst_dictionarymanager.cpp
