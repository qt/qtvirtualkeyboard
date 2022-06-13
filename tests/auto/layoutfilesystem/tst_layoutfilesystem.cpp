// Copyright (C) 2016 Pelagicore AB
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "layouttesthelper.h"

#include <QtTest/qtest.h>

static bool moduleEnv = qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

class tst_layoutfilesystem : public QObject
{
    Q_OBJECT

public:

private slots:
    void layouts();
};

void tst_layoutfilesystem::layouts()
{
    QString layoutPath(SRC_DIR "/data/layouts");

    qputenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH", qPrintable(layoutPath));

    LayoutTestHelper layoutTestHelper;

    layoutTestHelper.window->show();
    QVERIFY(QTest::qWaitForWindowExposed(layoutTestHelper.window.data()));
    QCoreApplication::processEvents(); // Process all queued events

    QObject *layout = layoutTestHelper.window->findChild<QObject*>("en_GB");
    QVERIFY(layout);

    QObject *settings = layoutTestHelper.window->property("settings").value<QObject*>();
    QVERIFY(settings);
    // availableLocales is based off of FolderListModel, which uses a QThread to
    // offload the work of getting the contents of a directory. Being
    // asynchronous, it can take a varying amount of time.
    QTRY_COMPARE(settings->property("availableLocales").toStringList(), QStringList() << "en_GB");
}

QTEST_MAIN(tst_layoutfilesystem)

#include "tst_layoutfilesystem.moc"
