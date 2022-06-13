// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QTQUICKVIRTUALKEYBOARDSTYLESBUILTINPLUGIN_H
#define QTQUICKVIRTUALKEYBOARDSTYLESBUILTINPLUGIN_H

#include <QQmlEngineExtensionPlugin>

QT_BEGIN_NAMESPACE

class QtQuickVirtualKeyboardStylesBuiltinPlugin : public QQmlEngineExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtQuickVirtualKeyboardStylesBuiltinPlugin(QObject *parent = nullptr);
};

QT_END_NAMESPACE

#endif // QTQUICKVIRTUALKEYBOARDSTYLESBUILTINPLUGIN_H

