// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtQuickTest/quicktest.h>
#include <QByteArray>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>

static bool s_configEnv = qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
static bool initStandardPaths() {
    QStandardPaths::setTestModeEnabled(true);
    auto configLocations = QStringList()
            << QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/qtvirtualkeyboard"
            << QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/qtvirtualkeyboard";
    for (const QString &configLocation : configLocations) {
        if (configLocation != "/qtvirtualkeyboard")
            QDir(configLocation).removeRecursively();
    }
    return true;
}
static bool s_initStandardPaths = initStandardPaths();

QUICK_TEST_MAIN(inputpanelcontrols)
