# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_qml_module(qtvkbbuiltinstylesplugin
    URI "QtQuick.VirtualKeyboard.Styles.Builtin"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2 1
    PLUGIN_TARGET qtvkbbuiltinstylesplugin
    CLASS_NAME "QtQuickVirtualKeyboardStylesBuiltinPlugin"
    NO_PLUGIN_OPTIONAL
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES
        qtquickvirtualkeyboardbstylesbuiltinplugin.cpp qtquickvirtualkeyboardbstylesbuiltinplugin.h
    NO_GENERATE_CPP_EXPORTS
)

# Resources:
set(virtualkeyboard_default_style_resource_files
    "default/images/backspace-fff.svg"
    "default/images/check-fff.svg"
    "default/images/enter-fff.svg"
    "default/images/globe-fff.svg"
    "default/images/handwriting-fff.svg"
    "default/images/hidekeyboard-fff.svg"
    "default/images/search-fff.svg"
    "default/images/selectionhandle-bottom.svg"
    "default/images/shift-80c342.svg"
    "default/images/shift-fff.svg"
    "default/images/shift-c5d6b6.svg"
    "default/images/textmode-fff.svg"
    "default/images/settings-fff.svg"
    "default/style.qml"
)

qt_internal_add_resource(qtvkbbuiltinstylesplugin "virtualkeyboard_default_style"
    PREFIX
        "/qt-project.org/imports/QtQuick/VirtualKeyboard/Styles/Builtin/default"
    BASE
        "default"
    FILES
        ${virtualkeyboard_default_style_resource_files}
)
set(virtualkeyboard_retro_style_resource_files
    "retro/images/backspace-c5a96f.svg"
    "retro/images/check-c5a96f.svg"
    "retro/images/enter-c5a96f.svg"
    "retro/images/globe-110b05.svg"
    "retro/images/globe-c5a96f.svg"
    "retro/images/globe-fff.svg"
    "retro/images/handwriting-110b05.svg"
    "retro/images/handwriting-c5a96f.svg"
    "retro/images/handwriting-fff.svg"
    "retro/images/hidekeyboard-110b05.svg"
    "retro/images/hidekeyboard-c5a96f.svg"
    "retro/images/hidekeyboard-fff.svg"
    "retro/images/key154px_black.png"
    "retro/images/key154px_black.svg"
    "retro/images/key154px_black_long.png"
    "retro/images/key154px_capslock.png"
    "retro/images/key154px_capslock_long.png"
    "retro/images/key154px_colorA.png"
    "retro/images/key154px_colorA.svg"
    "retro/images/key154px_colorA_long.png"
    "retro/images/key154px_colorB.png"
    "retro/images/key154px_shiftcase.png"
    "retro/images/key154px_shiftcase_long.png"
    "retro/images/key156px_black_long.png"
    "retro/images/key156px_black_medium_long.png"
    "retro/images/key156px_colorA.png"
    "retro/images/key156px_colorB.png"
    "retro/images/key160px_black.png"
    "retro/images/key160px_colorA.png"
    "retro/images/key160px_colorB.png"
    "retro/images/key_preview.png"
    "retro/images/search-c5a96f.svg"
    "retro/images/selectionhandle-bottom.svg"
    "retro/images/shift-c5a96f.svg"
    "retro/images/shift-cd8865.svg"
    "retro/images/shift-dc4f28.svg"
    "retro/images/textmode-110b05.svg"
    "retro/images/textmode-c5a96f.svg"
    "retro/images/textmode-fff.svg"
    "retro/images/triangle_black.png"
    "retro/images/triangle_highlight.png"
    "retro/style.qml"
)

qt_internal_add_resource(qtvkbbuiltinstylesplugin "virtualkeyboard_retro_style"
    PREFIX
        "/qt-project.org/imports/QtQuick/VirtualKeyboard/Styles/Builtin/retro"
    BASE
        "retro"
    FILES
        ${virtualkeyboard_retro_style_resource_files}
)
