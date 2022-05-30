/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

#include <QtVirtualKeyboard/private/enterkeyactionattachedtype_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::EnterKeyActionAttachedType
    \internal
*/

EnterKeyActionAttachedType::EnterKeyActionAttachedType(QObject *parent) :
    QObject(parent),
    m_actionId(EnterKeyAction::None),
    m_label(),
    m_enabled(true)
{
}

int EnterKeyActionAttachedType::actionId() const
{
    return m_actionId;
}

void EnterKeyActionAttachedType::setActionId(int actionId)
{
    if (m_actionId != actionId) {
        m_actionId = actionId;
        emit actionIdChanged();
    }
}

QString EnterKeyActionAttachedType::label() const
{
    return m_label;
}

void EnterKeyActionAttachedType::setLabel(const QString& label)
{
    if (m_label != label) {
        m_label = label;
        emit labelChanged();
    }
}

bool EnterKeyActionAttachedType::enabled() const
{
    return m_enabled;
}

void EnterKeyActionAttachedType::setEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        emit enabledChanged();
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
