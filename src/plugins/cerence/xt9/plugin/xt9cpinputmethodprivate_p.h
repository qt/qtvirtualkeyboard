// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9CPINPUTMETHODPRIVATE_P_H
#define XT9CPINPUTMETHODPRIVATE_P_H

#include "xt9inputmethodprivate_p.h"
#include "xt9cpinputmethod_p.h"
#include "xt9cpime.h"
#include <QMetaObject>
#include <QByteArray>
#include <QLocale>
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9CpInputMethodPrivate : public Xt9InputMethodPrivate
{
    Q_DECLARE_PUBLIC(Xt9CpInputMethod)
public:
    Xt9CpInputMethodPrivate(Xt9CpInputMethod *q_ptr);

    inline Xt9CpIme *xt9Ime() const;

    void cycleTones();
    void updatePreeditText() override;
    void selectionListSelectItem(int index) override;
    bool isValidInputChar(const QChar &c) const override;
    void reset() override;

    bool maybeInsertSpaceBeforeNextInputSymbol(QChar symbol) const override;
    ET9U32 inputModeToET9InputMode(QVirtualKeyboardInputEngine::InputMode aInputMode) const override;
};

Xt9CpIme *Xt9CpInputMethodPrivate::xt9Ime() const
{
    return static_cast<Xt9CpIme *>(_xt9Ime.data());
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9CPINPUTMETHODPRIVATE_P_H
