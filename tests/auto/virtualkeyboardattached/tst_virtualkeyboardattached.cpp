// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtQuickTest/quicktest.h>
#include <QByteArray>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>

static bool s_configEnv = qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

QUICK_TEST_MAIN(virtualkeyboardattached)
