// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9thaiinputmethod_p.h"
#include "xt9thaiinputmethodprivate_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::Xt9ThaiInputMethod
    \internal
*/

Xt9ThaiInputMethod::Xt9ThaiInputMethod(QObject *parent) :
    Xt9AwInputMethod(*new Xt9ThaiInputMethodPrivate(this), parent)
{
}

bool Xt9ThaiInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    const bool isMark = text.length() == 2 && text.at(0) == QLatin1Char(' ');
    if (isMark) {
        const QString mark(text.right(1));
        return Xt9AwInputMethod::keyEvent(static_cast<Qt::Key>(mark.at(0).unicode()),
                                          mark, modifiers);
    }
    return Xt9AwInputMethod::keyEvent(key, text, modifiers);
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
