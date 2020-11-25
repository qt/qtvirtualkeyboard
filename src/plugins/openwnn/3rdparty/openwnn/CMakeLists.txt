# Generated from openwnn.pro.

#####################################################################
## BundledOpenwnn Generic Library:
#####################################################################

qt_internal_add_3rdparty_library(BundledOpenwnn
    QMAKE_LIB_NAME openwnn
    STATIC
    SOURCES
        wnnDictionary/engine/ndapi.c
        wnnDictionary/engine/ndbdic.c
        wnnDictionary/engine/ndcommon.c
        wnnDictionary/engine/ndfdic.c
        wnnDictionary/engine/ndldic.c
        wnnDictionary/engine/ndrdic.c
        wnnDictionary/engine/neapi.c
        wnnDictionary/engine/necode.c
        wnnDictionary/engine/nj_str.c
        wnnDictionary/include/nj_dic.h
        wnnDictionary/include/nj_err.h
        wnnDictionary/include/nj_ext.h
        wnnDictionary/include/nj_lib.h
        wnnDictionary/include/njd.h
        wnnDictionary/include/njx_lib.h
        wnnEngine/WnnJpnDic.c
        wnnEngine/composingtext.cpp
        wnnEngine/include/composingtext.h
        wnnEngine/include/kanaconverter.h
        wnnEngine/include/letterconverter.h
        wnnEngine/include/openwnnclauseconverterjajp.h
        wnnEngine/include/openwnndictionary.h
        wnnEngine/include/openwnnenginejajp.h
        wnnEngine/include/romkan.h
        wnnEngine/include/romkanfullkatakana.h
        wnnEngine/include/romkanhalfkatakana.h
        wnnEngine/include/strsegment.h
        wnnEngine/include/wnnlookuptable.h
        wnnEngine/include/wnnword.h
        wnnEngine/kanaconverter.cpp
        wnnEngine/letterconverter.cpp
        wnnEngine/openwnnclauseconverterjajp.cpp
        wnnEngine/openwnndictionary.cpp
        wnnEngine/openwnnenginejajp.cpp
        wnnEngine/predef_table.h
        wnnEngine/romkan.cpp
        wnnEngine/romkanfullkatakana.cpp
        wnnEngine/romkanhalfkatakana.cpp
        wnnEngine/wnnlookuptable.cpp
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    PUBLIC_DEFINES
        HAVE_OPENWNN
    INCLUDE_DIRECTORIES
        wnnDictionary/include
    PUBLIC_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/wnnEngine/include>
    PUBLIC_LIBRARIES
        Qt::CorePrivate
)
qt_disable_warnings(BundledOpenwnn)

#### Keys ignored in scope 1:.:.:openwnn.pro:<TRUE>:
# VERSION = "1.3.6"
