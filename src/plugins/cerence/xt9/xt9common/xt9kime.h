// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9KIME_H
#define XT9KIME_H

#include "xt9awime.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9KIme : public Xt9AwIme
{
public:
    Xt9KIme(Xt9RequestCallback *requestCallback);

    void sysInit() override;
    QString exactWord(int *wordCompLen = nullptr) override;

public:
    ET9KLingCmnInfo sKLingCmn;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9KIME_H
