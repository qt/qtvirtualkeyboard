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
