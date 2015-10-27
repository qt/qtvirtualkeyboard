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

#include "declarativeinputcontext.h"
#include "declarativeinputengine.h"
#include "declarativeshifthandler.h"
#include "platforminputcontext.h"
#include "virtualkeyboarddebug.h"
#include "enterkeyaction.h"
#include "settings.h"

#include <QTextFormat>
#include <QGuiApplication>
#include <QtCore/private/qobject_p.h>

#ifdef COMPILING_QML
#include <private/qqmlmetatype_p.h>
#endif

QT_BEGIN_NAMESPACE
bool operator==(const QInputMethodEvent::Attribute &attribute1, const QInputMethodEvent::Attribute &attribute2)
{
    return attribute1.start == attribute2.start &&
           attribute1.length == attribute2.length &&
           attribute1.type == attribute2.type &&
           attribute1.value == attribute2.value;
}
QT_END_NAMESPACE

/*!
    \qmlmodule QtQuick.Enterprise.VirtualKeyboard 2.0

    This module provides a collection of QML components for Qt Virtual Keyboard.
*/

/*!
    \module InputFramework

    \title Input Framework

    \brief Contains classes for integrating input methods.
*/

/*!
    \namespace QtVirtualKeyboard
    \inmodule InputFramework

    \brief Namespace for the Qt Virtual Keyboard C++ API.
*/

namespace QtVirtualKeyboard {

class DeclarativeInputContextPrivate : public QObjectPrivate
{
public:
    enum StateFlag {
        ReselectEventState = 0x1,
        InputMethodEventState = 0x2,
        KeyEventState = 0x4,
        InputMethodClickState = 0x8
    };
    Q_DECLARE_FLAGS(StateFlags, StateFlag)

    DeclarativeInputContextPrivate() :
        QObjectPrivate(),
        inputContext(0),
        inputEngine(0),
        shiftHandler(0),
        keyboardRect(),
        previewRect(),
        previewVisible(false),
        animating(false),
        focus(false),
        shift(false),
        capsLock(false),
        cursorPosition(0),
        forceCursorPosition(-1),
        inputMethodHints(Qt::ImhNone),
        preeditText(),
        preeditTextAttributes(),
        surroundingText(),
        selectedText(),
        cursorRectangle()
#ifdef QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
        , activeNavigationKeys()
#endif
    {
    }

    PlatformInputContext *inputContext;
    DeclarativeInputEngine *inputEngine;
    DeclarativeShiftHandler *shiftHandler;
    QRectF keyboardRect;
    QRectF previewRect;
    bool previewVisible;
    bool animating;
    bool focus;
    bool shift;
    bool capsLock;
    StateFlags stateFlags;
    int cursorPosition;
    int forceCursorPosition;
    Qt::InputMethodHints inputMethodHints;
    QString preeditText;
    QList<QInputMethodEvent::Attribute> preeditTextAttributes;
    QString surroundingText;
    QString selectedText;
    QRectF cursorRectangle;
#ifdef QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
    QSet<int> activeNavigationKeys;
#endif
    QSet<quint32> activeKeys;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(DeclarativeInputContextPrivate::StateFlags)

/*!
    \qmltype InputContext
    \instantiates QtVirtualKeyboard::DeclarativeInputContext
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \brief Provides access to an input context.

    The InputContext can be accessed as singleton instance.
*/

/*!
    \class QtVirtualKeyboard::DeclarativeInputContext
    \inmodule InputFramework
    \brief Provides access to an input context.
*/

/*!
    \internal
    Constructs a declarative input context with \a parent as the platform input
    context.
*/
DeclarativeInputContext::DeclarativeInputContext(PlatformInputContext *parent) :
    QObject(*new DeclarativeInputContextPrivate(), parent)
{
    Q_D(DeclarativeInputContext);
    d->inputContext = parent;
    if (d->inputContext) {
        d->inputContext->setDeclarativeContext(this);
        connect(d->inputContext, SIGNAL(focusObjectChanged()), SLOT(onInputItemChanged()));
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

void DeclarativeInputContext::setPreeditText(const QString &text, QList<QInputMethodEvent::Attribute> attributes, int replaceFrom, int replaceLength)
{
    // Add default attributes
    if (!text.isEmpty()) {
        bool containsTextFormat = false;
        for (QList<QInputMethodEvent::Attribute>::ConstIterator attribute = attributes.constBegin();
             attribute != attributes.constEnd(); attribute++) {
            if (attribute->type == QInputMethodEvent::TextFormat) {
                containsTextFormat = true;
                break;
            }
        }
        if (!containsTextFormat) {
            QTextCharFormat textFormat;
            textFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
            attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat, 0, text.length(), textFormat));
        }
    } else {
        Q_D(DeclarativeInputContext);
        if (d->forceCursorPosition != -1)
            attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::Selection, d->forceCursorPosition, 0, QVariant()));
        d->forceCursorPosition = -1;
    }

