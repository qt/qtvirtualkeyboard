// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QProcess>
#include <QTextStream>

#include <unistd.h>

#include "processhandler.h"

ProcessHandler::ProcessHandler(QObject *parent, const QString &procPath, quint32 msec) :
    QObject(parent),
    m_process(new QProcess(this)),
    m_procPath(procPath),
    m_msec(msec)
{
    m_process->setProgram(m_procPath);
    QObject::connect(m_process, &QProcess::started, this, &ProcessHandler::procStarted);
}

ProcessHandler::~ProcessHandler()
{
    this->closeProcess();
}

qint64 ProcessHandler::getProcId() const
{
    return m_process->processId();
}

void ProcessHandler::closeProcess()
{
    m_process->close();
}

void ProcessHandler::procStarted()
{
    if (m_msec > 0) {
        usleep(m_msec);
    }
    emit procReady();
}

void ProcessHandler::startProc()
{
    m_process->start(m_procPath);
}

void ProcessHandler::startDetachedProc() const
{
    m_process->startDetached(m_procPath);
}

QProcess* ProcessHandler::getPRocess() const {
    return m_process;
}
