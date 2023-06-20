# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QtQuick.VirtualKeyboard
#####################################################################

set(VKB_INSTALL_DATA "${QT_INSTALL_DIR}/qtvirtualkeyboard" CACHE STRING "" FORCE)

set(qml_files
    HandwritingInputPanel.qml
    InputPanel.qml
    EnterKey.qml ### Qt7: Remove, see QTBUG-102227
)

qt_internal_add_qml_module(VirtualKeyboard
    URI "QtQuick.VirtualKeyboard"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 2 1
    PLUGIN_TARGET qtvkbplugin
    DEPENDENCIES
        QtQuick/auto
        QtQuick.Window/auto
        QtQuick.Layouts/auto
        Qt.labs.folderlistmodel/auto
        QtQuick.VirtualKeyboard.Settings/auto
        QtQuick.VirtualKeyboard.Styles/auto
        QtQuick.VirtualKeyboard.Plugins/auto
    IMPORTS
        QtQuick.VirtualKeyboard.Layouts/auto
        QtQuick.VirtualKeyboard.Components/auto ### Qt7: Move to dependencies, see QTBUG-102227
    SOURCES
        abstractinputpanel.cpp abstractinputpanel_p.h
        appinputpanel.cpp appinputpanel_p.h
        appinputpanel_p_p.h
        desktopinputselectioncontrol.cpp desktopinputselectioncontrol_p.h
        enterkeyaction.cpp enterkeyaction_p.h
        enterkeyactionattachedtype.cpp enterkeyactionattachedtype_p.h
        fallbackinputmethod.cpp fallbackinputmethod_p.h
        gesturerecognizer.cpp gesturerecognizer_p.h
        handwritinggesturerecognizer.cpp handwritinggesturerecognizer_p.h
        inputmethod.cpp inputmethod_p.h
        inputselectionhandle.cpp inputselectionhandle_p.h
        virtualkeyboard.cpp virtualkeyboard_p.h
        virtualkeyboardattachedtype.cpp virtualkeyboardattachedtype_p.h
        plaininputmethod.cpp plaininputmethod_p.h
        platforminputcontext.cpp platforminputcontext_p.h
        qvirtualkeyboard_global.h qvirtualkeyboard_global_p.h
        qvirtualkeyboard_namespace.h
        qvirtualkeyboardabstractinputmethod.cpp qvirtualkeyboardabstractinputmethod.h
        qvirtualkeyboardabstractinputmethod_p.cpp qvirtualkeyboardabstractinputmethod_p.h
        qvirtualkeyboarddictionary.cpp qvirtualkeyboarddictionary.h
        qvirtualkeyboarddictionarymanager.cpp qvirtualkeyboarddictionarymanager.h
        qvirtualkeyboardfeatures_namespace_p.h
        qvirtualkeyboardinputcontext.cpp qvirtualkeyboardinputcontext.h qvirtualkeyboardinputcontext_p.cpp qvirtualkeyboardinputcontext_p.h
        qvirtualkeyboardinputengine.cpp qvirtualkeyboardinputengine.h
        qvirtualkeyboardnamespace_p.h
        qvirtualkeyboardobserver.cpp qvirtualkeyboardobserver.h
        qvirtualkeyboardselectionlistmodel.cpp qvirtualkeyboardselectionlistmodel.h
        qvirtualkeyboardtrace.cpp qvirtualkeyboardtrace.h
        settings.cpp settings_p.h
        shadowinputcontext.cpp shadowinputcontext_p.h
        shifthandler.cpp shifthandler_p.h
        virtualkeyboarddebug_p.h
    QML_FILES
        ${qml_files}
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
        QVIRTUALKEYBOARD_LIBRARY
    LIBRARIES
        Qt::CorePrivate
        Qt::GuiPrivate
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
    PRIVATE_MODULE_INTERFACE
        Qt::CorePrivate
        Qt::GuiPrivate
    GENERATE_CPP_EXPORTS
    GENERATE_PRIVATE_CPP_EXPORTS
)

qt_internal_extend_target(VirtualKeyboard CONDITION QT_FEATURE_vkb_desktop
    SOURCES
        desktopinputpanel.cpp desktopinputpanel_p.h
        inputview.cpp inputview_p.h
    DEFINES
        QT_VIRTUALKEYBOARD_DESKTOP
)

qt_internal_extend_target(VirtualKeyboard CONDITION QT_FEATURE_vkb_record_trace_input
    SOURCES
        unipentrace.cpp unipentrace_p.h
    PUBLIC_DEFINES
        QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
)

qt_internal_extend_target(VirtualKeyboard CONDITION QT_FEATURE_vkb_arrow_keynavigation
    DEFINES
        QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
)

qt_internal_add_docs(VirtualKeyboard
    doc/qtvirtualkeyboard.qdocconf
)
