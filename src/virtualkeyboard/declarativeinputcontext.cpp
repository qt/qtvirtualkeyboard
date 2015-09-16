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

#include "declarativeinputcontext.h"
#include "declarativeinputengine.h"
#include "declarativeshifthandler.h"
#include "platforminputcontext.h"
#include "virtualkeyboarddebug.h"
#include "enterkeyaction.h"

#include <QTextFormat>
#include <QGuiApplication>
#include <QtCore/private/qobject_p.h>

#ifdef COMPILING_QML
#include <private/qqmlmetatype_p.h>
#endif

/*!
    \qmlmodule QtQuick.Enterprise.VirtualKeyboard 1.3

    This module provides a collection of QML components for Qt Virtual Keyboard.
*/

/*!
    \module InputFramework

    \title Input Framework

    \brief Contains classes for integrating input methods.
*/

class DeclarativeInputContextPrivate : public QObjectPrivate
{
public:
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
    int cursorPosition;
    Qt::InputMethodHints inputMethodHints;
    QString preeditText;
    QList<QInputMethodEvent::Attribute> preeditTextAttributes;
    QString surroundingText;
    QString selectedText;
    QRectF cursorRectangle;
#ifdef QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
    QSet<int> activeNavigationKeys;
#endif
};

/*!
    \qmltype InputContext
    \instantiates DeclarativeInputContext
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \brief Provides access to an input context.

    The InputContext can be accessed as singleton instance.
*/

/*!
    \class DeclarativeInputContext
    \inmodule InputFramework
    \ingroup qtvirtualkeyboard-qml
    \brief Provides access to an input context.
    \internal
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

void DeclarativeInputContext::setPreeditText(const QString &text, QList<QInputMethodEvent::Attribute> attributes)
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
    }

    sendPreedit(text, attributes);
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

    Commits the final \a text to the input item and optionally
    modifies the text relative to the start of the pre-edit text.
    If \a replacementStart is non-zero, the \a text replaces the
    contents relative to \a replacementStart with length of
    \a replacementLength.
*/
/*!
    Commits the final \a text to the input item and optionally
    modifies the text relative to the start of the pre-edit text.
    If \a replacementStart is non-zero, the \a text replaces the
    contents relative to \a replacementStart with length of
    \a replacementLength.
*/
void DeclarativeInputContext::commit(const QString &text, int replacementStart, int replacementLength)
{
    Q_D(DeclarativeInputContext);
    VIRTUALKEYBOARD_DEBUG() << "DeclarativeInputContext::commit():" << text << replacementStart << replacementLength;
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
        QInputMethodEvent event;
        d->inputContext->sendEvent(&event);
    }

    if (preeditChanged)
        emit preeditTextChanged();
}

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

bool DeclarativeInputContext::hasEnterKeyAction(QObject *item) const
{
    return item != 0 && qmlAttachedPropertiesObject<EnterKeyAction>(item, false);
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

bool operator==(const QInputMethodEvent::Attribute &attribute1, const QInputMethodEvent::Attribute &attribute2)
{
    return attribute1.start == attribute2.start &&
           attribute1.length == attribute2.length &&
           attribute1.type == attribute2.type &&
           attribute1.value == attribute2.value;
}

void DeclarativeInputContext::sendPreedit(const QString &text, const QList<QInputMethodEvent::Attribute> &attributes)
{
    Q_D(DeclarativeInputContext);
    VIRTUALKEYBOARD_DEBUG() << "DeclarativeInputContext::sendPreedit():" << text;

    bool textChanged = d->preeditText != text;
    bool attributesChanged = d->preeditTextAttributes != attributes;

    if (textChanged || attributesChanged) {
        d->preeditText = text;
        d->preeditTextAttributes = attributes;

        if (d->inputContext) {
            QInputMethodEvent event(text, attributes);
            d->inputContext->sendEvent(&event);
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
    bool newSelectedTextChange = selectedText != d->selectedText;
    bool newCursorPosition = cursorPosition != d->cursorPosition;
    bool newCursorRectangle = cursorRectangle != d->cursorRectangle;

    // update
    d->inputMethodHints = inputMethodHints;
    d->surroundingText = surroundingText;
    d->selectedText = selectedText;
    d->cursorPosition = cursorPosition;
    d->cursorRectangle = cursorRectangle;

    // update input engine
    if (newSurroundingText || newCursorPosition) {
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

bool DeclarativeInputContext::filterEvent(const QEvent *event)
{
#ifdef QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        Q_D(DeclarativeInputContext);
        const QKeyEvent *keyEvent = static_cast<const QKeyEvent *>(event);
        int key = keyEvent->key();
        if ((key >= Qt::Key_Left && key <= Qt::Key_Down) || key == Qt::Key_Return) {
            if (event->type() == QEvent::KeyPress && d->inputContext->isInputPanelVisible()) {
                d->activeNavigationKeys += key;
                emit navigationKeyPressed(key, keyEvent->isAutoRepeat());
                return true;
            } else if (event->type() == QEvent::KeyRelease && d->activeNavigationKeys.contains(key)) {
                d->activeNavigationKeys -= key;
                emit navigationKeyReleased(key, keyEvent->isAutoRepeat());
                return true;
            }
        }
    }
#else
    Q_UNUSED(event)
#endif
    return false;
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

    This property sets the pre-edit text.
*/

/*!
    \property DeclarativeInputContext::preeditText
    \brief the pre-edit text.

    This property sets the pre-edit text.
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

    Use this property to set the keyboard rectangle.
*/

/*!
    \property DeclarativeInputContext::keyboardRectangle
    \brief the keyboard rectangle.

    Use this property to set the keyboard rectangle.
*/

/*!
    \qmlproperty rect InputContext::previewRectangle

    Use this property to set the preview rectangle.
*/

/*!
    \property DeclarativeInputContext::previewRectangle
    \brief the preview rectangle.

    Use this property to set the preview rectangle.
*/

/*!
    \qmlproperty bool InputContext::previewVisible

    Use this property to set the visibility status of the preview.
*/

/*!
    \property DeclarativeInputContext::previewVisible
    \brief the animating status.

    Use this property to set the visibility status of the preview.
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

    Sets the locale for this input context.
*/

/*!
    \property DeclarativeInputContext::locale
    \brief the locale.

    Sets the locale for this input context.
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

    This property stores the shift handler.
*/

/*!
    \property DeclarativeInputContext::shiftHandler
    \brief the shift handler instance.

    This property stores the shift handler.
*/

/*!
    \qmlproperty InputEngine InputContext::inputEngine

    This property stores the input engine.
*/

/*!
    \property DeclarativeInputContext::inputEngine
    \brief the input engine.

    This property stores the input engine.
*/

/*!
    \qmlsignal InputContext::focusEditorChanged()

    This signal is emitted when the focus editor changes.
*/

/*!
    \fn void DeclarativeInputContext::focusEditorChanged()

    This signal is emitted when the focus editor changes.
*/
