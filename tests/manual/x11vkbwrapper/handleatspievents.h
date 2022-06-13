// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef HANDLEATSPIEVENTS_H
#define HANDLEATSPIEVENTS_H

#include <QObject>
#include <QList>
#include <atspi/atspi.h>

class HandleATSPIEvents : public QObject
{
    Q_OBJECT

public:
    explicit HandleATSPIEvents(QObject *parent = nullptr);
    ~HandleATSPIEvents();

    bool init();

    void gotFocusEventFromInput(const AtspiEvent *event);


private:
    void storeFocusElement(const qint8 role);
    bool isThereFocus(const qint8 role);

public slots:
    void setKeyboardVisible(const bool visible);

private:
    bool m_keyboardVisible;
    QList<qint8> m_focuses;
};

#endif // HANDLEATSPIEVENTS_H
