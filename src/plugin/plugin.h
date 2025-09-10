// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef PLUGIN_H
#define PLUGIN_H

#include <qpa/qplatforminputcontextplugin_p.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardPlugin : public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "qtvirtualkeyboard.json")

public:
    QStringList keys() const;
    QPlatformInputContext *create(const QString&, const QStringList&) override;
};

QT_END_NAMESPACE

#endif // PLUGIN_H
