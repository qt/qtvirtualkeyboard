// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef TESTLANGUAGECHANGE_H
#define TESTLANGUAGECHANGE_H

#include <QObject>
#include "testbase.h"

class WindowHelper;
class MouseSimulator;
class ProcessHandler;

class TestLanguageChange : public TestBase
{
    Q_OBJECT
public:
    explicit TestLanguageChange(QObject *parent, WindowHelper &windowHelper, quint32 numberOfTests, qint64 x11vkbProcId = 0);
    ~TestLanguageChange() {}

public:
    void setProcID(const qint64 procID) {m_x11vkbProcId = procID;}

public slots:
    void startTest() override;

private slots:
    void doTest();

private:
    quint8 verifyLanguage(const quint16 num, const bool langLineInListIsKnown = true);
    void deleteTestFile();

private:
    WindowHelper &m_windowHelper;
    ProcessHandler *m_otherProcHandler;
    quint8 m_currentLangNum;
};

#endif // TESTLANGUAGECHANGE_H
