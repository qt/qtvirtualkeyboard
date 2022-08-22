# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from dictionarymanager.pro.

#####################################################################
## tst_dictionarymanager Test:
#####################################################################

qt_internal_add_test(tst_dictionarymanager
    SOURCES
        tst_dictionarymanager.cpp
    LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::VirtualKeyboard
)

## Scopes:
#####################################################################

qt_internal_extend_target(tst_dictionarymanager CONDITION NOT QT_BUILD_SHARED_LIBS
    LIBRARIES
        Qt::Svg
)

#### Keys ignored in scope 3:.:.:dictionarymanager.pro:static:
# QTPLUGIN = "qtvirtualkeyboardplugin"
