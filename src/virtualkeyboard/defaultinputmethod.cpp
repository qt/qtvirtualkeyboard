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

#include "defaultinputmethod.h"
#include "inputcontext.h"

namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::DefaultInputMethod
    \internal
*/

DefaultInputMethod::DefaultInputMethod(QObject *parent) :
    AbstractInputMethod(parent)
{
}

QList<InputEngine::InputMode> DefaultInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale)
    return QList<InputEngine::InputMode>();
}

bool DefaultInputMethod::setInputMode(const QString &locale, InputEngine::InputMode inputMode)
{
    Q_UNUSED(locale)
    Q_UNUSED(inputMode)
    return true;
}

bool DefaultInputMethod::setTextCase(InputEngine::TextCase textCase)
{
    Q_UNUSED(textCase)
    return true;
}

bool DefaultInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    inputContext()->sendKeyClick(key, text, modifiers);
    return true;
}

void DefaultInputMethod::reset()
{
}

void DefaultInputMethod::update()
{
}

} // namespace QtVirtualKeyboard
