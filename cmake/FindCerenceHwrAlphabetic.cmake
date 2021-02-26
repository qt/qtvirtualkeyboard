#[=======================================================================[.rst:
FindCerenceHwrAlphabetic
------------------------

Searches for Cerence Handwriting Alphabetic SDK.

::

  CERENCE_SDK_ROOT this parameter is required and it indicates the location
  of the Cerence SDK. The SDK must be unpacked using unpack.py found in
  `src/plugins/cerence/unpack.py`.

::

  CERENCE_HWR_ALPHABETIC_FOUND is set to TRUE if SDK is found.
#]=======================================================================]

include(CerenceCommon REQUIRED)

set(CERENCE_HWR_ALPHABETIC_REQUIRED_VARS CERENCE_HWR_ALPHABETIC_INCLUDE_DIRS)

#
# Find handwriting engine
#

find_path(CERENCE_HWR_ALPHABETIC_INCLUDE_DIRS
    NAMES "decuma_hwr.h"
    PATHS "${CERENCE_SDK_ROOT}/t9write/api"
)

if(NOT CERENCE_HWR_ALPHABETIC_INCLUDE_DIRS STREQUAL "CERENCE_HWR_ALPHABETIC_INCLUDE_DIRS-NOTFOUND")
    set(CERENCE_HWR_ALPHABETIC_FOUND ON CACHE BOOL "" FORCE)
    list(APPEND CERENCE_HWR_ALPHABETIC_REQUIRED_VARS
        CERENCE_HWR_DATAPATH
        CERENCE_HWR_ALPHABETIC_LIBRARIES
    )

    find_path(CERENCE_HWR_DATAPATH
        NAMES "hwrDB_le.bin"
        PATHS "${CERENCE_SDK_ROOT}/t9write/data"
    )

    find_library(CERENCE_HWR_ALPHABETIC_LIBRARIES
        NAMES "t9write-ucr"
        PATHS "${CERENCE_SDK_ROOT}/t9write/lib/${CERENCE_SDK_OS_DIR}/${CERENCE_SDK_ARCH_DIR}/${CERENCE_SDK_LINK_DIR}/alphabetic/"
    )

    if(NOT CERENCE_HWR_ALPHABETIC_LIBRARIES STREQUAL "CERENCE_HWR_ALPHABETIC_LIBRARIES-NOTFOUND")
        set(CERENCE_HWR_ALPHABETIC_FOUND ON CACHE BOOL "" FORCE)
    endif()

    if(${CERENCE_SDK_LINK_DIR} STREQUAL "shared")
        if(WIN32)
            find_file(CERENCE_HWR_ALPHABETIC_BINARIES
                NAMES "t9write-ucr.dll"
                PATHS "${CERENCE_SDK_ROOT}/t9write/lib/${CERENCE_SDK_OS_DIR}/${CERENCE_SDK_ARCH_DIR}/${CERENCE_SDK_LINK_DIR}/alphabetic/"
                NO_DEFAULT_PATH
            )
        else()
            set(CERENCE_HWR_ALPHABETIC_BINARIES ${CERENCE_HWR_CJK_LIBRARIES} CACHE STRING "" FORCE)
        endif()
        list(APPEND CERENCE_HWR_ALPHABETIC_REQUIRED_VARS CERENCE_HWR_ALPHABETIC_BINARIES)
    endif()
endif()

if(CERENCE_HWR_ALPHABETIC_FOUND AND NOT TARGET Cerence::HWR::Alphabetic)
    add_library(Cerence::HWR::Alphabetic UNKNOWN IMPORTED)
    set_target_properties(Cerence::HWR::Alphabetic PROPERTIES
        IMPORTED_LOCATION "${CERENCE_HWR_ALPHABETIC_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${CERENCE_HWR_ALPHABETIC_INCLUDE_DIRS}")
endif()

#
# Common
#

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CerenceHwrAlphabetic
    REQUIRED_VARS ${CERENCE_HWR_ALPHABETIC_REQUIRED_VARS}
)
