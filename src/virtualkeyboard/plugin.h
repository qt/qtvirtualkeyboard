/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtQml>
#include <qpa/qplatforminputcontextplugin_p.h>
#include "platforminputcontext.h"
#include <QStringList>

class PlatformInputContextPlugin : public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QPlatformInputContextFactoryInterface" FILE "qtvirtualkeyboard.json")

public:
    QStringList keys() const;
    QPlatformInputContext *create(const QString&, const QStringList&);
};

#endif // PLUGIN_H
