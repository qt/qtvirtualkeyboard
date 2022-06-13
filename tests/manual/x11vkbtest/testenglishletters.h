// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef TESTENGLISHLETTERS_H
#define TESTENGLISHLETTERS_H

#include <QObject>
#include "testbase.h"

class WindowHelper;
class ProcessHandler;

class TestEnglishLetters : public TestBase
{
    Q_OBJECT
public:
    explicit TestEnglishLetters(QObject *parent, WindowHelper &windowHelper, quint32 numberOfTests, qint64 x11vkbProcId = 0);
    ~TestEnglishLetters() {}

public:
    void setTestingString();

public slots:
    void startTest() override;

private slots:
    void doTestLettersInGedit();

private:
    void verifyResult();
    void deleteTestFile() const;

private:
    WindowHelper &m_windowHelper;
    ProcessHandler *m_otherProcHandler;
    QString m_letters;
};

#endif // TESTENGLISHLETTERS_H
