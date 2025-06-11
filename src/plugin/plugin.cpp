// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
// Qt-Security score:significant reason:default

#include "plugin.h"
#include <private/settings_p.h>
#include <QtVirtualKeyboard/private/platforminputcontext_p.h>
#include <QLoggingCategory>
#if defined(Q_OS_WIN)
#include <qt_windows.h>
#endif
#include <qpa/qplatforminputcontextfactory_p.h>

#include <algorithm>

QT_BEGIN_NAMESPACE

using namespace Qt::StringLiterals;

using namespace QtVirtualKeyboard;

Q_LOGGING_CATEGORY(qlcVirtualKeyboard, "qt.virtualkeyboard")

static constexpr auto pluginName = "qtvirtualkeyboard"_L1;

QStringList QVirtualKeyboardPlugin::keys() const
{
    return QStringList(pluginName);
}

static bool evaluateParameter(QStringView param)
{
    if (param == "wordCandidateListVisible"_L1) {
        Settings::instance()->setWclAlwaysVisible(true);
        return true;
    }
    if (param == "wordCandidateListAutoCommitWord"_L1) {
        Settings::instance()->setWclAutoCommitWord(true);
        return true;
    }
    if (param == "fullScreen"_L1) {
        Settings::instance()->setFullScreenMode(true);
        return true;
    }

    const auto equalsPos = param.indexOf(u'=');
    if (equalsPos == -1 || equalsPos == param.size() - 1)
        return false;

    const auto keyword = param.sliced(0, equalsPos);
    const auto value = param.sliced(equalsPos + 1);
    if (keyword == "style"_L1) {
        Settings::instance()->setStyleName(value.toString());
        return true;
    }
    if (keyword == "locale"_L1) {
        Settings::instance()->setLocale(value.toString());
        return true;
    }

    return false;
}

static bool vkbRequested(const QString &req)
{
    return req.startsWith(pluginName);
}

QPlatformInputContext *QVirtualKeyboardPlugin::create(const QString &system, const QStringList &paramList)
{
    const auto &requested = QPlatformInputContextFactory::requested();
    if (std::none_of(requested.cbegin(), requested.cend(), vkbRequested))
        return nullptr;

    if (system.compare(pluginName, Qt::CaseInsensitive) != 0)
        return nullptr;

#if defined(Q_OS_WIN)
    // QTBUG-93042
    ImmDisableIME(0);
#endif

    for (const auto &param : paramList) {
        QStringView paramV{param};
        const auto params = paramV.split(u',');
        for (const auto &param : params) {
            if (!evaluateParameter(param)) {
                qCWarning(qlcVirtualKeyboard, "Invalid parameter \"%s\".",
                          qPrintable(param.toString()));
            }
        }
    }

    PlatformInputContext *platformInputContext = new PlatformInputContext();

    return platformInputContext;
}

QT_END_NAMESPACE
