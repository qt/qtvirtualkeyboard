/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