    sendPreedit(text, attributes, replaceFrom, replaceLength);
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

QRectF DeclarativeInputContext::previewRectangle() const
{
    Q_D(const DeclarativeInputContext);
    return d->previewRect;
}

void DeclarativeInputContext::setPreviewRectangle(QRectF rectangle)
{
    Q_D(DeclarativeInputContext);
    if (d->previewRect != rectangle) {
        d->previewRect = rectangle;
        emit previewRectangleChanged();
    }
}

bool DeclarativeInputContext::previewVisible() const
{
    Q_D(const DeclarativeInputContext);
    return d->previewVisible;
}

void DeclarativeInputContext::setPreviewVisible(bool visible)
{
    Q_D(DeclarativeInputContext);
    if (d->previewVisible != visible) {
        d->previewVisible = visible;
        emit previewVisibleChanged();
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

void DeclarativeInputContext::setLocale(const QString &locale)
{
    Q_D(DeclarativeInputContext);
    VIRTUALKEYBOARD_DEBUG() << "DeclarativeInputContext::setLocale():" << locale;
    QLocale newLocale(locale);
    if (newLocale != d->inputContext->locale()) {
        d->inputContext->setLocale(newLocale);
        d->inputContext->setInputDirection(newLocale.textDirection());
        emit localeChanged();
    }
}

/*!
    \internal
*/
void DeclarativeInputContext::updateAvailableLocales(const QStringList &availableLocales)
{
    Settings *settings = Settings::instance();
    if (settings)
        settings->setAvailableLocales(availableLocales);
}

QObject *DeclarativeInputContext::inputItem() const
{
    Q_D(const DeclarativeInputContext);
    return d->inputContext ? d->inputContext->focusObject() : 0;
}

DeclarativeShiftHandler *DeclarativeInputContext::shiftHandler() const
{
    Q_D(const DeclarativeInputContext);
    return d->shiftHandler;
}

DeclarativeInputEngine *DeclarativeInputContext::inputEngine() const
{
    Q_D(const DeclarativeInputContext);
    return d->inputEngine;
}

/*!
    \qmlmethod void InputContext::hideInputPanel()

    This method hides the input panel. This method should only be called
    when the user initiates the hide, e.g. by pressing a dedicated button
    on the keyboard.
*/
/*!
    This method hides the input panel. This method should only be called
    when the user initiates the hide, e.g. by pressing a dedicated button
    on the keyboard.
*/
void DeclarativeInputContext::hideInputPanel()
{
    Q_D(DeclarativeInputContext);
    d->inputContext->hideInputPanel();
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
void DeclarativeInputContext::sendKeyClick(int key, const QString &text, int modifiers)
{
    Q_D(DeclarativeInputContext);
    if (d->focus && d->inputContext) {
        QKeyEvent pressEvent(QEvent::KeyPress, key, Qt::KeyboardModifiers(modifiers), text);
        QKeyEvent releaseEvent(QEvent::KeyRelease, key, Qt::KeyboardModifiers(modifiers), text);
        VIRTUALKEYBOARD_DEBUG() << "DeclarativeInputContext::::sendKeyClick():" << key;

        d->stateFlags |= DeclarativeInputContextPrivate::KeyEventState;
        d->inputContext->sendKeyEvent(&pressEvent);
        d->inputContext->sendKeyEvent(&releaseEvent);
        if (d->activeKeys.isEmpty())
            d->stateFlags &= ~DeclarativeInputContextPrivate::KeyEventState;
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
void DeclarativeInputContext::commit(const QString &text, int replaceFrom, int replaceLength)
{
    Q_D(DeclarativeInputContext);
    VIRTUALKEYBOARD_DEBUG() << "DeclarativeInputContext::commit():" << text << replaceFrom << replaceLength;
    bool preeditChanged = !d->preeditText.isEmpty();
    d->preeditText.clear();

    if (d->inputContext) {
        QList<QInputMethodEvent::Attribute> attributes;
        if (d->forceCursorPosition != -1) {
            attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::Selection, d->forceCursorPosition, 0, QVariant()));
            d->forceCursorPosition = -1;
        }
        QInputMethodEvent inputEvent(QString(), attributes);
        inputEvent.setCommitString(text, replaceFrom, replaceLength);
        d->stateFlags |= DeclarativeInputContextPrivate::InputMethodEventState;
        d->inputContext->sendEvent(&inputEvent);
        d->stateFlags &= ~DeclarativeInputContextPrivate::InputMethodEventState;
    }

    if (preeditChanged)
        emit preeditTextChanged();
}

/*!
    \qmlmethod void InputContext::clear()

    Clears the pre-edit text.
*/
/*!
    Clears the pre-edit text.
*/
void DeclarativeInputContext::clear()
{
    Q_D(DeclarativeInputContext);
    bool preeditChanged = !d->preeditText.isEmpty();
    d->preeditText.clear();

    if (d->inputContext) {
        QList<QInputMethodEvent::Attribute> attributes;
        if (d->forceCursorPosition != -1) {
            attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::Selection, d->forceCursorPosition, 0, QVariant()));
            d->forceCursorPosition = -1;
        }
        QInputMethodEvent event(QString(), attributes);
        d->stateFlags |= DeclarativeInputContextPrivate::InputMethodEventState;
        d->inputContext->sendEvent(&event);
        d->stateFlags &= ~DeclarativeInputContextPrivate::InputMethodEventState;
    }

    if (preeditChanged)
        emit preeditTextChanged();
}

/*!
    \internal
*/
bool DeclarativeInputContext::fileExists(const QUrl &fileUrl)
{
#ifdef COMPILING_QML
    // workaround that qtquickcompiler removes *.qml file paths from qrc file (QTRD-3268)
    return QQmlMetaType::findCachedCompilationUnit(fileUrl);
#else
    QString fileName;
    if (fileUrl.scheme() == QLatin1String("qrc")) {
        fileName = QLatin1Char(':') + fileUrl.path();
    } else {
        fileName = fileUrl.toLocalFile();
    }
    return QFile(fileName).exists();
#endif
}

/*!
    \internal
*/
bool DeclarativeInputContext::hasEnterKeyAction(QObject *item) const
{
    return item != 0 && qmlAttachedPropertiesObject<EnterKeyAction>(item, false);
}

void DeclarativeInputContext::onInputItemChanged()
{
    Q_D(DeclarativeInputContext);
    if (!inputItem() && !d->activeKeys.isEmpty()) {
        // After losing keyboard focus it is impossible to track pressed keys
        d->activeKeys.clear();
        d->stateFlags &= ~DeclarativeInputContextPrivate::KeyEventState;
    }
    d->stateFlags &= ~DeclarativeInputContextPrivate::InputMethodClickState;
}

void DeclarativeInputContext::setFocus(bool enable)
{
    Q_D(DeclarativeInputContext);
    if (d->focus != enable) {
        VIRTUALKEYBOARD_DEBUG() << "DeclarativeInputContext::setFocus():" << enable;
        d->focus = enable;
        emit focusChanged();
    }
    emit focusEditorChanged();
}

void DeclarativeInputContext::sendPreedit(const QString &text, const QList<QInputMethodEvent::Attribute> &attributes, int replaceFrom, int replaceLength)
{
    Q_D(DeclarativeInputContext);
    VIRTUALKEYBOARD_DEBUG() << "DeclarativeInputContext::sendPreedit():" << text << replaceFrom << replaceLength;

    bool textChanged = d->preeditText != text;
    bool attributesChanged = d->preeditTextAttributes != attributes;

    if (textChanged || attributesChanged) {
        d->preeditText = text;
        d->preeditTextAttributes = attributes;

        if (d->inputContext) {
            QInputMethodEvent event(text, attributes);
            if (replaceFrom != 0 || replaceLength > 0)
                event.setCommitString(QString(), replaceFrom, replaceLength);
            d->stateFlags |= DeclarativeInputContextPrivate::InputMethodEventState;
            d->inputContext->sendEvent(&event);
            d->stateFlags &= ~DeclarativeInputContextPrivate::InputMethodEventState;
        }

        if (textChanged)
            emit preeditTextChanged();
    }
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
    bool newSelectedText = selectedText != d->selectedText;
    bool newCursorPosition = cursorPosition != d->cursorPosition;
    bool newCursorRectangle = cursorRectangle != d->cursorRectangle;

    // update
    d->inputMethodHints = inputMethodHints;
    d->surroundingText = surroundingText;
    d->selectedText = selectedText;
    d->cursorPosition = cursorPosition;
    d->cursorRectangle = cursorRectangle;

    // update input engine
    if ((newSurroundingText || newCursorPosition) &&
            !d->stateFlags.testFlag(DeclarativeInputContextPrivate::InputMethodEventState)) {
        d->inputEngine->update();
    }
    if (newInputMethodHints) {
        d->inputEngine->reset();
    }

    // notify
    if (newInputMethodHints) {
        emit inputMethodHintsChanged();
    }
    if (newSurroundingText) {
        emit surroundingTextChanged();
    }
    if (newSelectedText) {
        emit selectedTextChanged();
    }
    if (newCursorPosition) {
        emit cursorPositionChanged();
    }
    if (newCursorRectangle) {
        emit cursorRectangleChanged();
    }

    // word reselection
    if (newInputMethodHints || newSurroundingText || newSelectedText)
        d->stateFlags &= ~DeclarativeInputContextPrivate::InputMethodClickState;
    if ((newSurroundingText || newCursorPosition) && !newSelectedText && (int)d->stateFlags == 0 &&
            !d->inputMethodHints.testFlag(Qt::ImhNoPredictiveText) &&
            d->cursorPosition > 0 && d->selectedText.isEmpty()) {
        d->stateFlags |= DeclarativeInputContextPrivate::ReselectEventState;
        if (d->inputEngine->reselect(d->cursorPosition, DeclarativeInputEngine::WordAtCursor))
            d->stateFlags |= DeclarativeInputContextPrivate::InputMethodClickState;
        d->stateFlags &= ~DeclarativeInputContextPrivate::ReselectEventState;
    }
}

void DeclarativeInputContext::invokeAction(QInputMethod::Action action, int cursorPosition)
{
    Q_D(DeclarativeInputContext);
    switch (action) {
    case QInputMethod::Click:
        if ((int)d->stateFlags == 0) {
            bool reselect = !d->inputMethodHints.testFlag(Qt::ImhNoPredictiveText) && d->selectedText.isEmpty() && cursorPosition < d->preeditText.length();
            if (reselect) {
                d->stateFlags |= DeclarativeInputContextPrivate::ReselectEventState;
                d->forceCursorPosition = d->cursorPosition + cursorPosition;
                d->inputEngine->update();
                d->inputEngine->reselect(d->cursorPosition, DeclarativeInputEngine::WordBeforeCursor);
                d->stateFlags &= ~DeclarativeInputContextPrivate::ReselectEventState;
            } else if (!d->preeditText.isEmpty() && cursorPosition == d->preeditText.length()) {
                d->inputEngine->update();
            }
        }
        d->stateFlags &= ~DeclarativeInputContextPrivate::InputMethodClickState;
        break;

    case QInputMethod::ContextMenu:
        break;
    }
}

bool DeclarativeInputContext::filterEvent(const QEvent *event)
{
    QEvent::Type type = event->type();
    if (type == QEvent::KeyPress || type == QEvent::KeyRelease) {
        Q_D(DeclarativeInputContext);
        const QKeyEvent *keyEvent = static_cast<const QKeyEvent *>(event);

        // Keep track of pressed keys update key event state
        if (type == QEvent::KeyPress)
            d->activeKeys += keyEvent->nativeScanCode();
        else if (type == QEvent::KeyRelease)
            d->activeKeys -= keyEvent->nativeScanCode();

        if (d->activeKeys.isEmpty())
            d->stateFlags &= ~DeclarativeInputContextPrivate::KeyEventState;
        else
            d->stateFlags |= DeclarativeInputContextPrivate::KeyEventState;

#ifdef QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
        int key = keyEvent->key();
        if ((key >= Qt::Key_Left && key <= Qt::Key_Down) || key == Qt::Key_Return) {
            if (type == QEvent::KeyPress && d->inputContext->isInputPanelVisible()) {
                d->activeNavigationKeys += key;
                emit navigationKeyPressed(key, keyEvent->isAutoRepeat());
                return true;
            } else if (type == QEvent::KeyRelease && d->activeNavigationKeys.contains(key)) {
                d->activeNavigationKeys -= key;
                emit navigationKeyReleased(key, keyEvent->isAutoRepeat());
                return true;
            }
        }
#endif

        // Break composing text since the virtual keyboard does not support hard keyboard events
        if (!d->preeditText.isEmpty())
            d->inputEngine->update();
    }
    return false;
}

/*!
    \qmlproperty bool InputContext::focus

    This property is changed when the input method receives or loses focus.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::focus
    \brief the focus status.

    This property is changed when the input method receives or loses focus.
*/

/*!
    \qmlproperty bool InputContext::shift

    This property is changed when the shift status changes.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::shift
    \brief the shift status.

    This property is changed when the shift status changes.
*/

/*!
    \qmlproperty bool InputContext::capsLock

    This property is changed when the caps lock status changes.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::capsLock
    \brief the caps lock status.

    This property is changed when the caps lock status changes.
*/

/*!
    \qmlproperty int InputContext::cursorPosition

    This property is changed when the cursor position changes.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::cursorPosition
    \brief the cursor position.

    This property is changed when the cursor position changes.
*/

/*!
    \qmlproperty int InputContext::inputMethodHints

    This property is changed when the input method hints changes.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::inputMethodHints
    \brief the input method hints.

    This property is changed when the input method hints changes.
*/

/*!
    \qmlproperty string InputContext::preeditText

    This property sets the pre-edit text.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::preeditText
    \brief the pre-edit text.

    This property sets the pre-edit text.
*/

/*!
    \qmlproperty string InputContext::surroundingText

    This property is changed when the surrounding text around the cursor changes.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::surroundingText
    \brief the surrounding text around cursor.

    This property is changed when the surrounding text around the cursor changes.
*/

/*!
    \qmlproperty string InputContext::selectedText

    This property is changed when the selected text changes.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::selectedText
    \brief the selected text.

    This property is changed when the selected text changes.
*/

/*!
    \qmlproperty int InputContext::cursorRectangle

    This property is changed when the cursor rectangle changes.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::cursorRectangle
    \brief the cursor rectangle.

    This property is changed when the cursor rectangle changes.
*/

/*!
    \qmlproperty rect InputContext::keyboardRectangle

    Use this property to set the keyboard rectangle.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::keyboardRectangle
    \brief the keyboard rectangle.

    Use this property to set the keyboard rectangle.
*/

/*!
    \qmlproperty rect InputContext::previewRectangle

    Use this property to set the preview rectangle.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::previewRectangle
    \brief the preview rectangle.

    Use this property to set the preview rectangle.
*/

/*!
    \qmlproperty bool InputContext::previewVisible

    Use this property to set the visibility status of the preview.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::previewVisible
    \brief the animating status.

    Use this property to set the visibility status of the preview.
*/

/*!
    \qmlproperty bool InputContext::animating

    Use this property to set the animating status, for example
    during UI transitioning states.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::animating
    \brief the animating status.

    Use this property to set the animating status, for example
    during UI transitioning states.
*/

/*!
    \qmlproperty string InputContext::locale

    Sets the locale for this input context.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::locale
    \brief the locale.

    Sets the locale for this input context.
*/

/*!
    \qmlproperty QtObject InputContext::inputItem

    This property is changed when the focused input item changes.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::inputItem
    \brief the focused input item.

    This property is changed when the focused input item changes.
*/

/*!
    \qmlproperty ShiftHandler InputContext::shiftHandler

    This property stores the shift handler.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::shiftHandler
    \brief the shift handler instance.

    This property stores the shift handler.
*/

/*!
    \qmlproperty InputEngine InputContext::inputEngine

    This property stores the input engine.
*/

/*!
    \property QtVirtualKeyboard::DeclarativeInputContext::inputEngine
    \brief the input engine.

    This property stores the input engine.
*/

/*!
    \qmlsignal InputContext::focusEditorChanged()

    This signal is emitted when the focus editor changes.
*/

/*!
    \fn void QtVirtualKeyboard::DeclarativeInputContext::focusEditorChanged()

    This signal is emitted when the focus editor changes.
*/

/*!
    \fn void QtVirtualKeyboard::DeclarativeInputContext::navigationKeyPressed(int key, bool isAutoRepeat)
    \internal
*/

/*!
    \fn void QtVirtualKeyboard::DeclarativeInputContext::navigationKeyReleased(int key, bool isAutoRepeat)
    \internal
*/

} // namespace QtVirtualKeyboard
