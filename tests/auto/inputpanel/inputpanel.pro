TEMPLATE = app
TARGET = tst_inputpanel

QT += testlib
CONFIG += qmltestcase console

SOURCES += $$PWD/tst_inputpanel.cpp

TESTDATA = $$PWD/data/*

OTHER_FILES += \
    $$PWD/data/inputpanel/inputpanel.qml \
    $$PWD/data/tst_inputpanel.qml \
