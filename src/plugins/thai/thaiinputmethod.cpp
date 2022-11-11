// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "thaiinputmethod_p.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::ThaiInputMethod
    \internal
*/

ThaiInputMethod::ThaiInputMethod(QObject *parent) :
    ThaiInputMethodBase(parent)
{
}

#ifndef QT_HUNSPELLINPUTMETHOD_LIB
QList<QVirtualKeyboardInputEngine::InputMode> ThaiInputMethod::inputModes(
        const QString &locale)
{
    Q_UNUSED(locale);
    return QList<QVirtualKeyboardInputEngine::InputMode>() << QVirtualKeyboardInputEngine::InputMode::Latin;
}

bool ThaiInputMethod::setInputMode(const QString &locale,
                                         QVirtualKeyboardInputEngine::InputMode inputMode)
{
    Q_UNUSED(locale);
    Q_UNUSED(inputMode);
    return true;
}

bool ThaiInputMethod::setTextCase(QVirtualKeyboardInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase);
    return true;
}
#endif

bool ThaiInputMethod::keyEvent(Qt::Key key,
                               const QString &text,
                               Qt::KeyboardModifiers modifiers)
{
    const bool isMark = text.size() == 2 && text.at(0) == QLatin1Char(' ');
#ifdef QT_HUNSPELLINPUTMETHOD_LIB
    if (isMark) {
        const QString mark(text.right(1));
        return ThaiInputMethodBase::keyEvent(static_cast<Qt::Key>(mark.at(0).unicode()),
                                             mark, modifiers);
    }
    return ThaiInputMethodBase::keyEvent(key, text, modifiers);
#else
    Q_UNUSED(key);
    if (isMark) {
        const QString mark(text.right(1));
        inputContext()->sendKeyClick(static_cast<Qt::Key>(mark.at(0).unicode()), mark, modifiers);
        return true;
    }
    return false;
#endif
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
