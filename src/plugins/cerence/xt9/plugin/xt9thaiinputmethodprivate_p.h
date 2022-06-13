// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9THAIINPUTMETHODPRIVATE_P_H
#define XT9THAIINPUTMETHODPRIVATE_P_H

#include "xt9awinputmethodprivate_p.h"
#include "xt9thaiinputmethod_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9ThaiInputMethodPrivate : public Xt9AwInputMethodPrivate
{
    Q_DECLARE_PUBLIC(Xt9ThaiInputMethod)
public:
    Xt9ThaiInputMethodPrivate(Xt9ThaiInputMethod *q_ptr);
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9KINPUTMETHODPRIVATE_P_H
