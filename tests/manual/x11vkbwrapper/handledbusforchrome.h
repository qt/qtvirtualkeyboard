// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
