// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "handledbusforchrome.h"
#include "vkbhidetimer.h"

HandleDbusForChrome::HandleDbusForChrome(QObject *obj)
    : QDBusAbstractAdaptor(obj),
      m_focusValue(false)
{ }

// the property
bool HandleDbusForChrome::focusValue() const
{
    return m_focusValue;
}

void HandleDbusForChrome::setFocusValue(bool newValue)
{
    m_focusValue = newValue;
    emit showKeyboard(m_focusValue);
    VkbHideTimer::getInstance()->startTimer();
}
