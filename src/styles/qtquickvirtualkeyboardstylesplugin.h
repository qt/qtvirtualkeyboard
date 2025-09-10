// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QTQUICKVIRTUALKEYBOARDSTYLESPLUGIN_H
#define QTQUICKVIRTUALKEYBOARDSTYLESPLUGIN_H

#include <QQmlExtensionPlugin>

QT_BEGIN_NAMESPACE

class QtQuickVirtualKeyboardStylesPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtQuickVirtualKeyboardStylesPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;
};

QT_END_NAMESPACE

#endif // STYLES_PLUGIN_H

