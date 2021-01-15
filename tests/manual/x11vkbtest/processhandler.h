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

#ifndef PROCESSHANDLER_H
#define PROCESSHANDLER_H

#include <QObject>

class QProcess;

class ProcessHandler : public QObject
{
    Q_OBJECT
public:
    explicit ProcessHandler(QObject *parent, const QString &procPath, quint32 msec = 0);
    ~ProcessHandler();

public:
    void startProc();
    qint64 getProcId() const;
    QProcess *getPRocess() const;
    void startDetachedProc() const;

signals:
    void procReady();

public slots:
    void closeProcess();

private slots:
    void procStarted();

private:
    QProcess *m_process;
    const QString &m_procPath;
    quint32 m_msec;
};

#endif // PROCESSHANDLER_H
