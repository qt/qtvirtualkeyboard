// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9kinputmethodprivate_p.h"
#include <QVirtualKeyboardInputContext>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Xt9KInputMethodPrivate::Xt9KInputMethodPrivate(Xt9KInputMethod *q) :
    Xt9AwInputMethodPrivate(q, new Xt9KIme(this), QStringLiteral("xt9k.dlm"))
{
}

void Xt9KInputMethodPrivate::updatePreeditText()
{
    ET9KHangulWord hangul;
    ET9STATUS eStatus = XT9_API(ET9KBuildHangul, &xt9Ime()->sLingInfo, &hangul);
    if (!eStatus && hangul.wLen) {
        Q_Q(Xt9KInputMethod);
        q->inputContext()->setPreeditText(QString::fromUtf16(reinterpret_cast<const char16_t*>(hangul.sString), hangul.wLen));
    } else {
        Xt9AwInputMethodPrivate::updatePreeditText();
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
