#[=======================================================================[.rst:
FindCerenceXt9
--------------

Searches for Cerence XT9 SDK.

::

  CERENCE_SDK_ROOT this parameter is required and it indicates the location
  of the Cerence SDK. The SDK must be unpacked using unpack.py found in
  `src/plugins/cerence/unpack.py`.

::

  CERENCE_XT9_FOUND is set to TRUE if SDK is found.
#]=======================================================================]

include(CerenceCommon REQUIRED)

set(CERENCE_XT9_REQUIRED_VARS CERENCE_XT9_INCLUDE_DIRS)

#
# Find XT9 engine
#

find_path(CERENCE_XT9_INCLUDE_DIRS
    NAMES "et9api.h"
    PATHS "${CERENCE_SDK_ROOT}/xt9/api"
)

if(NOT CERENCE_XT9_INCLUDE_DIRS STREQUAL "CERENCE_XT9_INCLUDE_DIRS-NOTFOUND")
    set(CERENCE_XT9_FOUND ON CACHE BOOL "" FORCE)
    list(APPEND CERENCE_XT9_REQUIRED_VARS
        CERENCE_XT9_DATAPATH
        CERENCE_XT9_LIBRARIES
    )

    find_path(CERENCE_XT9_DATAPATH
        NAMES
            "ENubUN_xt9.ldb"
            "FRusUN_xt9_ALM3.ldb"
            "DEusUN_xt9_ALM3.ldb"
        PATHS "${CERENCE_SDK_ROOT}/xt9/data"
    )

    find_library(CERENCE_XT9_LIBRARIES
        NAMES "xt9-acktn"
        PATHS "${CERENCE_SDK_ROOT}/xt9/lib/${CERENCE_SDK_OS_DIR}/${CERENCE_SDK_ARCH_DIR}/${CERENCE_SDK_LINK_DIR}/"
        NO_DEFAULT_PATH
    )

    if(${CERENCE_SDK_LINK_DIR} STREQUAL "shared")
        if(WIN32)
            find_file(CERENCE_XT9_BINARIES
                NAMES "xt9-acktn.dll"
                PATHS "${CERENCE_SDK_ROOT}/xt9/lib/${CERENCE_SDK_OS_DIR}/${CERENCE_SDK_ARCH_DIR}/${CERENCE_SDK_LINK_DIR}/"
                NO_DEFAULT_PATH
            )
        else()
            set(CERENCE_XT9_BINARIES ${CERENCE_XT9_LIBRARIES} CACHE STRING "" FORCE)
        endif()
        list(APPEND CERENCE_XT9_REQUIRED_VARS CERENCE_XT9_BINARIES)
    endif()
endif()

if(CERENCE_XT9_FOUND AND NOT TARGET Cerence::XT9)
    add_library(Cerence::XT9 UNKNOWN IMPORTED)
    set_target_properties(Cerence::XT9 PROPERTIES
        IMPORTED_LOCATION "${CERENCE_XT9_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${CERENCE_XT9_INCLUDE_DIRS}")
endif()

#
# Common
#

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CerenceXt9
    REQUIRED_VARS ${CERENCE_XT9_REQUIRED_VARS}
)
