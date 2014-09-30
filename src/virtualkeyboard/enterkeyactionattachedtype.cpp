/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

#include "enterkeyactionattachedtype.h"

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
