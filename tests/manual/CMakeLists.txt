# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from manual.pro.

find_package(X11)
if(X11_FOUND)
    add_subdirectory(x11vkbwrapper)
    add_subdirectory(x11vkbtest)
else()
    message("Manual tests x11vkbwrapper and x11vkbtest are not built due to missing X11 lib.")
endif()
add_subdirectory(quickcontrols2)
add_subdirectory(startupperformance)
