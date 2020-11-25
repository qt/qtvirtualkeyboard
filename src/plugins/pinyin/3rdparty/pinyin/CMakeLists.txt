# Generated from pinyin.pro.

#####################################################################
## BundledPinyin Generic Library:
#####################################################################

# special case begin
# TODO: Prepare for removal, once Platform brings in Threads.
if(NOT TARGET Threads::Threads)
    find_package(Threads REQUIRED)
endif()
# special case end

qt_internal_add_3rdparty_library(BundledPinyin
    QMAKE_LIB_NAME pinyin
    STATIC
    SOURCES
        include/atomdictbase.h
        include/dictbuilder.h
        include/dictdef.h
        include/dictlist.h
        include/dicttrie.h
        include/lpicache.h
        include/matrixsearch.h
        include/mystdlib.h
        include/ngram.h
        include/pinyinime.h
        include/searchutility.h
        include/spellingtable.h
        include/spellingtrie.h
        include/splparser.h
        include/sync.h
        include/userdict.h
        include/utf16char.h
        include/utf16reader.h
        share/dictbuilder.cpp
        share/dictlist.cpp
        share/dicttrie.cpp
        share/lpicache.cpp
        share/matrixsearch.cpp
        share/mystdlib.cpp
        share/ngram.cpp
        share/pinyinime.cpp
        share/searchutility.cpp
        share/spellingtable.cpp
        share/spellingtrie.cpp
        share/splparser.cpp
        share/sync.cpp
        share/userdict.cpp
        share/utf16char.cpp
        share/utf16reader.cpp
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    PUBLIC_DEFINES
        HAVE_PINYIN
    PUBLIC_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PUBLIC_LIBRARIES
        Qt::Core
        Threads::Threads # special case
)
qt_disable_warnings(BundledPinyin)

#### Keys ignored in scope 1:.:.:pinyin.pro:<TRUE>:
# OTHER_FILES = "data/rawdict_utf16_65105_freq.txt" "data/valid_utf16.txt"
# VERSION = "1.0.0"

## Scopes:
#####################################################################
