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

set(qml_dependencies
    QtQuick/auto
    QtQuick.Layouts/auto
    QtQuick.VirtualKeyboard.Settings/auto
)

set(module_libraries
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::VirtualKeyboard
    Qt::VirtualKeyboardSettings
)

if(QT_FEATURE_vkb_sound_effects)
    list(APPEND qml_files MultiSoundEffect.qml)
    list(APPEND qml_dependencies QtMultimedia/auto)
    list(APPEND module_libraries Qt::Multimedia)
endif()

qt_internal_add_qml_module(qtvkbcomponentsplugin
    URI "QtQuick.VirtualKeyboard.Components"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2 1
    PLUGIN_TARGET qtvkbcomponentsplugin
    DEPENDENCIES
        ${qml_dependencies}
    QML_FILES
        ${qml_files}
    LIBRARIES
        ${module_libraries}
    NO_GENERATE_CPP_EXPORTS
)
