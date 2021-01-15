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
