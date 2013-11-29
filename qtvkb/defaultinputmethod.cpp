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

#include "defaultinputmethod.h"
#include "declarativeinputcontext.h"

DefaultInputMethod::DefaultInputMethod(QObject *parent) :
    AbstractInputMethod(parent)
{
}

QList<DeclarativeInputEngine::InputMode> DefaultInputMethod::inputModes(const QString& locale)
{
    Q_UNUSED(locale)
    return QList<DeclarativeInputEngine::InputMode>();
}

bool DefaultInputMethod::setInputMode(const QString& locale, DeclarativeInputEngine::InputMode inputMode)
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

bool DefaultInputMethod::keyEvent(Qt::Key key, const QString& text, Qt::KeyboardModifiers modifiers)
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
