// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef VIRTUALKEYBOARDDEBUG_H
#define VIRTUALKEYBOARDDEBUG_H

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

#include <QDebug>
#include <QLoggingCategory>
#include <private/qglobal_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Q_DECLARE_LOGGING_CATEGORY(qlcVirtualKeyboard)

// See config.pri for SENSITIVE_DEBUG.

#define VIRTUALKEYBOARD_DEBUG() qCDebug(qlcVirtualKeyboard)
#define VIRTUALKEYBOARD_WARN() qCWarning(qlcVirtualKeyboard)

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // VIRTUALKEYBOARDDEBUG_H
