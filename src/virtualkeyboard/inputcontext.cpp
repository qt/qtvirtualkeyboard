/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtVirtualKeyboard/inputcontext.h>
#include <QtVirtualKeyboard/private/inputcontext_p.h>
#include <QtVirtualKeyboard/private/shifthandler_p.h>
#include <QtVirtualKeyboard/private/platforminputcontext_p.h>
#include <QtVirtualKeyboard/private/virtualkeyboarddebug_p.h>

#include <QTextFormat>
#include <QGuiApplication>

/*!
    \namespace QtVirtualKeyboard
    \inmodule QtVirtualKeyboard

    \brief Namespace for the Qt Virtual Keyboard C++ API.
*/

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \qmltype InputContext
    \instantiates QtVirtualKeyboard::InputContext
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \brief Provides access to an input context.

    The InputContext can be accessed as singleton instance.
*/

/*!
    \class QtVirtualKeyboard::InputContext
    \inmodule QtVirtualKeyboard
    \brief Provides access to an input context.
*/

/*!
    \internal
    Constructs an input context with \a parent as the platform input
    context.
*/
InputContext::InputContext(PlatformInputContext *parent) :
    d_ptr(new InputContextPrivate(this, parent))
{
    Q_D(InputContext);
    d->init();
    QObject::connect(d->_shiftHandler, &ShiftHandler::shiftChanged, this, &InputContext::shiftChanged);
    QObject::connect(d->_shiftHandler, &ShiftHandler::capsLockChanged, this, &InputContext::capsLockChanged);
    QObject::connect(d->_shiftHandler, &ShiftHandler::uppercaseChanged, this, &InputContext::uppercaseChanged);
    QObject::connect(d, &InputContextPrivate::localeChanged, this, &InputContext::localeChanged);
}

/*!
    \internal
    Destroys the input context and frees all allocated resources.
*/
InputContext::~InputContext()
{
}

bool InputContext::shift() const
{
    Q_D(const InputContext);
    return d->_shiftHandler->shift();
}

bool InputContext::capsLock() const
{
    Q_D(const InputContext);
    return d->_shiftHandler->capsLock();
}

bool InputContext::uppercase() const
{
    Q_D(const InputContext);
    return d->_shiftHandler->uppercase();
}

int InputContext::anchorPosition() const
{
    Q_D(const InputContext);
    return d->anchorPosition;
}

int InputContext::cursorPosition() const
{
    Q_D(const InputContext);
    return d->cursorPosition;
}

Qt::InputMethodHints InputContext::inputMethodHints() const
{
    Q_D(const InputContext);
    return d->inputMethodHints;
}

QString InputContext::preeditText() const
{
    Q_D(const InputContext);
    return d->preeditText;
}

void InputContext::setPreeditText(const QString &text, QList<QInputMethodEvent::Attribute> attributes, int replaceFrom, int replaceLength)
{
    Q_D(InputContext);
    // Add default attributes
    if (!text.isEmpty()) {
        if (!d->testAttribute(attributes, QInputMethodEvent::TextFormat)) {
            QTextCharFormat textFormat;
            textFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
            attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat, 0, text.length(), textFormat));
        }
    } else if (d->_forceCursorPosition != -1) {
        d->addSelectionAttribute(attributes);
    }

    d->sendPreedit(text, attributes, replaceFrom, replaceLength);
}

QList<QInputMethodEvent::Attribute> InputContext::preeditTextAttributes() const
{
    Q_D(const InputContext);
    return d->preeditTextAttributes;
}

QString InputContext::surroundingText() const
{
    Q_D(const InputContext);
    return d->surroundingText;
}

QString InputContext::selectedText() const
{
    Q_D(const InputContext);
    return d->selectedText;
}

QRectF InputContext::anchorRectangle() const
{
    Q_D(const InputContext);
    return d->anchorRectangle;
}

QRectF InputContext::cursorRectangle() const
{
    Q_D(const InputContext);
    return d->cursorRectangle;
}

bool InputContext::animating() const
{
    Q_D(const InputContext);
    return d->animating;
}

void InputContext::setAnimating(bool animating)
{
    Q_D(InputContext);
    if (d->animating != animating) {
        VIRTUALKEYBOARD_DEBUG() << "InputContext::setAnimating():" << animating;
        d->animating = animating;
        emit animatingChanged();
        d->platformInputContext->emitAnimatingChanged();
    }
}

QString InputContext::locale() const
{
    Q_D(const InputContext);
    return d->locale();
}

