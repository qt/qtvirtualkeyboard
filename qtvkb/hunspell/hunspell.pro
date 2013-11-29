TEMPLATE = lib
MOC_DIR = .moc
RCC_DIR = .rcc
OBJECTS_DIR = .obj
QT -= core gui
TARGET = hunspell
VERSION = 1.3.2
DEFINES += BUILDING_LIBHUNSPELL
CONFIG += dll
#CONFIG += staticlib
CONFIG += precompile_header warn_off
debug {
    DEFINES += HUNSPELL_WARNING_ON
}
dll {
    android-no-sdk {
        target.path = /system/lib
    } else {
        target.path = $$[QT_INSTALL_LIBS]
    }
    INSTALLS += target
}

INCLUDEPATH += \
    ./ \
    src/hunspell \
    src/parsers

SOURCES += \
    src/hunspell/affentry.cxx \
    src/hunspell/affixmgr.cxx \
    src/hunspell/csutil.cxx \
    src/hunspell/dictmgr.cxx \
    src/hunspell/filemgr.cxx \
    src/hunspell/hashmgr.cxx \
    src/hunspell/hunspell.cxx \
    src/hunspell/hunzip.cxx \
    src/hunspell/phonet.cxx \
    src/hunspell/replist.cxx \
    src/hunspell/suggestmgr.cxx \
    src/parsers/firstparser.cxx \
    src/parsers/htmlparser.cxx \
    src/parsers/latexparser.cxx \
    src/parsers/manparser.cxx \
    src/parsers/testparser.cxx \
    src/parsers/textparser.cxx

HEADERS += \
    config.h \
    src/hunspell/affentry.hxx \
    src/hunspell/affixmgr.hxx \
    src/hunspell/atypes.hxx \
    src/hunspell/baseaffix.hxx \
    src/hunspell/csutil.hxx \
    src/hunspell/dictmgr.hxx \
    src/hunspell/filemgr.hxx \
    src/hunspell/hashmgr.hxx \
    src/hunspell/htypes.hxx \
    src/hunspell/hunspell.hxx \
    src/hunspell/hunzip.hxx \
    src/hunspell/langnum.hxx \
    src/hunspell/phonet.hxx \
    src/hunspell/replist.hxx \
    src/hunspell/suggestmgr.hxx \
    src/hunspell/w_char.hxx \
    src/parsers/firstparser.hxx \
    src/parsers/htmlparser.hxx \
    src/parsers/latexparser.hxx \
    src/parsers/manparser.hxx \
    src/parsers/textparser.hxx

OTHER_FILES +=\
    src/hunspell/license.hunspell \
    src/hunspell/license.myspell \
    src/hunspell/utf_info.cxx
