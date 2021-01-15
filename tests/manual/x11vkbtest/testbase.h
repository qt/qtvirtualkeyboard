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