InputEngine *InputContext::inputEngine() const
{
    Q_D(const InputContext);
    return d->inputEngine;
}

/*!
    \qmlmethod void InputContext::sendKeyClick(int key, string text, int modifiers = 0)

    Sends a key click event with the given \a key, \a text and \a modifiers to
    the input item that currently has focus.
*/
/*!
    Sends a key click event with the given \a key, \a text and \a modifiers to
    the input item that currently has focus.
*/
void InputContext::sendKeyClick(int key, const QString &text, int modifiers)
{
    Q_D(InputContext);
    if (d->_focus && d->platformInputContext) {
        QKeyEvent pressEvent(QEvent::KeyPress, key, Qt::KeyboardModifiers(modifiers), text);
        QKeyEvent releaseEvent(QEvent::KeyRelease, key, Qt::KeyboardModifiers(modifiers), text);
        VIRTUALKEYBOARD_DEBUG() << "InputContext::sendKeyClick():" << key;

        d->stateFlags |= InputContextPrivate::KeyEventState;
        d->platformInputContext->sendKeyEvent(&pressEvent);
        d->platformInputContext->sendKeyEvent(&releaseEvent);
        if (d->activeKeys.isEmpty())
            d->stateFlags &= ~InputContextPrivate::KeyEventState;
    } else {
        qWarning() << "InputContext::sendKeyClick(): no focus to send key click" << key << text
                   << "- QGuiApplication::focusWindow() is:" << QGuiApplication::focusWindow();
    }
}

/*!
    \qmlmethod void InputContext::commit()

    Commits the current pre-edit text.
*/
/*!
    \fn void QtVirtualKeyboard::InputContext::commit()

    Commits the current pre-edit text.
*/
void InputContext::commit()
{
    Q_D(InputContext);
    QString text = d->preeditText;
    commit(text);
}

/*!
    \qmlmethod void InputContext::commit(string text, int replaceFrom = 0, int replaceLength = 0)

    Commits the final \a text to the input item and optionally
    modifies the text relative to the start of the pre-edit text.
    If \a replaceFrom is non-zero, the \a text replaces the
    contents relative to \a replaceFrom with a length of
    \a replaceLength.
*/
/*!
    Commits the final \a text to the input item and optionally
    modifies the text relative to the start of the pre-edit text.
    If \a replaceFrom is non-zero, the \a text replaces the
    contents relative to \a replaceFrom with a length of
    \a replaceLength.
*/
void InputContext::commit(const QString &text, int replaceFrom, int replaceLength)
{
    Q_D(InputContext);
    VIRTUALKEYBOARD_DEBUG() << "InputContext::commit():" << text << replaceFrom << replaceLength;
    bool preeditChanged = !d->preeditText.isEmpty();

    if (d->platformInputContext) {
        QList<QInputMethodEvent::Attribute> attributes;
        d->addSelectionAttribute(attributes);
        d->preeditText.clear();
        d->preeditTextAttributes.clear();
        QInputMethodEvent inputEvent(QString(), attributes);
        inputEvent.setCommitString(text, replaceFrom, replaceLength);
        d->stateFlags |= InputContextPrivate::InputMethodEventState;
        d->platformInputContext->sendEvent(&inputEvent);
        d->stateFlags &= ~InputContextPrivate::InputMethodEventState;
    } else {
        d->preeditText.clear();
        d->preeditTextAttributes.clear();
    }

    if (preeditChanged)
        emit preeditTextChanged();
}

/*!
    \qmlmethod void InputContext::clear()

    Clears the pre-edit text.
*/
/*!
    \fn void QtVirtualKeyboard::InputContext::clear()

    Clears the pre-edit text.
*/
void InputContext::clear()
{
    Q_D(InputContext);
    bool preeditChanged = !d->preeditText.isEmpty();
    d->preeditText.clear();
    d->preeditTextAttributes.clear();

    if (d->platformInputContext) {
        QList<QInputMethodEvent::Attribute> attributes;
        d->addSelectionAttribute(attributes);
        QInputMethodEvent event(QString(), attributes);
        d->stateFlags |= InputContextPrivate::InputMethodEventState;
        d->platformInputContext->sendEvent(&event);
        d->stateFlags &= ~InputContextPrivate::InputMethodEventState;
    }

    if (preeditChanged)
        emit preeditTextChanged();
}

/*!
    \internal
*/
void InputContext::setSelectionOnFocusObject(const QPointF &anchorPos, const QPointF &cursorPos)
{
    QPlatformInputContext::setSelectionOnFocusObject(anchorPos, cursorPos);
}

