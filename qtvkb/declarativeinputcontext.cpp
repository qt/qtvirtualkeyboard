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

#include "declarativeinputcontext.h"
#include "declarativeinputengine.h"
#include "declarativeshifthandler.h"
#include "platforminputcontext.h"
#include "vkbdebug.h"

#include <QEvent>
#include <QTextFormat>
#include <QGuiApplication>

/*!
    \qmlmodule QtVkb 1.0

    This module provides a collection of QML components for virtual keyboard.
*/

/*!
    \module InputFramework

    \title Input Framework

    \brief Contains classes for integrating input methods.
*/

class DeclarativeInputContextPrivate
{
public:
    PlatformInputContext* inputContext;
    DeclarativeInputEngine* inputEngine;
    DeclarativeShiftHandler* shiftHandler;
    QRectF keyboardRect;
    bool animating;
    bool focus;
    bool shift;
    bool capsLock;
    int cursorPosition;
    Qt::InputMethodHints inputMethodHints;
    QString preeditText;
    QString surroundingText;
    QString selectedText;
    QRectF cursorRectangle;
};

/*!
    \qmltype InputContext
    \instantiates DeclarativeInputContext
    \inqmlmodule QtVkb 1.0
    \brief Provides access to input context.

    The InputContext can be accessed as singleton instance.
*/

/*!
    \class DeclarativeInputContext
    \inmodule InputFramework
    \brief Provides access to input context.
*/

/*!
    \internal
    Constructs the declarative input context with \a parent as platform input context.
*/
DeclarativeInputContext::DeclarativeInputContext(PlatformInputContext *parent) :
    QObject(parent),
    d_ptr(new DeclarativeInputContextPrivate())
{
    Q_D(DeclarativeInputContext);
    d->inputContext = parent;
    if (d->inputContext) {
        d->inputContext->setDeclarativeContext(this);
        connect(d->inputContext, SIGNAL(focusObjectChanged()), SIGNAL(inputItemChanged()));
    }
    d->inputEngine = new DeclarativeInputEngine(this);
    d->shiftHandler = new DeclarativeShiftHandler(this);
}

/*!
    \internal
    Destroys the input context and frees all allocated resources.
*/
DeclarativeInputContext::~DeclarativeInputContext()
{
    Q_D(DeclarativeInputContext);
    if (d->inputContext)
        d->inputContext->setDeclarativeContext(0);
}

bool DeclarativeInputContext::focus() const
{
    Q_D(const DeclarativeInputContext);
    return d->focus;
}

bool DeclarativeInputContext::shift() const
{
    Q_D(const DeclarativeInputContext);
    return d->shift;
}

void DeclarativeInputContext::setShift(bool enable)
{
    Q_D(DeclarativeInputContext);
    if (d->shift != enable) {
        d->shift = enable;
        emit shiftChanged();
    }
}

bool DeclarativeInputContext::capsLock() const
{
    Q_D(const DeclarativeInputContext);
    return d->capsLock;
}

void DeclarativeInputContext::setCapsLock(bool enable)
{
    Q_D(DeclarativeInputContext);
    if (d->capsLock != enable) {
        d->capsLock = enable;
        emit capsLockChanged();
    }
}

int DeclarativeInputContext::cursorPosition() const
{
    Q_D(const DeclarativeInputContext);
    return d->cursorPosition;
}

Qt::InputMethodHints DeclarativeInputContext::inputMethodHints() const
{
    Q_D(const DeclarativeInputContext);
    return d->inputMethodHints;
}

QString DeclarativeInputContext::preeditText() const
{
    Q_D(const DeclarativeInputContext);
    return d->preeditText;
}

void DeclarativeInputContext::setPreeditText(const QString &text)
{
    Q_D(DeclarativeInputContext);
    if (text != d->preeditText)
        sendPreedit(text);
}

QString DeclarativeInputContext::surroundingText() const
{
    Q_D(const DeclarativeInputContext);
    return d->surroundingText;
}

QString DeclarativeInputContext::selectedText() const
{
    Q_D(const DeclarativeInputContext);
    return d->selectedText;
}

QRectF DeclarativeInputContext::cursorRectangle() const
{
    Q_D(const DeclarativeInputContext);
    return d->cursorRectangle;
}

