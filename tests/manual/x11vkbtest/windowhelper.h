// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
