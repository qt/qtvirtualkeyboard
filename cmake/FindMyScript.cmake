#[=======================================================================[.rst:
FindMyScript
------------

Searches for MyScript SDK.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``MyScript::VOIM``
  The MyScript VOIM library

Result Variables
^^^^^^^^^^^^^^^^

``MyScript_FOUND``
  TRUE if MyScript SDK is found.

Cache Variables
^^^^^^^^^^^^^^^

``MyScript_ROOT_DIR``
  It is a required variable and it indicates the location of the MyScript SDK.
  Please contact MyScript Support team to get detailed installation guide.

``MyScript_BINARIES``
  It is a list of MyScript Library Binaries which need to be installed.
  It includes required variables: MyScript_VOIM_BINARY, MyScript_Ink_BINARY,
  MyScript_Prediction_BINARY, MyScript_Text_BINARY and MyScript_Engine_BINARY.

#]=======================================================================]

set(MYSCRIPT_REQUIRED_VARS
    MyScript_ROOT_DIR
    MyScript_VOIM_INCLUDE_DIR
    MyScript_VOIM_BINARY
    MyScript_Ink_BINARY
    MyScript_Prediction_BINARY
    MyScript_Text_BINARY
    MyScript_Engine_BINARY
)

if(NOT MyScript_ROOT_DIR)
    if(INPUT_vkb_myscript_sdk)
        set(MyScript_ROOT_DIR ${INPUT_vkb_myscript_sdk} CACHE STRING "" FORCE)
    elseif(DEFINED ENV{MYSCRIPT_SDK_ROOT})
        set(MyScript_ROOT_DIR $ENV{MYSCRIPT_SDK_ROOT} CACHE STRING "" FORCE)
    elseif(EXISTS "${QtVirtualKeyboard_SOURCE_DIR}/src/plugins/myscript/sdk")
        set(MyScript_ROOT_DIR "${QtVirtualKeyboard_SOURCE_DIR}/src/plugins/myscript/sdk" CACHE STRING "" FORCE)
    endif()
endif()

if(MyScript_ROOT_DIR AND NOT MyScript_ARCH)
    if(INPUT_vkb_myscript_arch)
        if(WIN32)
            set(MyScript_ARCH "win-${INPUT_vkb_myscript_arch}")
        else()
            set(MyScript_ARCH "lin-${INPUT_vkb_myscript_arch}")
        endif()
    else()
        if(WIN32)
            if(CMAKE_SIZEOF_VOID_P MATCHES "8")
                set(MyScript_ARCH "win-x64")
            else()
                set(MyScript_ARCH "win-x86")
            endif()
        else()
            if (CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
                set(MyScript_ARCH "lin-arm64")
            elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
                set(MyScript_ARCH "lin-armv7hf")
            elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
                set(MyScript_ARCH "lin-x64")
            elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "i386" OR CMAKE_SYSTEM_PROCESSOR MATCHES "x86")
                set(MyScript_ARCH "lin-x86")
            endif()
        endif()
    endif()
endif()

find_path(MyScript_VOIM_INCLUDE_DIR
    NAMES "voim.h"
    PATHS "${MyScript_ROOT_DIR}/voim/api/c/include"
    NO_DEFAULT_PATH
)

if(NOT MyScript_VOIM_INCLUDE_DIR STREQUAL "MyScript_VOIM_INCLUDE_DIR-NOTFOUND")
    if(WIN32)
        find_file(MyScript_VOIM_BINARY
            NAMES "voim.dll"
            PATHS "${MyScript_ROOT_DIR}/voim/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )

        find_file(MyScript_Ink_BINARY
            NAMES "MyScriptInk.dll"
            PATHS "${MyScript_ROOT_DIR}/engine/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )

        find_file(MyScript_Prediction_BINARY
            NAMES "MyScriptPrediction.dll"
            PATHS "${MyScript_ROOT_DIR}/engine/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )

        find_file(MyScript_Text_BINARY
            NAMES "MyScriptText.dll"
            PATHS "${MyScript_ROOT_DIR}/engine/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )

        find_file(MyScript_Engine_BINARY
            NAMES "MyScriptEngine.dll"
            PATHS "${MyScript_ROOT_DIR}/engine/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )
    else()
        find_library(MyScript_VOIM_BINARY
            NAMES "voim"
            PATHS "${MyScript_ROOT_DIR}/voim/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )

        find_library(MyScript_Ink_BINARY
            NAMES "MyScriptInk"
            PATHS "${MyScript_ROOT_DIR}/engine/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )

        find_library(MyScript_Prediction_BINARY
            NAMES "MyScriptPrediction"
            PATHS "${MyScript_ROOT_DIR}/engine/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )

        find_library(MyScript_Text_BINARY
            NAMES "MyScriptText"
            PATHS "${MyScript_ROOT_DIR}/engine/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )

        find_library(MyScript_Engine_BINARY
            NAMES "MyScriptEngine"
            PATHS "${MyScript_ROOT_DIR}/engine/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )
    endif()

    set(MyScript_BINARIES
        ${MyScript_VOIM_BINARY}
        ${MyScript_Ink_BINARY}
        ${MyScript_Prediction_BINARY}
        ${MyScript_Text_BINARY}
        ${MyScript_Engine_BINARY}
        CACHE STRING "" FORCE
    )
endif()

if(NOT MyScript_VOIM_BINARY STREQUAL "MyScript_VOIM_BINARY-NOTFOUND" AND NOT TARGET MyScript::VOIM)
    add_library(MyScript::VOIM SHARED IMPORTED)

    if(WIN32)
        find_library(MyScript_VOIM_LIBRARY
            NAMES "voim"
            PATHS "${MyScript_ROOT_DIR}/voim/bin/${MyScript_ARCH}"
            NO_DEFAULT_PATH
        )
        list(APPEND MYSCRIPT_REQUIRED_VARS MyScript_VOIM_LIBRARY)

        set_target_properties(MyScript::VOIM PROPERTIES
            IMPORTED_LOCATION "${MyScript_VOIM_BINARY}"
            IMPORTED_IMPLIB "${MyScript_VOIM_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${MyScript_VOIM_INCLUDE_DIR}"
        )
    else()
        set_target_properties(MyScript::VOIM PROPERTIES
            IMPORTED_LOCATION "${MyScript_VOIM_BINARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${MyScript_VOIM_INCLUDE_DIR}"
        )
    endif()
endif()

#
# Common
#

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(MyScript
    REQUIRED_VARS ${MYSCRIPT_REQUIRED_VARS}
)

