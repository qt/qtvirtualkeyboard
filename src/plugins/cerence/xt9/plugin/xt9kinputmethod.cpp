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
        if (d->selectionList.length() > 0) {
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
