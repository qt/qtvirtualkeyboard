// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9JINPUTMETHODPRIVATE_P_H
#define XT9JINPUTMETHODPRIVATE_P_H

#include "xt9awinputmethodprivate_p.h"
#include "xt9jinputmethod_p.h"
#include "xt9jime.h"
#include <QMetaObject>
#include <QByteArray>
#include <QLocale>
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9JInputMethodPrivate : public Xt9AwInputMethodPrivate
{
    Q_DECLARE_PUBLIC(Xt9JInputMethod)
public:
    Xt9JInputMethodPrivate(Xt9JInputMethod *q_ptr);

    inline Xt9JIme *xt9Ime() const;

    void updateLdb() override;
    void updatePreeditText() override;
    ET9U32 inputModeToET9InputMode(QVirtualKeyboardInputEngine::InputMode aInputMode) const override;
    void reset() override;

    void setModifyKeyEnabled(bool value);

    bool isModifyKeyEnabled;
};

Xt9JIme *Xt9JInputMethodPrivate::xt9Ime() const
{
    return static_cast<Xt9JIme *>(_xt9Ime.data());
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9JINPUTMETHODPRIVATE_P_H
