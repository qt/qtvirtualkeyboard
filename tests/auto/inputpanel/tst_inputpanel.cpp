// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtQuickTest/quicktest.h>
#include <QByteArray>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>

namespace
{

struct VirtualKeyboardSetup : QObject
{
    VirtualKeyboardSetup()
    {
        qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
        QStandardPaths::setTestModeEnabled(true);
        auto configLocations = QStringList()
                << QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/qtvirtualkeyboard"
                << QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/qtvirtualkeyboard";
        for (const QString &configLocation : configLocations) {
            if (configLocation != "/qtvirtualkeyboard")
                QDir(configLocation).removeRecursively();
        }
    }
};

}

QUICK_TEST_MAIN_WITH_SETUP(inputpanel, VirtualKeyboardSetup)
