/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
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

#include "extensionloader.h"
#include <QtVirtualKeyboard/QVirtualKeyboardExtensionPlugin>
#include <QtCore/private/qfactoryloader_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

QMutex ExtensionLoader::m_mutex;
QMultiHash<QString, QCborMap> ExtensionLoader::m_plugins;
bool ExtensionLoader::m_alreadyDiscovered = false;

Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, loader,
        (QVirtualKeyboardExtensionPluginFactoryInterface_iid,
         QLatin1String("/virtualkeyboard")))

QMultiHash<QString, QCborMap> ExtensionLoader::plugins(bool reload)
{
    QMutexLocker lock(&m_mutex);

    if (reload == true)
        m_alreadyDiscovered = false;

    if (!m_alreadyDiscovered) {
        loadPluginMetadata();
        m_alreadyDiscovered = true;
    }
    return m_plugins;
}

QCborMap ExtensionLoader::loadMeta(const QString &extensionName)
{
    QCborMap metaData;
    QList<QCborMap> candidates = ExtensionLoader::plugins().values(extensionName);

    int versionFound = -1;

    // figure out which version of the plugin we want
    for (int i = 0; i < candidates.size(); ++i) {
        QCborMap meta = candidates[i];
        if (int ver = meta.value(QLatin1String("Version")).toInteger(); ver > versionFound) {
            versionFound = ver;
            metaData = std::move(meta);
        }
    }

    if (metaData.isEmpty())
        metaData.insert(QLatin1String("index"), -1); // not found
    return metaData;
}

QVirtualKeyboardExtensionPlugin *ExtensionLoader::loadPlugin(QCborMap metaData)
{
    int idx = metaData.value(QLatin1String("index")).toInteger();
    if (idx < 0)
        return nullptr;
    return qobject_cast<QVirtualKeyboardExtensionPlugin *>(loader()->instance(idx));
}

void ExtensionLoader::loadPluginMetadata()
{
    QFactoryLoader *l = loader();
    QList<QPluginParsedMetaData> meta = l->metaData();
    for (int i = 0; i < meta.size(); ++i) {
        QCborMap obj = meta.at(i).value(QtPluginMetaDataKeys::MetaData).toMap();
        QString name = obj.value(QLatin1String("Name")).toString();
        if (!name.isEmpty()) {
            obj.insert(QLatin1String("index"), i);
            m_plugins.insert(name, obj);
        }
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
