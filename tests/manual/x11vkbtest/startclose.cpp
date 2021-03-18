/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QTimer>

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
        availableMemSize = procStream.readLine().split(QRegExp("\\s+")).at(1).toULong();
        procFile.close();
    }
    return availableMemSize;
}
