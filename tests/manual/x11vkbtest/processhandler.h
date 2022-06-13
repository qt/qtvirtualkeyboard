// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
