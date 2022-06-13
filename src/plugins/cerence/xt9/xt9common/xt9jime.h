// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9JIME_H
#define XT9JIME_H

#include "xt9awime.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9JIme : public Xt9AwIme
{
public:
    Xt9JIme(Xt9RequestCallback *requestCallback);
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9JIME_H
