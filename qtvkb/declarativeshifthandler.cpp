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

#include "declarativeshifthandler.h"
#include "declarativeinputcontext.h"

class DeclarativeShiftHandlerPrivate
{
public:
    DeclarativeInputContext* inputContext;
    QString sentenceEndingCharacters;
};

/*!
    \qmltype ShiftHandler
    \inqmlmodule QtVkb 1.0
    \instantiates DeclarativeShiftHandler
    \brief Manages the shift state.
*/

/*!
    \class DeclarativeShiftHandler
    \inmodule InputFramework
    \brief Manages the shift state.
*/

DeclarativeShiftHandler::DeclarativeShiftHandler(DeclarativeInputContext* parent) :
    QObject(parent),
    d_ptr(new DeclarativeShiftHandlerPrivate())
{
    Q_D(DeclarativeShiftHandler);
    d->inputContext = parent;
    if (d->inputContext) {
        connect(d->inputContext, SIGNAL(inputMethodHintsChanged()), SLOT(restart()));
        connect(d->inputContext, SIGNAL(focusEditorChanged()), SLOT(restart()));
        connect(d->inputContext, SIGNAL(preeditTextChanged()), SLOT(autoCapitalize()));
        connect(d->inputContext, SIGNAL(cursorPositionChanged()), SLOT(autoCapitalize()));
    }
    d->sentenceEndingCharacters = ".!?";
}

/*!
    \internal
*/
DeclarativeShiftHandler::~DeclarativeShiftHandler()
{

}

QString DeclarativeShiftHandler::sentenceEndingCharacters() const
{
    Q_D(const DeclarativeShiftHandler);
    return d->sentenceEndingCharacters;
}

void DeclarativeShiftHandler::setSentenceEndingCharacters(const QString& value)
{
    Q_D(DeclarativeShiftHandler);
    if (d->sentenceEndingCharacters != value) {
        d->sentenceEndingCharacters = value;
        autoCapitalize();
        emit sentenceEndingCharactersChanged();
    }
}

void DeclarativeShiftHandler::reset()
{
    Q_D(DeclarativeShiftHandler);
    if (d->inputContext->inputItem()) {
        bool preferUpperCase = (d->inputContext->inputMethodHints() & Qt::ImhPreferUppercase);
        d->inputContext->setShift(preferUpperCase);
        d->inputContext->setCapsLock(preferUpperCase);
    }
}

void DeclarativeShiftHandler::autoCapitalize()
{
    Q_D(DeclarativeShiftHandler);
    if (!isEnabled() || d->inputContext->capsLock())
        return;
    if (!d->inputContext->preeditText().isEmpty()) {
        if (isEnabled() && !d->inputContext->capsLock()) {
            d->inputContext->setShift(false);
        }
    } else {
        int cursorPosition = d->inputContext->cursorPosition();
        bool preferLowerCase = d->inputContext->inputMethodHints() & Qt::ImhPreferLowercase;
        if (cursorPosition == 0) {
            d->inputContext->setShift(!preferLowerCase);
        } else {
            QString text = d->inputContext->surroundingText();
            text.truncate(cursorPosition);
            text = text.trimmed();
            if (text.length() == 0)
                d->inputContext->setShift(!preferLowerCase);
            else if (text.length() > 0 && d->sentenceEndingCharacters.indexOf(text[text.length() - 1]) >= 0)
                d->inputContext->setShift(!preferLowerCase);
            else
                d->inputContext->setShift(false);
        }
    }
}

void DeclarativeShiftHandler::restart()
{
    reset();
    autoCapitalize();
}

bool DeclarativeShiftHandler::isEnabled() const
{
    static const Qt::InputMethodHints disallowFlags = (Qt::ImhNoAutoUppercase | Qt::ImhUppercaseOnly| Qt::ImhLowercaseOnly |
        Qt::ImhEmailCharactersOnly | Qt::ImhUrlCharactersOnly | Qt::ImhDialableCharactersOnly |
        Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly);
    Q_D(const DeclarativeShiftHandler);
    return !(d->inputContext->inputMethodHints() & disallowFlags);
}

/*!
    \property DeclarativeShiftHandler::sentenceEndingCharacters

    This property specifies the sentence ending characters which
    will cause shift state change.

    By default, the property is initialized to sentence
    ending characters found in the ASCII range (i.e. ".!?").
*/

/*!
    \qmlproperty string ShiftHandler::sentenceEndingCharacters

    This property specifies the sentence ending characters which
    will cause shift state change.

    By default, the property is initialized to sentence
    ending characters found in the ASCII range (i.e. ".!?").
*/
