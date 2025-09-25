// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef RECURSIVEMETHODGUARD_P_H
#define RECURSIVEMETHODGUARD_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class RecursiveMethodGuard
{
    Q_DISABLE_COPY_MOVE(RecursiveMethodGuard)

public:
    explicit RecursiveMethodGuard(bool &flag) noexcept
        : m_flag(flag), m_acquired(!flag)
    {
        if (m_acquired)
            m_flag = true;
    }

    ~RecursiveMethodGuard() noexcept
    {
        if (m_acquired)
            m_flag = false;
    }

    [[nodiscard]] bool locked() const noexcept { return !m_acquired; }

private:
    bool &m_flag;
    const bool m_acquired;
};

}
QT_END_NAMESPACE

#endif // RECURSIVEMETHODGUARD_P_H
