// Copyright (C) 2016 Jeremy Katz
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtQuickTest/quicktest.h>
#include <QByteArray>

static bool s_configImport = qputenv("QML2_IMPORT_PATH", TESTDATA_DIR);
static bool s_configIM = qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

QUICK_TEST_MAIN(styles)
