// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9KDB_H
#define XT9KDB_H

#include "xt9kdblayout.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9Kdb
{
    Q_DISABLE_COPY(Xt9Kdb)

public:
    static QByteArray generate(const Xt9KdbLayout &layout, bool prettyPrint = false);
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9KDBGENERATOR_H
