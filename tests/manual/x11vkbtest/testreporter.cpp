/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include <QFile>
#include <QTextStream>
#include <QVectorIterator>
#include <QTextStream>
#include "testreporter.h"
#include "testbase.h"
#include "colors.h"
#include "startclose.h"

namespace {
const QString KReport_CSV_File = "result.csv";
const QString KCSV_Column_Separator = ";";
}

TestReporter::TestReporter(QObject *parent) : QObject(parent)
{
}

void TestReporter::startMemoryReport()
{
    QFile file(KReport_CSV_File);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "Time" << KCSV_Column_Separator;
        stream << "Process Memory size" << KCSV_Column_Separator << endl;
        file.close();
    }
}

void TestReporter::printTestResultsToCSV(const QVector<TestBase *> &tests) const
{
    QFile file(KReport_CSV_File);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&file);

        stream << endl;
        qint64 timeElapsed = 0;
        quint8 passed = 0;
        quint8 failed = 0;
        bool currentTestIsStartClose = true;

        for (auto test : tests) {
            if (nullptr == qobject_cast<StartClose*>(test)) {
                currentTestIsStartClose = false;
                if (test->passed()) {
                    stream << "PASS" << KCSV_Column_Separator;
                    passed++;
                } else {
                    stream << "FAIL" << KCSV_Column_Separator;
                    failed++;
                }
            }
            stream << test->testName() << KCSV_Column_Separator
                   << test->timeElapsed() << "s" << endl;

            QString extraInfo = test->reportResult();
            if (!extraInfo.isEmpty()) {
                extraInfo.replace(QString(": "), QString(KCSV_Column_Separator));
                stream << extraInfo << endl;
            }
            timeElapsed = timeElapsed + test->timeElapsed();

            if (currentTestIsStartClose) {
                stream << endl;
            }
        }

        stream << endl;
        stream << "Totals" << KCSV_Column_Separator << passed << " passed "
               << KCSV_Column_Separator << failed << " failed"
               << KCSV_Column_Separator << timeElapsed << "s";
        stream << endl;
        file.close();
    }
}

void TestReporter::printMemoryResultToCSV(QString minPeakMemoryReport) const
{
    QFile file(KReport_CSV_File);

    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&file);
        minPeakMemoryReport.replace(QString(": "), QString(KCSV_Column_Separator));
        stream << minPeakMemoryReport << endl;
        file.close();
    }
}

void TestReporter::printTestResultToConsole(const QVector<TestBase *> &tests) const
{
    QTextStream stream(stdout);

    qint64 timeElapsed = 0;
    quint8 passed = 0;
    quint8 failed = 0;

    for (auto test : tests) {
        if (nullptr == qobject_cast<StartClose*>(test)) {
            if (test->passed()) {
                stream << FBold(FGreen("PASS: "));
                passed++;
            } else {
                stream << FBold(FRed("FAIL:"));
                failed++;
            }
        }
        stream << test->testName() << " " << test->timeElapsed() << "s" << endl;
        QString extraInfo = test->reportResult();
        if (!extraInfo.isEmpty()) {
            stream << extraInfo << endl;
        }

        timeElapsed = timeElapsed + test->timeElapsed();
    }

    stream << "Totals: " << passed << " passed, " << failed << " failed. " << timeElapsed << "s";
    stream << endl;
}

void TestReporter::currentMemUsage(const quint64 timeElapsed, const ulong memSize) const
{
    QFile file(KReport_CSV_File);

    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&file);
        stream << timeElapsed << "s" << KCSV_Column_Separator;
        stream << memSize << " KB" << KCSV_Column_Separator << endl;
        file.close();
    }
}
