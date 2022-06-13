// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9inputmethod_p.h"
#include "xt9inputmethodprivate_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::Xt9InputMethod
    \internal
*/

Xt9InputMethod::Xt9InputMethod(Xt9InputMethodPrivate &dd, QObject *parent) :
    QVirtualKeyboardAbstractInputMethod(dd, parent)
{
    Q_D(Xt9InputMethod);
    d->sysInit();
}

void Xt9InputMethod::clearInputMode()
{
    qCDebug(lcXT9) << "clearInputMode";
    Q_D(Xt9InputMethod);
    d->uninit();
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
