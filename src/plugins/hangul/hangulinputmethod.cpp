// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "hangulinputmethod_p.h"
#include "hangul_p.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::HangulInputMethod
    \internal
*/

HangulInputMethod::HangulInputMethod(QObject *parent) :
    QVirtualKeyboardAbstractInputMethod(parent)
{
}

HangulInputMethod::~HangulInputMethod()
{
}

QList<QVirtualKeyboardInputEngine::InputMode> HangulInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale);
    return QList<QVirtualKeyboardInputEngine::InputMode>() << QVirtualKeyboardInputEngine::InputMode::Hangul;
}

bool HangulInputMethod::setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
{
    Q_UNUSED(locale);
    Q_UNUSED(inputMode);
    return true;
}

bool HangulInputMethod::setTextCase(QVirtualKeyboardInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase);
    return true;
}

bool HangulInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);
    QVirtualKeyboardInputContext *ic = inputContext();
    bool accept = false;
    int cursorPosition = ic->cursorPosition();
    if (ic->cursorPosition() > 0) {
        if (key == Qt::Key_Backspace) {
            int contextLength = cursorPosition > 1 ? 2 : 1;
            QString hangul = Hangul::decompose(ic->surroundingText().mid(cursorPosition - contextLength, contextLength));
            int length = hangul.size();
            if (hangul.size() > 1) {
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
QT_END_NAMESPACE
