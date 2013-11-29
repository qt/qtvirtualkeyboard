/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "plaininputmethod.h"
#include "declarativeinputengine.h"
#include "declarativeinputcontext.h"

PlainInputMethod::PlainInputMethod(QObject* parent) :
    AbstractInputMethod(parent)
{
}

PlainInputMethod::~PlainInputMethod()
{
}

QList<DeclarativeInputEngine::InputMode> PlainInputMethod::inputModes(const QString& locale)
{
    Q_UNUSED(locale)
    return QList<DeclarativeInputEngine::InputMode>() << DeclarativeInputEngine::Latin << DeclarativeInputEngine::Numeric;
}

bool PlainInputMethod::setInputMode(const QString& locale, DeclarativeInputEngine::InputMode inputMode)
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

bool PlainInputMethod::keyEvent(Qt::Key key, const QString& text, Qt::KeyboardModifiers modifiers)
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
