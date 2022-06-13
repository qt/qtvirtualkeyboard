// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