bool InputContext::anchorRectIntersectsClipRect() const
{
    Q_D(const InputContext);
    return d->anchorRectIntersectsClipRect;
}

bool InputContext::cursorRectIntersectsClipRect() const
{
    Q_D(const InputContext);
    return d->cursorRectIntersectsClipRect;
}

bool InputContext::selectionControlVisible() const
{
    Q_D(const InputContext);
    return d->selectionControlVisible;
}

InputContextPrivate *InputContext::priv() const
{
    Q_D(const InputContext);
    return const_cast<InputContextPrivate *>(d);
}

/*!
    \qmlproperty bool InputContext::shift

    This property is changed when the shift status changes.
*/

/*!
    \property QtVirtualKeyboard::InputContext::shift
    \brief the shift status.

    This property is changed when the shift status changes.
*/

/*!
    \qmlproperty bool InputContext::capsLock

    This property is changed when the caps lock status changes.
*/

/*!
    \property QtVirtualKeyboard::InputContext::capsLock
    \brief the caps lock status.

    This property is changed when the caps lock status changes.
*/

/*!
    \qmlproperty bool InputContext::uppercase
    \since QtQuick.VirtualKeyboard 2.2

    This property is \c true when either \l shift or \l capsLock is \c true.
*/

/*!
    \property QtVirtualKeyboard::InputContext::uppercase
    \brief the uppercase status.

    This property is \c true when either \l shift or \l capsLock is \c true.
*/

/*!
    \qmlproperty int InputContext::anchorPosition
    \since QtQuick.VirtualKeyboard 2.2

    This property is changed when the anchor position changes.
*/

/*!
    \property QtVirtualKeyboard::InputContext::anchorPosition
    \brief the anchor position.

    This property is changed when the anchor position changes.
*/

/*!
    \qmlproperty int InputContext::cursorPosition

    This property is changed when the cursor position changes.
*/

/*!
    \property QtVirtualKeyboard::InputContext::cursorPosition
    \brief the cursor position.

    This property is changed when the cursor position changes.
*/

/*!
    \qmlproperty int InputContext::inputMethodHints

    This property is changed when the input method hints changes.
*/

/*!
    \property QtVirtualKeyboard::InputContext::inputMethodHints
    \brief the input method hints.

    This property is changed when the input method hints changes.
*/

/*!
    \qmlproperty string InputContext::preeditText

    This property sets the pre-edit text.
*/

/*!
    \property QtVirtualKeyboard::InputContext::preeditText
    \brief the pre-edit text.

    This property sets the pre-edit text.
*/

/*!
    \qmlproperty string InputContext::surroundingText

    This property is changed when the surrounding text around the cursor changes.
*/

/*!
    \property QtVirtualKeyboard::InputContext::surroundingText
    \brief the surrounding text around cursor.

    This property is changed when the surrounding text around the cursor changes.
*/

/*!
    \qmlproperty string InputContext::selectedText

    This property is changed when the selected text changes.
*/

/*!
    \property QtVirtualKeyboard::InputContext::selectedText
    \brief the selected text.

    This property is changed when the selected text changes.
*/

/*!
    \qmlproperty rect InputContext::anchorRectangle
    \since QtQuick.VirtualKeyboard 2.1

    This property is changed when the anchor rectangle changes.
*/

/*!
    \property QtVirtualKeyboard::InputContext::anchorRectangle
    \brief the anchor rectangle.

    This property is changed when the anchor rectangle changes.
*/

/*!
    \qmlproperty rect InputContext::cursorRectangle

    This property is changed when the cursor rectangle changes.
*/

/*!
    \property QtVirtualKeyboard::InputContext::cursorRectangle
    \brief the cursor rectangle.

    This property is changed when the cursor rectangle changes.
*/

/*!
    \qmlproperty bool InputContext::animating

    Use this property to set the animating status, for example
    during UI transitioning states.
*/

/*!
    \property QtVirtualKeyboard::InputContext::animating
    \brief the animating status.

    Use this property to set the animating status, for example
    during UI transitioning states.
*/

/*!
    \qmlproperty string InputContext::locale

    This property is changed when the input locale changes.
*/

/*!
    \property QtVirtualKeyboard::InputContext::locale
    \brief the locale.

    This property is changed when the input locale changes.
*/

/*!
    \qmlproperty InputEngine InputContext::inputEngine

    This property stores the input engine.
*/

/*!
    \property QtVirtualKeyboard::InputContext::inputEngine
    \brief the input engine.

    This property stores the input engine.
*/

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
