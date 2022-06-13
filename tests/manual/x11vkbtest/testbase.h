// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef TESTBASE_H
#define TESTBASE_H

#include <QObject>
#include <QElapsedTimer>

class QTextStream;

class TestBase : public QObject
{
    Q_OBJECT

public:
    explicit TestBase(QObject *parent, QString testName, quint32 numberOfTests, qint64 x11vkbProcId = 0);
    virtual ~TestBase() {}

public:
    virtual QString reportResult();
    void setProcID(const qint64 procID);
    QString testName() const;
    void setTestName();
    void printResult(QTextStream &stream) const;
    bool passed() const;
    qint64 timeElapsed() const;
    void setTestRepeats(const quint32 repeats);

signals:
    void endTest();

public slots:
    virtual void startTest() = 0;

protected:
    static bool shiftIsDown;
    qint64 m_x11vkbProcId;
    QElapsedTimer m_testTimer;

    qint64 m_timeElapsed;
    QString m_testName;
    quint32 m_numberOfTests;
    QString m_testResult;
    bool m_passed;
};

#endif // TESTBASE_H
