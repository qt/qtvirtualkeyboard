/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

#ifndef EXTENSIONLOADER_H
#define EXTENSIONLOADER_H

#include <QMutex>
#include <QtVirtualKeyboard/QVirtualKeyboardExtensionPlugin>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class ExtensionLoader
{
    Q_DISABLE_COPY(ExtensionLoader)
public:
    static QMultiHash<QString, QJsonObject> plugins(bool reload = false);
    static QJsonObject loadMeta(const QString &extensionName);
    static QVirtualKeyboardExtensionPlugin *loadPlugin(QJsonObject metaData);

private:
    static void loadPluginMetadata();

private:
    static QMutex m_mutex;
    static QMultiHash<QString, QJsonObject> m_plugins;
    static bool m_alreadyDiscovered;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // EXTENSIONLOADER_H
