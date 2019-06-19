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

#include <QEventLoop>
#include <QFile>
#include <QElapsedTimer>
#include <QLoggingCategory>

#include "testreporter.h"
#include "processhandler.h"
#include "startclose.h"
#include "testenglishletters.h"
#include "testlanguagechange.h"
#include "testthread.h"
#include "windowhelper.h"

namespace {
const quint32 KTime_Wait_To_Start_Test = 1000000;
}

Q_LOGGING_CATEGORY(lcTestThread, "qt.virtualkeyboard.tests.manual.x11vkbtest.testthread")

TestThread::TestThread(const QString &x11vkbPath, quint32 startCloseTest, quint32 keyOperationTest, quint32 langChangeTest, QObject *parent) :
    QThread(parent),
    m_x11vkbPath(x11vkbPath),
    m_numberOfStartClose(startCloseTest),
    m_numberOfKeyOperation(keyOperationTest),
    m_numberOfLangChange(langChangeTest)
{
}

void TestThread::run()
{
    QElapsedTimer testTimer;
    testTimer.start();

    QVector<TestBase*> tests;

    TestReporter reporter;
    WindowHelper windowHelper;
    auto x11vkbProcHandler = new ProcessHandler(&windowHelper, m_x11vkbPath);

    if (m_numberOfStartClose > 0 || (m_numberOfKeyOperation == 0 && m_numberOfLangChange == 0)) {
        auto startClose = new StartClose(*x11vkbProcHandler->getPRocess(), m_numberOfStartClose, &windowHelper);
        tests.append(startClose);
    }

    if (m_numberOfKeyOperation > 0 || (m_numberOfStartClose == 0 && m_numberOfLangChange == 0)) {
        auto testEngLetters = new TestEnglishLetters(&windowHelper, windowHelper, m_numberOfKeyOperation);
        tests.append(testEngLetters);
    }

    if (m_numberOfLangChange > 0 || (m_numberOfStartClose == 0 && m_numberOfKeyOperation == 0)) {
        auto testLang = new TestLanguageChange(&windowHelper, windowHelper, m_numberOfLangChange);
        tests.append(testLang);
    }

    bool startVKB = true;
    if (tests.size() == 1 && nullptr != qobject_cast<StartClose*>(tests.first())) {
        startVKB = false;
    }
    /* main loop to connect test each after another */
    for (int i = 0 ; i < tests.size() - 1 ; ++i) {
        if (nullptr != qobject_cast<StartClose*>(tests.at(i))) {
            QObject::connect(tests.at(i), &StartClose::endTest, [&]() {

                auto x11vkbProcId = x11vkbProcHandler->getProcId();

                emit processID(x11vkbProcId);

                for (int i = 1 ; i < tests.size() ; ++i) {
                    tests.at(i)->setProcID(x11vkbProcId);
                }
                if (tests.size() > 1) {
                    emit startMemoryMonitor();
                    usleep(KTime_Wait_To_Start_Test);
                    tests.at(1)->startTest();
                }
            });
            startVKB = false;
        } else {
            QObject::connect(tests.at(i), &TestBase::endTest, tests.at(i+1), &TestBase::startTest);
        }
    }

    if (startVKB) {
        emit startMemoryMonitor();
        x11vkbProcHandler->startProc();
        qCDebug(lcTestThread) << "Explicitly start process";
        auto x11vkbProcId = x11vkbProcHandler->getProcId();

        emit processID(x11vkbProcId);

        for (auto test : tests) {
            test->setProcID(x11vkbProcId);
        }
        usleep(KTime_Wait_To_Start_Test);
    }

    QObject::connect(tests.last(), &TestBase::endTest,  this, &QThread::quit);

    tests.first()->startTest();
    exec();

    reporter.printTestResultsToCSV(tests);
    reporter.printTestResultToConsole(tests);

    x11vkbProcHandler->closeProcess();
}
