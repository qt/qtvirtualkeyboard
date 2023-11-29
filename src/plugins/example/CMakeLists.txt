# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory(hwr)
list(APPEND example_imports QtQuick.VirtualKeyboard.Plugins.Example.HWR/auto)

qt_internal_add_qml_module(qtvkbexampleplugin
    URI "QtQuick.VirtualKeyboard.Plugins.Example"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtvkbexampleplugin
    IMPORTS
        ${example_imports}
    NO_GENERATE_CPP_EXPORTS
)
