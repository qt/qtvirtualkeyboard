// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "qtquickvirtualkeyboardbstylesbuiltinplugin.h"

QT_BEGIN_NAMESPACE

extern void qml_register_types_QtQuick_VirtualKeyboard_Styles_Builtin();
Q_GHS_KEEP_REFERENCE(qml_register_types_QtQuick_VirtualKeyboard_Styles_Builtin);

QtQuickVirtualKeyboardStylesBuiltinPlugin::QtQuickVirtualKeyboardStylesBuiltinPlugin(QObject *parent) :
    QQmlEngineExtensionPlugin(parent)
{
    volatile auto registration = &qml_register_types_QtQuick_VirtualKeyboard_Styles_Builtin;
    Q_UNUSED(registration);
#if defined(QT_STATICPLUGIN)
    Q_INIT_RESOURCE(virtualkeyboard_default_style);
    Q_INIT_RESOURCE(virtualkeyboard_retro_style);
#endif
}

QT_END_NAMESPACE
