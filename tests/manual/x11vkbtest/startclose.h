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

#ifndef STARTCLOSE_H
#define STARTCLOSE_H

#include "testbase.h"

#include <QTime>

class QProcess;

class StartClose : public TestBase
{
    Q_OBJECT
public:
    explicit StartClose(QProcess &proc, quint32 numberOfTests, QObject *parent = nullptr);
    ~StartClose() {}

public:
    ulong currentTotalAvailableMemory() const;
    QString reportResult() override;

public slots:
    void startTest() override;
    void runCycles();

private:
    QProcess &m_procToTest;
    QStringList m_results;
    quint32 m_testCycleCount;
};

#endif // STARTCLOSE_H
