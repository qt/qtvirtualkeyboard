// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9INPUTMETHOD_P_H
#define XT9INPUTMETHOD_P_H

#include <QtVirtualKeyboard/qvirtualkeyboardabstractinputmethod.h>
#include "xt9inputmethodprivate_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9InputMethod : public QVirtualKeyboardAbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Xt9InputMethod)

protected:
    Xt9InputMethod(Xt9InputMethodPrivate &dd, QObject *parent = nullptr);

public:
    void clearInputMode() override;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
