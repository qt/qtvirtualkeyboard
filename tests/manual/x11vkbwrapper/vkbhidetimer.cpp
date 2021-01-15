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

#include "vkbhidetimer.h"
#include <QGuiApplication>
#include <QTimer>
#include <QGlobalStatic>

namespace {
const quint16 KvkbCloseTimeout= 5000;
}

Q_GLOBAL_STATIC(CloseTimer,uniqueInstance)

VkbHideTimer::VkbHideTimer(QObject *parent) : QObject(parent)
{
    m_vkbHideTimer = new QTimer(this);
    m_vkbHideTimer->setInterval(KvkbCloseTimeout);
    m_vkbHideTimer->setSingleShot(true);
    QObject::connect(m_vkbHideTimer, &QTimer::timeout, this, &VkbHideTimer::closeVKB);
}

VkbHideTimer::~VkbHideTimer() {

}

VkbHideTimer* VkbHideTimer::getInstance() {
    return uniqueInstance;
}

void VkbHideTimer::startTimer() {
    m_vkbHideTimer->start();
}

void VkbHideTimer::closeVKB() const {
    QGuiApplication::inputMethod()->hide();
}
