/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtQml>
#include <qpa/qplatforminputcontextplugin_p.h>
#include "platforminputcontext.h"
#include <QStringList>

class QVirtualKeyboardPlugin : public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "qtvirtualkeyboard.json")

public:
    QStringList keys() const;
    QPlatformInputContext *create(const QString&, const QStringList&);
};

#endif // PLUGIN_H
