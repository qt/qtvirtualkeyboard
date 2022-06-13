// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef VKBHIDETIMER_H
#define VKBHIDETIMER_H

#include <QObject>

class QTimer;

class VkbHideTimer : public QObject
{
    Q_OBJECT
    friend class CloseTimer;
public:
    static VkbHideTimer *getInstance();
    virtual ~VkbHideTimer();

private:
    explicit VkbHideTimer(QObject *parent = nullptr);
    VkbHideTimer( const VkbHideTimer& ) = delete;
    VkbHideTimer& operator=( const VkbHideTimer& ) = delete;

public:
    void startTimer();

private slots:
    void closeVKB() const;

private:
    QTimer *m_vkbHideTimer;
};

class CloseTimer : public VkbHideTimer
{
};
#endif // VKBHIDETIMER_H