QRectF DeclarativeInputContext::keyboardRectangle() const
{
    Q_D(const DeclarativeInputContext);
    return d->keyboardRect;
}

void DeclarativeInputContext::setKeyboardRectangle(QRectF rectangle)
{
    Q_D(DeclarativeInputContext);
    if (d->keyboardRect != rectangle) {
        d->keyboardRect = rectangle;
        emit keyboardRectangleChanged();
        d->inputContext->emitKeyboardRectChanged();
    }
}

bool DeclarativeInputContext::animating() const
{
    Q_D(const DeclarativeInputContext);
    return d->animating;
}

void DeclarativeInputContext::setAnimating(bool animating)
{
    Q_D(DeclarativeInputContext);
    if (d->animating != animating) {
        d->animating = animating;
        emit animatingChanged();
        d->inputContext->emitAnimatingChanged();
    }
}


QString DeclarativeInputContext::locale() const
{
    Q_D(const DeclarativeInputContext);
    return d->inputContext->locale().name();
}

void DeclarativeInputContext::setLocale(const QString& locale)
{
    Q_D(DeclarativeInputContext);
    VKB_DEBUG() << "DeclarativeInputContext::setLocale():" << locale;
    QLocale newLocale(locale);
    if (newLocale != d->inputContext->locale()) {
        d->inputContext->setLocale(newLocale);
        d->inputContext->setInputDirection(newLocale.textDirection());
        emit localeChanged();
    }
}

QObject* DeclarativeInputContext::inputItem() const
{
    Q_D(const DeclarativeInputContext);
    return d->inputContext ? d->inputContext->focusObject() : 0;
}

DeclarativeShiftHandler* DeclarativeInputContext::shiftHandler() const
{
    Q_D(const DeclarativeInputContext);
    return d->shiftHandler;
}

DeclarativeInputEngine* DeclarativeInputContext::inputEngine() const
{
    Q_D(const DeclarativeInputContext);
    return d->inputEngine;
}

/*!
    \qmlmethod void InputContext::hideInputPanel()

    This method hides the input panel. This method should only be called
    when the user initiates the hide, e.g. by pressing a dedicated button
    in keyboard.
*/
/*!
    This method hides the input panel. This method should only be called
    when the user initiates the hide, e.g. by pressing a dedicated button
    in keyboard.
*/
void DeclarativeInputContext::hideInputPanel()
{
    Q_D(DeclarativeInputContext);
    d->inputContext->hideInputPanel();
}

/*!
    \qmlmethod void InputContext::sendKeyClick(int key, string text, int modifiers = 0)

    Sends key click event to focused input item with \a key, \a text and \a modifiers.
*/
/*!
    Sends key click event to focused input item with \a key, \a text and \a modifiers.
*/
void DeclarativeInputContext::sendKeyClick(int key, const QString &text, int modifiers)
{
    Q_D(DeclarativeInputContext);
    if (d->focus && d->inputContext) {
        QKeyEvent pressEvent(QEvent::KeyPress, key, Qt::KeyboardModifiers(modifiers), text);
        QKeyEvent releaseEvent(QEvent::KeyRelease, key, Qt::KeyboardModifiers(modifiers), text);
        VKB_DEBUG() << "DeclarativeInputContext::::sendKeyClick():" << key;

        d->inputContext->sendKeyEvent(&pressEvent);
        d->inputContext->sendKeyEvent(&releaseEvent);
    } else {
        qWarning() << "DeclarativeInputContext::::sendKeyClick():" << key << "no focus";
    }
}

/*!
    \qmlmethod void InputContext::commit()

    Commits the current pre-edit text.
*/
/*!
    Commits the current pre-edit text.
*/
void DeclarativeInputContext::commit()
{
    Q_D(DeclarativeInputContext);
    QString text = d->preeditText;
    commit(text);
}

