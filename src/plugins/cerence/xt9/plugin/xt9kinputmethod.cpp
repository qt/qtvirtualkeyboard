// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9kinputmethod_p.h"
#include "xt9kinputmethodprivate_p.h"
#include <QVirtualKeyboardInputContext>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::Xt9KInputMethod
    \internal
*/

Xt9KInputMethod::Xt9KInputMethod(QObject *parent) :
    Xt9AwInputMethod(*new Xt9KInputMethodPrivate(this), parent)
{
}

bool Xt9KInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_D(Xt9KInputMethod);
    return Xt9AwInputMethod::keyEvent(key, d->xt9Ime()->codeConverter->convertTo(text), modifiers);
}

void Xt9KInputMethod::update()
{
    Q_D(Xt9KInputMethod);

    if (d->xt9Ime()->hasActiveInput()) {
        if (d->selectionList.size() > 0) {
            d->learnWord(d->selectionList.at(0));
            d->setAutoSpaceAllowed(false);
            d->selectionListSelectItem(0);
        } else {
            inputContext()->commit();
            reset();
        }
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
