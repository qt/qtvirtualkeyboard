// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9KINPUTMETHODPRIVATE_P_H
#define XT9KINPUTMETHODPRIVATE_P_H

#include "xt9awinputmethodprivate_p.h"
#include "xt9kinputmethod_p.h"
#include "xt9kime.h"
#include <QMetaObject>
#include <QByteArray>
#include <QLocale>
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9KInputMethodPrivate : public Xt9AwInputMethodPrivate
{
    Q_DECLARE_PUBLIC(Xt9KInputMethod)
public:
    Xt9KInputMethodPrivate(Xt9KInputMethod *q_ptr);

    inline Xt9KIme *xt9Ime() const;

    void updatePreeditText();
};

Xt9KIme *Xt9KInputMethodPrivate::xt9Ime() const
{
    return static_cast<Xt9KIme *>(_xt9Ime.data());
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9KINPUTMETHODPRIVATE_P_H
