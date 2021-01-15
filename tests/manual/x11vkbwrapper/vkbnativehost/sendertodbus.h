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
