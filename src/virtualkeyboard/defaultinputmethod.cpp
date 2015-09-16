/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

#include "defaultinputmethod.h"
#include "declarativeinputcontext.h"

DefaultInputMethod::DefaultInputMethod(QObject *parent) :
    AbstractInputMethod(parent)
{
}

QList<DeclarativeInputEngine::InputMode> DefaultInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale)
    return QList<DeclarativeInputEngine::InputMode>();
}

bool DefaultInputMethod::setInputMode(const QString &locale, DeclarativeInputEngine::InputMode inputMode)
{
    Q_UNUSED(locale)
    Q_UNUSED(inputMode)
    return true;
}

bool DefaultInputMethod::setTextCase(DeclarativeInputEngine::TextCase textCase)
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