/*!
    \qmlmethod void InputContext::commit(string text, int replacementStart = 0, int replacementEnd = 0)

    Commits the final \a text to input item and optionally
    modifies the text relative to start of the pre-edit text.
    If \a replacementStart is non-zero the \a text replaces the
    contents relative to replacementStart with length of \a
    replacementLength.
*/
/*!
    Commits the final \a text to input item and optionally
    modifies the text relative to start of the pre-edit text.
    If \a replacementStart is non-zero the \a text replaces the
    contents relative to replacementStart with length of \a
    replacementLength.
*/
void DeclarativeInputContext::commit(const QString &text, int replacementStart, int replacementLength)
{
    Q_D(DeclarativeInputContext);
    VKB_DEBUG() << "DeclarativeInputContext::commit():" << text << replacementStart << replacementLength;
    bool preeditChanged = !d->preeditText.isEmpty();
    d->preeditText.clear();

    if (d->inputContext) {
        QInputMethodEvent inputEvent;
        inputEvent.setCommitString(text, replacementStart, replacementLength);
        d->inputContext->sendEvent(&inputEvent);
    }

    if (preeditChanged)
        emit preeditTextChanged();
}

/*!
    \qmlmethod void InputContext::clear()

    Clears pre-edit text.
*/
/*!
    Clears pre-edit text.
*/
void DeclarativeInputContext::clear()
{
    Q_D(DeclarativeInputContext);
    bool preeditChanged = !d->preeditText.isEmpty();
    d->preeditText.clear();

    if (d->inputContext) {
        QInputMethodEvent event;
        d->inputContext->sendEvent(&event);
    }

    if (preeditChanged)
        emit preeditTextChanged();
}

void DeclarativeInputContext::setFocus(bool enable)
{
    Q_D(DeclarativeInputContext);
    if (d->focus != enable) {
        VKB_DEBUG() << "DeclarativeInputContext::setFocus():" << enable;
        d->focus = enable;
        emit focusChanged();
    }
    emit focusEditorChanged();
}

void DeclarativeInputContext::sendPreedit(const QString &text, int cursor)
{
    Q_D(DeclarativeInputContext);
    VKB_DEBUG() << "DeclarativeInputContext::sendPreedit():" << text << cursor;
    const QString preedit = d->preeditText;
    d->preeditText = text;

    if (d->inputContext) {
        QList<QInputMethodEvent::Attribute> attributes;

        if (cursor >= 0 && cursor <= text.length()) {
            attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::Cursor, cursor, text.length(), QVariant()));
        }

        QTextCharFormat textFormat;
        textFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
        attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat, 0, text.length(), textFormat));

        QInputMethodEvent event(text, attributes);
        d->inputContext->sendEvent(&event);
    }

    if (d->preeditText != preedit)
        emit preeditTextChanged();
}

void DeclarativeInputContext::reset()
{
    Q_D(DeclarativeInputContext);
    d->inputEngine->reset();
}

void DeclarativeInputContext::externalCommit()
{
    Q_D(DeclarativeInputContext);
    d->inputEngine->update();
}

void DeclarativeInputContext::update(Qt::InputMethodQueries queries)
{
    Q_D(DeclarativeInputContext);
    Q_UNUSED(queries);

    // fetch
    Qt::InputMethodHints inputMethodHints = Qt::InputMethodHints(d->inputContext->inputMethodQuery(Qt::ImHints).toInt());
    int cursorPosition = d->inputContext->inputMethodQuery(Qt::ImCursorPosition).toInt();
    QRectF cursorRectangle = qApp->inputMethod()->cursorRectangle();
    QString surroundingText = d->inputContext->inputMethodQuery(Qt::ImSurroundingText).toString();
    QString selectedText = d->inputContext->inputMethodQuery(Qt::ImCurrentSelection).toString();

    // check against changes
    bool newInputMethodHints = inputMethodHints != d->inputMethodHints;
    bool newSurroundingText = surroundingText != d->surroundingText;
    bool newSelectedTextChange = selectedText != d->selectedText;
    bool newCursorPosition = cursorPosition != d->cursorPosition;
    bool newCursorRectangle = cursorRectangle != d->cursorRectangle;

    // update
    d->inputMethodHints = inputMethodHints;
    d->surroundingText = surroundingText;
    d->selectedText = selectedText;
    d->cursorPosition = cursorPosition;
    d->cursorRectangle = cursorRectangle;

    d->inputEngine->update();

    // notify
    if (newInputMethodHints) {
        emit inputMethodHintsChanged();
    }
    if (newSurroundingText) {
        emit surroundingTextChanged();
    }
    if (newSelectedTextChange) {
        emit selectedTextChanged();
    }
    if (newCursorPosition) {
        emit cursorPositionChanged();
    }
    if (newCursorRectangle) {
        emit cursorRectangleChanged();
    }
}

