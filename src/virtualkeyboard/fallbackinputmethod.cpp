// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/fallbackinputmethod_p.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::DefaultInputMethod
    \internal
*/

FallbackInputMethod::FallbackInputMethod(QObject *parent) :
    QVirtualKeyboardAbstractInputMethod(parent)
{
}

QList<QVirtualKeyboardInputEngine::InputMode> FallbackInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale);
    return QList<QVirtualKeyboardInputEngine::InputMode>();
}

bool FallbackInputMethod::setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
{
    Q_UNUSED(locale);
    Q_UNUSED(inputMode);
    return true;
}

bool FallbackInputMethod::setTextCase(QVirtualKeyboardInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase);
    return true;
}

bool FallbackInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    const Qt::KeyboardModifiers mods = (key == Qt::Key_Return) ? Qt::NoModifier : modifiers;
    inputContext()->sendKeyClick(key, text, mods);
    return true;
}

void FallbackInputMethod::reset()
{
}

void FallbackInputMethod::update()
{
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
