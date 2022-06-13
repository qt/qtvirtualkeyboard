// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
