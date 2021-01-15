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

#ifndef WINDOWHELPER_H
#define WINDOWHELPER_H

#include <QObject>

extern "C" {
#include <xdo.h>
}

class WindowHelper : public QObject
{
    Q_OBJECT
public:
    explicit WindowHelper(QObject *parent = nullptr);
    ~WindowHelper();

public:
    Window findWindowByPid(const qint64 appPid) const;
    QPair<quint16, quint16> getWindowDimension(const Window winId) const;

private:
    /** Libxdo context. */
    xdo_t *m_xdo;
};

#endif // WINDOWHELPER_H
