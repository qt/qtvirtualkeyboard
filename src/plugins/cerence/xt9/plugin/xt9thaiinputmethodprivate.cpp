// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9thaiinputmethodprivate_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Xt9ThaiInputMethodPrivate::Xt9ThaiInputMethodPrivate(Xt9ThaiInputMethod *q) :
    Xt9AwInputMethodPrivate(q, new Xt9AwIme(this), QStringLiteral("xt9aw.dlm"))
{
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
