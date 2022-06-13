// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCore/QFile>
#include <QtDBus/QtDBus>

#include "sendertodbus.h"
#include "common_defs.h"

namespace  {
//!
//! \brief msgLengthBytes, Chromium sends first 4 bytes as a length of coming message
//!
const qint8 msgLengthBytes = 4;

//!
//! \brief msgLength, Chromium sends next 1 byte as a true/false to popup/hide virtual keyboard
//!
const qint8 msgLength = 1;
}



SenderToDbus::SenderToDbus(QObject *parent)
    : QObject(parent),
      m_iface(nullptr)
{
    m_iface = new QDBusInterface(SERVICE_NAME, "/", "",
                               QDBusConnection::sessionBus(), this);
    if (!m_iface->isValid()) {
        QCoreApplication::quit();
    }

    this->forwardMessages();
}

void SenderToDbus::forwardMessages()
{
    m_qstdin.open(stdin, QIODevice::ReadOnly);

    while (true)
    {
        // Read the message length (first 4 bytes)
        QByteArray byteCount = m_qstdin.read(msgLengthBytes);

        //When Chromium closes stdin is closed
        if (byteCount.count() == 0)
        {
            // before exit, send false to hide keyboard
            m_iface->setProperty("focusValue", false);
            this->quit();
            return;
        }

        QByteArray value = m_qstdin.read(msgLength);
        m_iface->setProperty("focusValue", value == "1");
    };
}


void SenderToDbus::quit()
{
    QTimer::singleShot(0, QCoreApplication::instance(), &QCoreApplication::quit);
}
