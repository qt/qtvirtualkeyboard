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

#include "qtquickvirtualkeyboardsettingsplugin.h"
#include <QtVirtualKeyboard/private/virtualkeyboardsettings_p.h>
#include <QtVirtualKeyboard/private/qvirtualkeyboard_staticplugin_p.h>

QT_BEGIN_NAMESPACE

using namespace QtVirtualKeyboard;

void QtQuickVirtualKeyboardSettingsPlugin::registerTypes(const char *uri)
{
#if defined(QT_STATICPLUGIN)
    Q_VKB_IMPORT_PLUGIN(QtQuick2Plugin)
#endif

    qmlRegisterSingletonType<VirtualKeyboardSettings>(uri, 1, 0, "VirtualKeyboardSettings", VirtualKeyboardSettings::registerSettingsModule);
    qmlRegisterSingletonType<VirtualKeyboardSettings>(uri, 1, 1, "VirtualKeyboardSettings", VirtualKeyboardSettings::registerSettingsModule);
    qmlRegisterSingletonType<VirtualKeyboardSettings>(uri, 1, 2, "VirtualKeyboardSettings", VirtualKeyboardSettings::registerSettingsModule);
    qmlRegisterSingletonType<VirtualKeyboardSettings>(uri, 2, 0, "VirtualKeyboardSettings", VirtualKeyboardSettings::registerSettingsModule);
    qmlRegisterSingletonType<VirtualKeyboardSettings>(uri, 2, 1, "VirtualKeyboardSettings", VirtualKeyboardSettings::registerSettingsModule);
    qRegisterMetaType<WordCandidateListSettings *>("WordCandidateListSettings*");
    qmlRegisterUncreatableType<WordCandidateListSettings>(uri, 2, 2, "WordCandidateListSettings", QLatin1String("Cannot create word candidate list settings"));

    // Auto-increment the import to stay in sync with ALL future QtQuick minor versions
    qmlRegisterModule(uri, 2, QT_VERSION_MINOR);
}

QT_END_NAMESPACE
