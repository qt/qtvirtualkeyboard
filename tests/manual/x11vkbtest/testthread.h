// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>
#include "testbase.h"

class TestBase;

class TestThread : public QThread
{
    Q_OBJECT
public:
    explicit TestThread(const QString &x11vkbPath, quint32 startCloseTest, quint32 keyOperationTest, quint32 langChangeTest, QObject *parent = nullptr);

public:
    void run() override;

signals:
    void resultReady(const QString &s);
    void processID(const qint64 procID);
    void startMemoryMonitor();

private:
    const QString &m_x11vkbPath;
    quint32 m_numberOfStartClose;
    quint32 m_numberOfKeyOperation;
    quint32 m_numberOfLangChange;
};

#endif // TESTTHREAD_H
