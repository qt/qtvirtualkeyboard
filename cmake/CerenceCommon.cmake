# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT CERENCE_SDK_ROOT)
    if(INPUT_vkb_cerence_sdk)
        set(CERENCE_SDK_ROOT ${INPUT_vkb_cerence_sdk})
    elseif(DEFINED ENV{CERENCE_SDK_ROOT})
        set(CERENCE_SDK_ROOT $ENV{CERENCE_SDK_ROOT})
    else(EXISTS "${QtVirtualKeyboard_SOURCE_DIR}/src/plugins/cerence/sdk")
        set(CERENCE_SDK_ROOT "${QtVirtualKeyboard_SOURCE_DIR}/src/plugins/cerence/sdk")
    endif()
endif()

if(WIN32)
    set(CERENCE_SDK_OS_DIR "win32")
else()
    set(CERENCE_SDK_OS_DIR "linux")
endif()

set(CERENCE_SDK_ARCH_DIR ${CMAKE_SYSTEM_PROCESSOR})

if(BUILD_SHARED_LIBS AND NOT FEATURE_vkb_cerence_static)
    set(CERENCE_SDK_LINK_DIR "shared")
else()
    set(CERENCE_SDK_LINK_DIR "static")
endif()
