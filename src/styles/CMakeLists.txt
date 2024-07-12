# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

set(styles_imports)
if(NOT QT_FEATURE_vkb_no_builtin_style)
    add_subdirectory(builtin)
    list(APPEND styles_imports QtQuick.VirtualKeyboard.Styles.Builtin/auto)
endif()

#####################################################################
## QtQuick.VirtualKeyboard.Styles
#####################################################################

qt_internal_add_qml_module(qtvkbstylesplugin
    URI "QtQuick.VirtualKeyboard.Styles"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2 1
    PLUGIN_TARGET qtvkbstylesplugin
    CLASS_NAME "QtQuickVirtualKeyboardStylesPlugin"
    # Note: The plugin source is defined manually because it uses an
    #       image provider. Once the image provider doesn't need an
    #       engine anymore, we can auto-generate the plugin.
    NO_GENERATE_PLUGIN_SOURCE
    NO_PLUGIN_OPTIONAL
    DEPENDENCIES
        QtQuick/auto
    IMPORTS
        ${styles_imports}
    SOURCES
        qtquickvirtualkeyboardstylesplugin.cpp qtquickvirtualkeyboardstylesplugin.h
        svgimageprovider.cpp svgimageprovider.h
    QML_FILES
        KeyboardStyle.qml
        KeyIcon.qml
        KeyPanel.qml
        SelectionListItem.qml
        TraceInputKeyPanel.qml
        TraceCanvas.qml
        TraceUtils.js
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::Svg
)
