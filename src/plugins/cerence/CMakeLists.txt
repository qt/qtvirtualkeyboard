# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

set(cerence_imports)

add_subdirectory(cerencecommon)
if(QT_FEATURE_cerence_hwr)
    add_subdirectory(hwr)
    list(APPEND cerence_imports QtQuick.VirtualKeyboard.Plugins.Cerence.HWR/auto)
endif()
if(QT_FEATURE_cerence_xt9)
    add_subdirectory(xt9)
    list(APPEND cerence_imports QtQuick.VirtualKeyboard.Plugins.Cerence.XT9/auto)
endif()

qt_internal_add_qml_module(qtvkbcerenceplugin
    URI "QtQuick.VirtualKeyboard.Plugins.Cerence"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbcerenceplugin
    IMPORTS
        ${cerence_imports}
    NO_GENERATE_CPP_EXPORTS
)
