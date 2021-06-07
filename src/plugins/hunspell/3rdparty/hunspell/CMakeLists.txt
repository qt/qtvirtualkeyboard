# Generated from hunspell.pro.

#####################################################################
## BundledHunspell Generic Library:
#####################################################################

qt_internal_add_3rdparty_library(BundledHunspell
    QMAKE_LIB_NAME hunspell
    STATIC
    SOURCES
        config.h
        src/hunspell/affentry.cxx src/hunspell/affentry.hxx
        src/hunspell/affixmgr.cxx src/hunspell/affixmgr.hxx
        src/hunspell/atypes.hxx
        src/hunspell/baseaffix.hxx
        src/hunspell/csutil.cxx src/hunspell/csutil.hxx
        src/hunspell/filemgr.cxx src/hunspell/filemgr.hxx
        src/hunspell/hashmgr.cxx src/hunspell/hashmgr.hxx
        src/hunspell/htypes.hxx
        src/hunspell/hunspell.cxx src/hunspell/hunspell.h src/hunspell/hunspell.hxx
        src/hunspell/hunvisapi.h
        src/hunspell/hunzip.cxx src/hunspell/hunzip.hxx
        src/hunspell/langnum.hxx
        src/hunspell/phonet.cxx src/hunspell/phonet.hxx
        src/hunspell/replist.cxx src/hunspell/replist.hxx
        src/hunspell/suggestmgr.cxx src/hunspell/suggestmgr.hxx
        src/hunspell/w_char.hxx
    PUBLIC_DEFINES
        HUNSPELL_STATIC
    PUBLIC_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
qt_disable_warnings(BundledHunspell)

# special case begin
file(READ ChangeLog HUNSPELL_VERSION LIMIT 10)
string(STRIP ${HUNSPELL_VERSION} HUNSPELL_VERSION)
configure_file(config.h.cmake.in config.h)
# special case end

#### Keys ignored in scope 1:.:.:hunspell.pro:<TRUE>:
# OTHER_FILES = "src/hunspell/license.hunspell" "src/hunspell/license.myspell" "src/hunspell/utf_info.cxx"
# config_file = "/* Version number of package */" "$${LITERAL_HASH}define VERSION "$$VERSION""

## Scopes:
#####################################################################

qt_internal_extend_target(BundledHunspell CONDITION CMAKE_BUILD_TYPE STREQUAL Debug
    DEFINES
        HUNSPELL_WARNING_ON
)
