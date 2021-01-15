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

#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>
#include "testbase.h"

class TestBase;

class TestThread : public QThread
{
    Q_OBJECT
public:
    explicit TestThread(const QString &x11vkbPath, quint32 startCloseTest, quint32 keyOperationTest, quint32 langChangeTest, QObject *parent = nullptr);

public:
    void run() override;

signals:
    void resultReady(const QString &s);
    void processID(const qint64 procID);
    void startMemoryMonitor();

private:
    const QString &m_x11vkbPath;
    quint32 m_numberOfStartClose;
    quint32 m_numberOfKeyOperation;
    quint32 m_numberOfLangChange;
};

#endif // TESTTHREAD_H
