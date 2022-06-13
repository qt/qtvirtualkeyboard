// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef STARTCLOSE_H
#define STARTCLOSE_H

#include "testbase.h"

#include <QTime>

class QProcess;

class StartClose : public TestBase
{
    Q_OBJECT
public:
    explicit StartClose(QProcess &proc, quint32 numberOfTests, QObject *parent = nullptr);
    ~StartClose() {}

public:
    ulong currentTotalAvailableMemory() const;
    QString reportResult() override;

public slots:
    void startTest() override;
    void runCycles();

private:
    QProcess &m_procToTest;
    QStringList m_results;
    quint32 m_testCycleCount;
};

#endif // STARTCLOSE_H