/*!
    \qmlproperty bool InputContext::focus

    This property is changed when the input method receives or loses focus.
*/

/*!
    \property DeclarativeInputContext::focus
    \brief the focus status.

    This property is changed when the input method receives or loses focus.
*/

/*!
    \qmlproperty bool InputContext::shift

    This property is changed when the shift status changes.
*/

/*!
    \property DeclarativeInputContext::shift
    \brief the shift status.

    This property is changed when the shift status changes.
*/

/*!
    \qmlproperty bool InputContext::capsLock

    This property is changed when the caps lock status changes.
*/

/*!
    \property DeclarativeInputContext::capsLock
    \brief the caps lock status.

    This property is changed when the caps lock status changes.
*/

/*!
    \qmlproperty int InputContext::cursorPosition

    This property is changed when the cursor position changes.
*/

/*!
    \property DeclarativeInputContext::cursorPosition
    \brief the cursor position.

    This property is changed when the cursor position changes.
*/

/*!
    \qmlproperty int InputContext::inputMethodHints

    This property is changed when the input method hints changes.
*/

/*!
    \property DeclarativeInputContext::inputMethodHints
    \brief the input method hints.

    This property is changed when the input method hints changes.
*/

/*!
    \qmlproperty string InputContext::preeditText

    Use this property to modify the pre-edit text.
*/

/*!
    \property DeclarativeInputContext::preeditText
    \brief the pre-edit text.

    Use this property to modify the pre-edit text.
*/

/*!
    \qmlproperty string InputContext::surroundingText

    This property is changed when the surrounding text around the cursor changes.
*/

/*!
    \property DeclarativeInputContext::surroundingText
    \brief the surrounding text around cursor.

    This property is changed when the surrounding text around the cursor changes.
*/

/*!
    \qmlproperty string InputContext::selectedText

    This property is changed when the selected text changes.
*/

/*!
    \property DeclarativeInputContext::selectedText
    \brief the selected text.

    This property is changed when the selected text changes.
*/

/*!
    \qmlproperty int InputContext::cursorRectangle

    This property is changed when the cursor rectangle changes.
*/

/*!
    \property DeclarativeInputContext::cursorRectangle
    \brief the cursor rectangle.

    This property is changed when the cursor rectangle changes.
*/

/*!
    \qmlproperty rect InputContext::keyboardRectangle

    Use this property to set keyboard rectangle.
*/

/*!
    \property DeclarativeInputContext::keyboardRectangle
    \brief the keyboard rectangle.

    Use this property to set keyboard rectangle.
*/

/*!
    \qmlproperty bool InputContext::animating

    Use this property to set the animating status, for example
    during UI transitioning states.
*/

/*!
    \property DeclarativeInputContext::animating
    \brief the animating status.

    Use this property to set the animating status, for example
    during UI transitioning states.
*/

/*!
    \qmlproperty string InputContext::locale

    Use this property to set the locale.
*/

/*!
    \property DeclarativeInputContext::locale
    \brief the locale.

    Use this property to set the locale.
*/

/*!
    \qmlproperty QtObject InputContext::inputItem

    This property is changed when the focused input item changes.
*/

/*!
    \property DeclarativeInputContext::inputItem
    \brief the focused input item.

    This property is changed when the focused input item changes.
*/

/*!
    \qmlproperty ShiftHandler InputContext::shiftHandler

    Use this property to access the shift handler.
*/

/*!
    \property DeclarativeInputContext::shiftHandler
    \brief the shift handler instance.

    Use this property to access the auto shift handler.
*/

/*!
    \qmlproperty InputEngine InputContext::inputEngine

    Use this property to access the input engine.
*/

/*!
    \property DeclarativeInputContext::inputEngine
    \brief the input engine.

    Use this property to access the input engine.
*/

/*!
    \qmlsignal InputContext::focusEditorChanged()

    This signal is emitted when the focus editor changes.
*/

/*!
    \fn void DeclarativeInputContext::focusEditorChanged()

    This signal is emitted when the focus editor changes.
*/
