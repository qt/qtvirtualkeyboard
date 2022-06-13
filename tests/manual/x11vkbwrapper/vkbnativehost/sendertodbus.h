// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef SENDERTODBUS_H
#define SENDERTODBUS_H

#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtDBus/QDBusInterface>

class SenderToDbus: public QObject
{
    Q_OBJECT

public:
    explicit SenderToDbus(QObject *parent = nullptr);

private:
    //!
    //! \brief forwardMessages
    //! reads stdin where Chromium sends messages
    //! and forwards them to dbus by setting value
    //!
    void forwardMessages();

    //!
    //! \brief quit
    //! sets singleShot of timer
    //! when the application is going to quit
    //!
    Q_NOREPLY void quit();

private:
    QFile m_qstdin;
    QDBusInterface *m_iface;
};

#endif // SENDERTODBUS_H
