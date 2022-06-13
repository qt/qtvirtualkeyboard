// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QRegularExpression>

#include "startclose.h"

namespace  {
const QString KTest_Name = "Test start/close %1 times.";
const quint16 KTestCycles = 25;
const int KTestMultiplier = 2;
}

StartClose::StartClose(QProcess &proc, quint32 numberOfTests, QObject *parent)
    : TestBase (parent, KTest_Name, numberOfTests),
    m_procToTest(proc),
    m_results(QStringList()),
    m_testCycleCount(0)
{
    this->setTestRepeats(KTestCycles);
    this->setTestName();
    QObject::connect(&m_procToTest, &QProcess::started, this, &StartClose::runCycles);
    QObject::connect(&m_procToTest, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
                     this, &StartClose::runCycles);
}

void StartClose::startTest()
{
    m_testTimer.start();
    m_procToTest.start();
}

void StartClose::runCycles()
{
    QTimer::singleShot(50, this, [&]() {
        if (m_testCycleCount == 0) {
            m_results << QString::number(this->currentTotalAvailableMemory());
        }
        // The original number of tests will be multiplied by 2 because we always need to
        // have even number of test cycles because one cycle consists off ON & OFF.
        if (m_testCycleCount == (m_numberOfTests * KTestMultiplier)) {
            m_results << QString::number(this->currentTotalAvailableMemory());
            QObject::disconnect(&m_procToTest, &QProcess::started, this, &StartClose::startTest);
            QObject::disconnect(&m_procToTest,
                                static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
                                this, &StartClose::startTest);

            m_passed = true;
            m_timeElapsed = m_testTimer.elapsed();

            emit endTest();
            return;
        }
        m_testCycleCount ++;

        if (m_procToTest.state() == QProcess::Running) {
            m_procToTest.kill();
        } else {
            m_procToTest.start();
        }
    });
}

QString StartClose::reportResult()
{
    m_testResult =
        QString("Total free system memory at start: %1 KB\nTotal free system memory at end: %2 KB\nDifference: %3 KB")
            .arg(m_results.value(0).toInt()).arg(m_results.value(1).toInt())
            .arg(m_results.value(1).toInt() - m_results.value(0).toInt());
    return m_testResult;
}

/**
 * @brief StartClose::currentTotalAvailableMemory
 * @return current free system memory by procID in kB
 * Getting current free memory using Linux proc
 * filesystem.
 */
ulong StartClose::currentTotalAvailableMemory() const
{
    ulong availableMemSize = 0UL;
    QString str = QString("/proc/meminfo");
    QFile procFile(str);

    if (procFile.open(QIODevice::ReadOnly)) {
        QTextStream procStream(&procFile);
        procStream.readLine(); // "Read away" the first row
        availableMemSize = procStream.readLine().split(QRegularExpression("\\s+")).at(1).toULong();
        procFile.close();
    }
    return availableMemSize;
}
