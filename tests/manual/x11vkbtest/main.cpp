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

#include <QApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QStateMachine>
#include <QtGui/QGuiApplication>
#include <QtCharts/QChartView>
#include <QtWidgets/QMainWindow>

#include "processhandler.h"
#include "windowhelper.h"
#include "testenglishletters.h"
#include "startclose.h"
#include "memorymonitor.h"
#include "testlanguagechange.h"
#include "testthread.h"
#include "testreporter.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("X11VKB Testing application");
    parser.addHelpOption();

    parser.addOption({"exec", "Give absolute path to target <executable>. See README.md for usage instructions.", "directory"});

    parser.addOption({"sc", "Give a number of how many times a start&close cycle is to be executed.", "number"});

    parser.addOption({"ko", "Give a number of how many times a key operation test is to be executed.", "number"});

    parser.addOption({"lc", "Give a number of how many times a language change test is to be executed.", "number"});

    parser.process(app);

    QString x11vkbPath = parser.value("exec");
    if (x11vkbPath.isEmpty()) {
        qWarning() << "Give absolute path to target executable, including the filename";
        qWarning() << "Example: --exec <path_to_executable>.";
        qWarning() << "See README.md for detailed usage instructions.";
        return 1;
    }

    quint32 startCloseTest = static_cast<quint16>(parser.value("sc").toInt());
    quint32 keyOperationTest = static_cast<quint16>(parser.value("ko").toInt());
    quint32 langChangeTest = static_cast<quint16>(parser.value("lc").toInt());

    QMainWindow window;
    window.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    auto memoryMonitor = new MemoryMonitor(window);

    memoryMonitor->legend()->hide();
    QChartView chartView(memoryMonitor);
    chartView.setRenderHint(QPainter::Antialiasing);

    window.setCentralWidget(&chartView);
    window.resize(900, 600);
    window.show();
    memoryMonitor->init();

    TestReporter reporter;
    reporter.startMemoryReport();
    QObject::connect(memoryMonitor, &MemoryMonitor::memUsage, &reporter, &TestReporter::currentMemUsage);

    auto testThread = new TestThread(x11vkbPath, startCloseTest, keyOperationTest, langChangeTest, &app);
    QObject::connect(testThread, &TestThread::startMemoryMonitor, memoryMonitor, &MemoryMonitor::start);
    QObject::connect(testThread, &TestThread::processID, memoryMonitor, &MemoryMonitor::setProcID);
    QObject::connect(testThread, &TestThread::finished, testThread, &QObject::deleteLater);
    QObject::connect(testThread, &TestThread::finished, memoryMonitor, &MemoryMonitor::stopChart);
    QObject::connect(memoryMonitor, &MemoryMonitor::minAndPeakReport, &reporter, &TestReporter::printMemoryResultToCSV);
    QObject::connect(testThread, &TestThread::finished, &app, &QApplication::quit);
    testThread->start();

    return app.exec();
}
