#[=======================================================================[.rst:
FindCerenceHwrCjk
-----------------

Searches for Cerence Handwriting CJK SDK.

::

  CERENCE_SDK_ROOT this parameter is required and it indicates the location
  of the Cerence SDK. The SDK must be unpacked using unpack.py found in
  `src/plugins/cerence/unpack.py`.

::

  CERENCE_HWR_CJK_FOUND is set to TRUE if SDK is found.
#]=======================================================================]

include(CerenceCommon REQUIRED)

set(CERENCE_HWR_CJK_REQUIRED_VARS CERENCE_HWR_CJK_INCLUDE_DIRS)

#
# Find handwriting engine for Chinese Japanese and Korean
#

find_path(CERENCE_HWR_CJK_INCLUDE_DIRS
    NAMES "decuma_hwr_cjk.h"
    PATHS "${CERENCE_SDK_ROOT}/t9write/api"
)

if(NOT CERENCE_HWR_CJK_INCLUDE_DIRS STREQUAL "CERENCE_HWR_CJK_INCLUDE_DIRS-NOTFOUND")
    set(CERENCE_HWR_CJK_FOUND ON CACHE BOOL "" FORCE)

    find_library(CERENCE_HWR_CJK_LIBRARIES
        NAMES "t9write-cjk"
        PATHS "${CERENCE_SDK_ROOT}/t9write/lib/${CERENCE_SDK_OS_DIR}/${CERENCE_SDK_ARCH_DIR}/${CERENCE_SDK_LINK_DIR}/cjk/"
        NO_DEFAULT_PATH
    )

    if(NOT CERENCE_HWR_CJK_LIBRARIES STREQUAL "CERENCE_HWR_CJK_LIBRARIES-NOTFOUND")
        set(CERENCE_HWR_CJK_FOUND ON CACHE BOOL "" FORCE)
        list(APPEND CERENCE_HWR_CJK_REQUIRED_VARS CERENCE_HWR_CJK_LIBRARIES)
    endif()

    if(${CERENCE_SDK_LINK_DIR} STREQUAL "shared")
        if(WIN32)
            find_file(CERENCE_HWR_CJK_BINARIES
                NAMES "t9write-cjk.dll"
                PATHS "${CERENCE_SDK_ROOT}/t9write/lib/${CERENCE_SDK_OS_DIR}/${CERENCE_SDK_ARCH_DIR}/${CERENCE_SDK_LINK_DIR}/cjk/"
                NO_DEFAULT_PATH
            )
        else()
            set(CERENCE_HWR_CJK_BINARIES ${CERENCE_HWR_CJK_LIBRARIES} CACHE STRING "" FORCE)
        endif()
        list(APPEND CERENCE_HWR_CJK_REQUIRED_VARS CERENCE_HWR_CJK_BINARIES)
    endif()
endif()

if(CERENCE_HWR_CJK_FOUND AND NOT TARGET Cerence::HWR::CJK)
    add_library(Cerence::HWR::CJK UNKNOWN IMPORTED)
    set_target_properties(Cerence::HWR::CJK PROPERTIES
        IMPORTED_LOCATION "${CERENCE_HWR_CJK_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${CERENCE_HWR_INCLUDE_DIRS}")
endif()

#
# Common
#

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CerenceHwrCjk
    REQUIRED_VARS ${CERENCE_HWR_CJK_REQUIRED_VARS}
)
