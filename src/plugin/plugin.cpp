/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "plugin.h"
#include "extensionloader.h"
#include <QtVirtualKeyboard/private/platforminputcontext_p.h>
#include <QtVirtualKeyboard/private/plaininputmethod_p.h>
#include <QtVirtualKeyboard/private/qvirtualkeyboard_staticplugin_p.h>
#include <QLoggingCategory>
#include <QtQml>
#if defined(Q_OS_WIN)
#include <qt_windows.h>
#endif

QT_BEGIN_NAMESPACE

using namespace QtVirtualKeyboard;

Q_LOGGING_CATEGORY(qlcVirtualKeyboard, "qt.virtualkeyboard")

static const char pluginsUri[] = "QtQuick.VirtualKeyboard.Plugins";
static const char pluginName[] = "qtvirtualkeyboard";
static const char inputMethodEnvVarName[] = "QT_IM_MODULE";

QStringList QVirtualKeyboardPlugin::keys() const
{
    return QStringList(QLatin1String(pluginName));
}

QPlatformInputContext *QVirtualKeyboardPlugin::create(const QString &system, const QStringList &paramList)
{
    Q_UNUSED(paramList);

#if defined(QT_STATICPLUGIN)
#if !defined(QT_VIRTUALKEYBOARD_DISABLE_LAYOUTS)
    Q_INIT_RESOURCE(qmake_virtualkeyboard_layouts);
#endif
    Q_INIT_RESOURCE(virtualkeyboard_content);
#if !defined(QT_VIRTUALKEYBOARD_NO_BUILTIN_STYLES)
    Q_INIT_RESOURCE(virtualkeyboard_default_style);
    Q_INIT_RESOURCE(virtualkeyboard_retro_style);
#endif
    Q_VKB_IMPORT_PLUGIN(QtQuickVirtualKeyboardPlugin)
    Q_VKB_IMPORT_PLUGIN(QtQuickVirtualKeyboardSettingsPlugin)
    Q_VKB_IMPORT_PLUGIN(QtQuickVirtualKeyboardStylesPlugin)
#endif

    if (!qEnvironmentVariableIsSet(inputMethodEnvVarName) || qgetenv(inputMethodEnvVarName) != pluginName)
        return Q_NULLPTR;

    if (system.compare(system, QLatin1String(pluginName), Qt::CaseInsensitive) != 0)
        return Q_NULLPTR;

#if defined(Q_OS_WIN)
    // QTBUG-93042
    ImmDisableIME(0);
#endif

    PlatformInputContext *platformInputContext = new PlatformInputContext();

    QStringList inputMethodList;
    inputMethodList.append(QLatin1String("PlainInputMethod"));
    qRegisterMetaType<PlainInputMethod *>("PlainInputMethod*");
    qmlRegisterType<PlainInputMethod>(pluginsUri, 1, 0, "PlainInputMethod");
    qmlRegisterType<PlainInputMethod>(pluginsUri, 2, 0, "PlainInputMethod");
    qmlRegisterType<PlainInputMethod>(pluginsUri, 2, 3, "PlainInputMethod");

    QMultiHash<QString, QJsonObject> extensions = ExtensionLoader::plugins();
    for (const QString &extensionName : extensions.uniqueKeys()) {
        QJsonObject metaData = ExtensionLoader::loadMeta(extensionName);
        if (metaData.isEmpty()) {
            qCWarning(qlcVirtualKeyboard) << "Error loading extension - metadata not found!";
            continue;
        }

        const QJsonValue &inputMethodValue = metaData.value(QLatin1String("InputMethod"));
        QStringList inputMethodValueList;
        if (inputMethodValue.isArray()) {
            for (const QJsonValue v : inputMethodValue.toArray()) {
                const QString &inputMethod = v.toString();
                if (!inputMethod.isEmpty())
                    inputMethodValueList.append(inputMethod);
            }
        } else {
            const QString &inputMethod = inputMethodValue.toString();
            if (!inputMethod.isEmpty())
                inputMethodValueList.append(inputMethod);
        }

        bool ignoreExtension = false;
        for (const QString &inputMethod : inputMethodValueList) {
            if (inputMethodList.contains(inputMethod)) {
                ignoreExtension = true;
                qCWarning(qlcVirtualKeyboard) << "Ignored extension" << extensionName <<
                                                 "by" << metaData.value(QLatin1String("Provider")).toString() <<
                                                 "-" << inputMethod << "is already registered!";
                break;
            }
        }

        if (ignoreExtension)
            continue;

        qCDebug(qlcVirtualKeyboard) << "Loading extension" << extensionName;
        QVirtualKeyboardExtensionPlugin *extensionPlugin = ExtensionLoader::loadPlugin(metaData);
        if (extensionPlugin && !inputMethodValueList.isEmpty()) {
            extensionPlugin->registerTypes(pluginsUri);
            inputMethodList.append(inputMethodValueList);
        }
    }

    // Auto-increment the import to stay in sync with ALL future QtQuick minor versions
    qmlRegisterModule(pluginsUri, 2, QT_VERSION_MINOR);

    platformInputContext->setInputMethods(inputMethodList);

    return platformInputContext;
}

QT_END_NAMESPACE
