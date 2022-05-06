/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

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
