# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QtQuickVirtualKeyboardHunspellPlugin Plugin:
#####################################################################

qt_internal_add_qml_module(HunspellInputMethod
    URI "QtQuick.VirtualKeyboard.Plugins.Hunspell"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbhunspellplugin
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick.VirtualKeyboard/auto
    SOURCES
        hunspellinputmethod.cpp hunspellinputmethod_p.cpp hunspellinputmethod_p.h
        hunspellinputmethod_p_p.h
        hunspellworker.cpp hunspellworker_p.h
        hunspellwordlist.cpp hunspellwordlist_p.h
        qhunspellinputmethod_global.h
    DEFINES
        QHUNSPELLINPUTMETHOD_LIBRARY
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::Core
        Qt::Gui
    PUBLIC_LIBRARIES
        Qt::VirtualKeyboardPrivate
    GENERATE_CPP_EXPORTS
    GENERATE_PRIVATE_CPP_EXPORTS
)

qt_internal_extend_target(HunspellInputMethod CONDITION QT_FEATURE_system_hunspell
    LIBRARIES
        Hunspell::Hunspell
)

qt_internal_extend_target(HunspellInputMethod CONDITION NOT QT_FEATURE_system_hunspell AND QT_FEATURE_3rdparty_hunspell
    LIBRARIES
        Qt::BundledHunspell
)

if(QT_FEATURE_3rdparty_hunspell)
    qt_copy_or_install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/hunspell/data/"
        DESTINATION "${VKB_INSTALL_DATA}/hunspell"
        FILES_MATCHING
        PATTERN "*.dic"
        PATTERN "*.aff"
    )
endif()
