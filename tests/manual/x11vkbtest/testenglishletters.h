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
