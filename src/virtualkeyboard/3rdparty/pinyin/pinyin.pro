TEMPLATE = lib
QT -= core gui
TARGET = pinyin
VERSION = 1.0.0
CONFIG += dll
QMAKE_CXXFLAGS += -Wno-unused-parameter
#CONFIG += staticlib
#CONFIG += precompile_header warn_off
CONFIG -= qtquickcompiler # QTRD-3292

dll {
    android-no-sdk {
        target.path = /system/lib
    } else:!isEmpty(CROSS_COMPILE) {
        target.path = /usr/local/Qt-$$[QT_VERSION]/lib
    } else {
        target.path = $$[QT_INSTALL_LIBS]
    }
    INSTALLS += target
}

INCLUDEPATH += \
    include

SOURCES += \
    share/dictbuilder.cpp \
    share/dictlist.cpp \
    share/dicttrie.cpp \
    share/lpicache.cpp \
    share/matrixsearch.cpp \
    share/mystdlib.cpp \
    share/ngram.cpp \
    share/pinyinime.cpp \
    share/searchutility.cpp \
    share/spellingtable.cpp \
    share/spellingtrie.cpp \
    share/splparser.cpp \
    share/sync.cpp \
    share/userdict.cpp \
    share/utf16char.cpp \
    share/utf16reader.cpp

HEADERS += \
    include/atomdictbase.h \
    include/dictbuilder.h \
    include/dictdef.h \
    include/dictlist.h \
    include/dicttrie.h \
    include/lpicache.h \
    include/matrixsearch.h \
    include/mystdlib.h \
    include/ngram.h \
    include/pinyinime.h \
    include/searchutility.h \
    include/spellingtable.h \
    include/spellingtrie.h \
    include/splparser.h \
    include/sync.h \
    include/userdict.h \
    include/utf16char.h \
    include/utf16reader.h

OTHER_FILES +=\
    data/rawdict_utf16_65105_freq.txt \
    data/valid_utf16.txt
