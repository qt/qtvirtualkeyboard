# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

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
