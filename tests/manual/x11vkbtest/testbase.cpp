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

#include <QTextStream>
#include "testbase.h"

namespace {
const qint32 KMs_In_Sec = 1000;
}

TestBase::TestBase(QObject *parent, QString testName, quint32 numberOfTests, qint64 x11vkbProcId):
    QObject(parent),
    m_x11vkbProcId(x11vkbProcId),
    m_testTimer(QElapsedTimer()),
    m_timeElapsed(0),
    m_testName(testName),
    m_numberOfTests(numberOfTests),
    m_testResult(QString()),
    m_passed(false)

{}

QString TestBase::reportResult()
{
    return m_testResult;
}

void TestBase::setProcID(const qint64 procID)
{
    m_x11vkbProcId = procID;
}

QString TestBase::testName() const
{
    return m_testName;
}

void TestBase::setTestName()
{
    m_testName = m_testName.arg(m_numberOfTests);
}
void TestBase::printResult(QTextStream &stream) const
{
    stream << m_testResult;
}

bool TestBase::passed() const
{
    return m_passed;
}

qint64 TestBase::timeElapsed() const
{
    return m_timeElapsed/KMs_In_Sec;
}

bool TestBase::shiftIsDown = false;

void TestBase::setTestRepeats(const quint32 repeats)
{
    if (m_numberOfTests == 0) {
        m_numberOfTests = repeats;
    }
}
