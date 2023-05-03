# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from auto.pro.

if(NOT ANDROID) # QTBUG-102756
add_subdirectory(inputpanel)
endif()
add_subdirectory(inputpanelcontrols)
add_subdirectory(styles)
add_subdirectory(layoutfilesystem)
add_subdirectory(layoutresources)
# add_subdirectory(cmake) # special case
add_subdirectory(dictionarymanager)
add_subdirectory(shadowinput)
