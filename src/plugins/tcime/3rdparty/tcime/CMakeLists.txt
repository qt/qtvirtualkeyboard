# Generated from tcime.pro.

#####################################################################
## BundledTcime Generic Library:
#####################################################################

qt_add_3rdparty_library(BundledTcime
    STATIC
    SOURCES
        cangjiedictionary.cpp cangjiedictionary.h
        cangjietable.cpp cangjietable.h
        phrasedictionary.cpp phrasedictionary.h
        worddictionary.cpp worddictionary.h
        zhuyindictionary.cpp zhuyindictionary.h
        zhuyintable.cpp zhuyintable.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    PUBLIC_DEFINES
        HAVE_TCIME
    PUBLIC_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PUBLIC_LIBRARIES
        Qt::Core
)

#### Keys ignored in scope 1:.:.:tcime.pro:<TRUE>:
# OTHER_FILES = "data/dict_cangjie.dat" "data/dict_phrases.dat"
