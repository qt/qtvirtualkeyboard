/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include "hangulinputmethod.h"
#include "declarativeinputcontext.h"
#include "hangul.h"

namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::HangulInputMethod
    \internal
*/

HangulInputMethod::HangulInputMethod(QObject *parent) :
    AbstractInputMethod(*new AbstractInputMethodPrivate(), parent)
{
}

HangulInputMethod::~HangulInputMethod()
{
}

QList<DeclarativeInputEngine::InputMode> HangulInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale)
    return QList<DeclarativeInputEngine::InputMode>() << DeclarativeInputEngine::Hangul;
}

bool HangulInputMethod::setInputMode(const QString &locale, DeclarativeInputEngine::InputMode inputMode)
{
    Q_UNUSED(locale)
    Q_UNUSED(inputMode)
    return true;
}

bool HangulInputMethod::setTextCase(DeclarativeInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase)
    return true;
}

bool HangulInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers)
    DeclarativeInputContext *ic = inputContext();
    bool accept = false;
    int cursorPosition = ic->cursorPosition();
    if (ic->cursorPosition() > 0) {
        if (key == Qt::Key_Backspace) {
            int contextLength = cursorPosition > 1 ? 2 : 1;
            QString hangul = Hangul::decompose(ic->surroundingText().mid(cursorPosition - contextLength, contextLength));
            int length = hangul.length();
            if (hangul.length() > 1) {
                ic->commit(Hangul::compose(hangul.left(length - 1)), -contextLength, contextLength);
                accept = true;
            }
        } else if (!text.isEmpty() && Hangul::isJamo(text.at(0).unicode())) {
            QString hangul = Hangul::compose(ic->surroundingText().mid(cursorPosition - 1, 1) + text);
            ic->commit(hangul, -1, 1);
            accept = true;
        }
    }
    return accept;
}

void HangulInputMethod::reset()
{
}

void HangulInputMethod::update()
{
}

} // namespace QtVirtualKeyboard
