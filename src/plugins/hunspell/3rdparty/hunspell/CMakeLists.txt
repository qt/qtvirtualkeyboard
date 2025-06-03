#####################################################################
## BundledHunspell Generic Library:
#####################################################################

qt_internal_add_3rdparty_library(BundledHunspell
    QMAKE_LIB_NAME hunspell
    STATIC
    SOURCES
        ${CMAKE_CURRENT_BINARY_DIR}/hunspell/config.h
        hunspell/src/hunspell/affentry.cxx hunspell/src/hunspell/affentry.hxx
        hunspell/src/hunspell/affixmgr.cxx hunspell/src/hunspell/affixmgr.hxx
        hunspell/src/hunspell/atypes.hxx
        hunspell/src/hunspell/baseaffix.hxx
        hunspell/src/hunspell/csutil.cxx hunspell/src/hunspell/csutil.hxx
        hunspell/src/hunspell/filemgr.cxx hunspell/src/hunspell/filemgr.hxx
        hunspell/src/hunspell/hashmgr.cxx hunspell/src/hunspell/hashmgr.hxx
        hunspell/src/hunspell/htypes.hxx
        hunspell/src/hunspell/hunspell.cxx hunspell/src/hunspell/hunspell.h hunspell/src/hunspell/hunspell.hxx
        hunspell/src/hunspell/hunvisapi.h
        hunspell/src/hunspell/hunzip.cxx hunspell/src/hunspell/hunzip.hxx
        hunspell/src/hunspell/langnum.hxx
        hunspell/src/hunspell/phonet.cxx hunspell/src/hunspell/phonet.hxx
        hunspell/src/hunspell/replist.cxx hunspell/src/hunspell/replist.hxx
        hunspell/src/hunspell/suggestmgr.cxx hunspell/src/hunspell/suggestmgr.hxx
        hunspell/src/hunspell/w_char.hxx
    PUBLIC_DEFINES
        HUNSPELL_STATIC
    PUBLIC_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hunspell/src>
)
qt_disable_warnings(BundledHunspell)

file(READ hunspell/ChangeLog HUNSPELL_VERSION LIMIT 10)
string(STRIP ${HUNSPELL_VERSION} HUNSPELL_VERSION)
configure_file(config.h.cmake.in hunspell/config.h)

qt_internal_extend_target(BundledHunspell CONDITION CMAKE_BUILD_TYPE STREQUAL Debug
    DEFINES
        HUNSPELL_WARNING_ON
)
