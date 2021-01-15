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

#ifndef HANDLEDBUSFORCHROME_H
#define HANDLEDBUSFORCHROME_H

#include <QtCore/QObject>
#include <QtDBus/QDBusAbstractAdaptor>
#include "common_defs.h"

class HandleDbusForChrome: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", SERVICE_NAME)
    Q_PROPERTY(bool focusValue READ focusValue WRITE setFocusValue)

public:
    HandleDbusForChrome(QObject *obj);

    bool focusValue() const;
    void setFocusValue(bool newValue);

signals:
    //!
    //! \brief showKeyboard
    //! signal for request by param value to popup or hide keyboard.
    //! it is sent when setValue is called via dbus
    //! \param bool focusValue
    //!
    void showKeyboard(bool focusValue);

private:
    bool m_focusValue;

};

#endif // HANDLEDBUSFORCHROME_H
