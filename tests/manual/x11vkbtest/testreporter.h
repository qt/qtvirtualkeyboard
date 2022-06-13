// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CSVPRINTER_H
#define CSVPRINTER_H

#include <QObject>

class TestBase;

class TestReporter : public QObject
{
    Q_OBJECT
public:
    explicit TestReporter(QObject *parent = nullptr);

public:
    void startMemoryReport();
    void printTestResultsToCSV(const QList<TestBase *> &tests) const;
    void printTestResultToConsole(const QList<TestBase *> &tests) const;

public slots:
    void printMemoryResultToCSV(const QString minPeakMemoryReport) const;
    void currentMemUsage(const quint64 timeElapsed, const ulong memSize) const;
};

#endif // CSVPRINTER_H
