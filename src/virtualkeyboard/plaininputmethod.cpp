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

#include "plaininputmethod.h"
#include "declarativeinputengine.h"
#include "declarativeinputcontext.h"

PlainInputMethod::PlainInputMethod(QObject *parent) :
    AbstractInputMethod(parent)
{
}

PlainInputMethod::~PlainInputMethod()
{
}

QList<DeclarativeInputEngine::InputMode> PlainInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale)
    // Supports all input modes
    return QList<DeclarativeInputEngine::InputMode>()
            << DeclarativeInputEngine::Latin
            << DeclarativeInputEngine::Numeric
            << DeclarativeInputEngine::Dialable
            << DeclarativeInputEngine::Pinyin;
}

bool PlainInputMethod::setInputMode(const QString &locale, DeclarativeInputEngine::InputMode inputMode)
{
    Q_UNUSED(locale)
    Q_UNUSED(inputMode)
    return true;
}

bool PlainInputMethod::setTextCase(DeclarativeInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase)
    return true;
}

bool PlainInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(key)
    Q_UNUSED(text)
    Q_UNUSED(modifiers)
    bool accept = false;
    return accept;
}

void PlainInputMethod::reset()
{
}

void PlainInputMethod::update()
{
}
