// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/plaininputmethod_p.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::PlainInputMethod
    \internal
*/

PlainInputMethod::PlainInputMethod(QObject *parent) :
    QVirtualKeyboardAbstractInputMethod(parent)
{
}

PlainInputMethod::~PlainInputMethod()
{
}

QList<QVirtualKeyboardInputEngine::InputMode> PlainInputMethod::inputModes(const QString &locale)
{
    QList<QVirtualKeyboardInputEngine::InputMode> result;
    switch (QLocale(locale).script()) {
    case QLocale::GreekScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Greek);
        break;
    case QLocale::CyrillicScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Cyrillic);
        break;
    case QLocale::ArabicScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Arabic);
        break;
    case QLocale::HebrewScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Hebrew);
        break;
    default:
        break;
    }
    result.append(QVirtualKeyboardInputEngine::InputMode::Latin);
    result.append(QVirtualKeyboardInputEngine::InputMode::Numeric);
    return result;
}

bool PlainInputMethod::setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
{
    Q_UNUSED(locale);
    Q_UNUSED(inputMode);
    return true;
}

bool PlainInputMethod::setTextCase(QVirtualKeyboardInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase);
    return true;
}

bool PlainInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(key);
    Q_UNUSED(text);
    Q_UNUSED(modifiers);
    bool accept = false;
    return accept;
}

void PlainInputMethod::reset()
{
}

void PlainInputMethod::update()
{
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
