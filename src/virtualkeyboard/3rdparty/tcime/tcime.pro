TEMPLATE = lib
QT -= gui
TARGET = tcime
CONFIG += staticlib

build_pass {
    CONFIG(debug, debug|release): SUBPATH = debug
    else: SUBPATH = release
} else {
    debug_and_release: CONFIG += build_all
}

DESTDIR = $$SUBPATH

SOURCES += \
    cangjiedictionary.cpp \
    cangjietable.cpp \
    phrasedictionary.cpp \
    worddictionary.cpp \
    zhuyindictionary.cpp \
    zhuyintable.cpp

HEADERS += \
    cangjiedictionary.h \
    cangjietable.h \
    phrasedictionary.h \
    worddictionary.h \
    zhuyindictionary.h \
    zhuyintable.h

OTHER_FILES += \
    data/dict_cangjie.dat \
    data/dict_phrases.dat
