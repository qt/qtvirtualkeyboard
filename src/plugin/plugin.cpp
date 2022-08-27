// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "plugin.h"
#include <QtVirtualKeyboard/private/platforminputcontext_p.h>
#include <QLoggingCategory>
#if defined(Q_OS_WIN)
#include <qt_windows.h>
#endif

QT_BEGIN_NAMESPACE

using namespace QtVirtualKeyboard;

Q_LOGGING_CATEGORY(qlcVirtualKeyboard, "qt.virtualkeyboard")

static const char pluginName[] = "qtvirtualkeyboard";
static const char inputMethodEnvVarName[] = "QT_IM_MODULE";

QStringList QVirtualKeyboardPlugin::keys() const
{
    return QStringList(QLatin1String(pluginName));
}

QPlatformInputContext *QVirtualKeyboardPlugin::create(const QString &system, const QStringList &paramList)
{
    Q_UNUSED(paramList);

    if (!qEnvironmentVariableIsSet(inputMethodEnvVarName) || qgetenv(inputMethodEnvVarName) != pluginName)
        return nullptr;

    if (system.compare(system, QLatin1String(pluginName), Qt::CaseInsensitive) != 0)
        return nullptr;

#if defined(Q_OS_WIN)
    // QTBUG-93042
    ImmDisableIME(0);
#endif

    PlatformInputContext *platformInputContext = new PlatformInputContext();

    return platformInputContext;
}

QT_END_NAMESPACE
