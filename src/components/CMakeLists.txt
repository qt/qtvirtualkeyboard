# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## VirtualKeyboard.Components Module:
#####################################################################

set(qml_files
    AlternativeKeys.qml
    BackspaceKey.qml
    BaseKey.qml
    ChangeLanguageKey.qml
    CharacterPreviewBubble.qml
    EnterKey.qml
    FillerKey.qml
    FlickKey.qml
    FunctionPopupList.qml
    HandwritingModeKey.qml
    HideKeyboardKey.qml
    InputModeKey.qml
    Key.qml
    Keyboard.qml
    KeyboardColumn.qml
    KeyboardLayout.qml
    KeyboardLayoutLoader.qml
    KeyboardRow.qml
    ModeKey.qml
    MultiSoundEffect.qml
    MultitapInputMethod.qml
    NumberKey.qml
    PopupList.qml
    SelectionControl.qml
    ShadowInputControl.qml
    ShiftKey.qml
    SpaceKey.qml
    SymbolModeKey.qml
    TraceInputArea.qml
    TraceInputKey.qml
    WordCandidatePopupList.qml
)

qt_internal_add_qml_module(qtvkbcomponentsplugin
    URI "QtQuick.VirtualKeyboard.Components"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2 1
    PLUGIN_TARGET qtvkbcomponentsplugin
    DEPENDENCIES
        QtQuick/auto
        QtQuick.Layouts/auto
        QtQuick.VirtualKeyboard.Settings/auto
    QML_FILES
        ${qml_files}
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::VirtualKeyboard
        Qt::VirtualKeyboardSettings
    NO_GENERATE_CPP_EXPORTS
)
