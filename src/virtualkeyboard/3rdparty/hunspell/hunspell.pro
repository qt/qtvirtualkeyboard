TEMPLATE = lib
QT -= core gui
TARGET = hunspell
VERSION = 1.3.3
DEFINES += BUILDING_LIBHUNSPELL
CONFIG += dll
#CONFIG += staticlib
CONFIG += precompile_header warn_off
debug {
    DEFINES += HUNSPELL_WARNING_ON
}
CONFIG -= qtquickcompiler # QTRD-3292

dll {
    target.path = $$[QT_INSTALL_LIBS]
    INSTALLS += target
}

config_file = "/* Version number of package */" "$${LITERAL_HASH}define VERSION \"$$VERSION\""
write_file($$PWD/config.h, config_file)

INCLUDEPATH += \
    ./ \
    src/hunspell

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
    src/hunspell/suggestmgr.cxx

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
    src/hunspell/hunspell.h \
    src/hunspell/hunspell.hxx \
    src/hunspell/hunvisapi.h \
    src/hunspell/hunzip.hxx \
    src/hunspell/langnum.hxx \
    src/hunspell/phonet.hxx \
    src/hunspell/replist.hxx \
    src/hunspell/suggestmgr.hxx \
    src/hunspell/w_char.hxx

OTHER_FILES +=\
    src/hunspell/license.hunspell \
    src/hunspell/license.myspell \
    src/hunspell/utf_info.cxx
