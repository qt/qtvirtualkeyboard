# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

set(plugins_imports)
if(QT_FEATURE_cerence_sdk)
    add_subdirectory(cerence)
    list(APPEND plugins_imports QtQuick.VirtualKeyboard.Plugins.Cerence/auto)
endif()
if(QT_FEATURE_example_hwr)
    add_subdirectory(example)
    list(APPEND plugins_imports QtQuick.VirtualKeyboard.Plugins.Example/auto)
endif()
if(QT_FEATURE_hangul)
    add_subdirectory(hangul)
    list(APPEND plugins_imports QtQuick.VirtualKeyboard.Plugins.Hangul/auto)
endif()
if(QT_FEATURE_hunspell)
    add_subdirectory(hunspell)
    list(APPEND plugins_imports QtQuick.VirtualKeyboard.Plugins.Hunspell/auto)
endif()
if(QT_FEATURE_openwnn)
    add_subdirectory(openwnn)
    list(APPEND plugins_imports QtQuick.VirtualKeyboard.Plugins.OpenWNN/auto)
endif()
if(QT_FEATURE_pinyin AND NOT QT_FEATURE_cerence_xt9)
    add_subdirectory(pinyin)
    list(APPEND plugins_imports QtQuick.VirtualKeyboard.Plugins.Pinyin/auto)
endif()
if(QT_FEATURE_tcime)
    add_subdirectory(tcime)
    list(APPEND plugins_imports QtQuick.VirtualKeyboard.Plugins.TCIme/auto)
endif()
if(QT_FEATURE_myscript)
    add_subdirectory(myscript)
    list(APPEND plugins_imports QtQuick.VirtualKeyboard.Plugins.MyScript/auto)
endif()
if(QT_FEATURE_thai)
    add_subdirectory(thai)
    list(APPEND plugins_imports QtQuick.VirtualKeyboard.Plugins.Thai/auto)
endif()

qt_internal_add_qml_module(qtvkbpluginsplugin
    URI "QtQuick.VirtualKeyboard.Plugins"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbpluginsplugin
    IMPORTS
        ${plugins_imports}
)
