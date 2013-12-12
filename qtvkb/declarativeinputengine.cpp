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

#include "declarativeinputengine.h"
#include "declarativeinputcontext.h"
#include "defaultinputmethod.h"
#include "vkbdebug.h"

#include <QTimerEvent>

class DeclarativeInputEnginePrivate
{
public:
    virtual ~DeclarativeInputEnginePrivate() { }
    DeclarativeInputContext* inputContext;
    QPointer<AbstractInputMethod> inputMethod;
    AbstractInputMethod* defaultInputMethod;
    DeclarativeInputEngine::TextCase textCase;
    DeclarativeInputEngine::InputMode inputMode;
    QMap<DeclarativeSelectionListModel::Type, DeclarativeSelectionListModel*> selectionListModels;
    Qt::Key activeKey;
    QString activeKeyText;
    Qt::KeyboardModifiers activeKeyModifiers;
    Qt::Key previousKey;
    int repeatTimer;
    int repeatCount;
    int recursiveMethodLock;
};

class RecursiveMethodGuard
{
public:
    explicit RecursiveMethodGuard(int& ref) : m_ref(ref)
    {
        m_ref++;
    }
    ~RecursiveMethodGuard()
    {
        m_ref--;
    }
    bool locked() const
    {
        return m_ref > 1;
    }
private:
    int& m_ref;
};

/*!
    \qmltype InputEngine
    \inqmlmodule QtVkb 1.0
    \instantiates DeclarativeInputEngine
    \brief The InputEngine provides access to input methods.

    The input engine is responsible for routing input events to input
    method. The actual input logic is implemented by the input methods.

    The input engine also includes the default input method, which takes
    care of default processing if the active input method does not handle
    the event.
*/

/*!
    \class DeclarativeInputEngine
    \inmodule InputFramework
    \brief The DeclarativeInputEngine class specifies an input engine
    that supports C++ and QML integration.

    The input engine is responsible for routing input events to input
    method. The actual input logic is implemented by the input methods.

    The input engine also includes the default input method, which takes
    care of default processing if the active input method does not handle
    the event.
*/

/*!
    \internal
    Constructs an input engine with input context as \a parent.
*/
DeclarativeInputEngine::DeclarativeInputEngine(DeclarativeInputContext* parent) :
    QObject(parent),
    d_ptr(new DeclarativeInputEnginePrivate())
{
    Q_D(DeclarativeInputEngine);
    d->inputContext = parent;
    if (d->inputContext) {
        connect(d->inputContext, SIGNAL(shiftChanged()), SLOT(shiftChanged()));
        connect(d->inputContext, SIGNAL(localeChanged()), SLOT(localeChanged()));
    }
    d->defaultInputMethod = new DefaultInputMethod(this);
    if (d->defaultInputMethod)
        d->defaultInputMethod->setInputEngine(this);
    d->textCase = Lower;
    d->inputMode = Latin;
    d->activeKey = Qt::Key_unknown;
    d->previousKey = Qt::Key_unknown;
}

/*!
    \internal
    Destroys the input engine and frees all allocated resources.
*/
DeclarativeInputEngine::~DeclarativeInputEngine()
{
}

/*!
    \qmlmethod bool InputEngine::virtualKeyPress(int key, string text, int modifiers, bool repeat)

    Called by keyboard layer to indicate \a key press with \a text and \a
    modifiers.

    The \a key is set as an active key (down key). The actual key event is
    triggered when the key is released by virtualKeyRelease() method. The key
    press event can be discarded by calling virtualKeyCancel() method.

    The key press also initiates the key repeat timer if \a repeat is true.

    Returns true if the key was accepted by input engine.

    \sa virtualKeyCancel(), virtualKeyRelease()
*/
/*!
    Called by keyboard layer to indicate \a key press with \a text and \a
    modifiers.

    The \a key is set as an active key (down key). The actual key event is
    triggered when the key is released by virtualKeyRelease() method. The key
    press event can be discarded by calling virtualKeyCancel() method.

    The key press also initiates the key repeat timer if \a repeat is true.

    Returns true if the key was accepted by input engine.

    \sa virtualKeyCancel(), virtualKeyRelease()
*/
bool DeclarativeInputEngine::virtualKeyPress(Qt::Key key, const QString& text, Qt::KeyboardModifiers modifiers, bool repeat)
{
    Q_D(DeclarativeInputEngine);
    VKB_DEBUG() << "DeclarativeInputEngine::virtualKeyPress():" << key << text << modifiers << repeat;
    bool accept = false;
    if (d->activeKey == Qt::Key_unknown || d->activeKey == key) {
        d->activeKey = key;
        d->activeKeyText = text;
        d->activeKeyModifiers = modifiers;
        if (repeat) {
            d->repeatTimer = startTimer(600);
        }
        accept = true;
        emit activeKeyChanged(d->activeKey);
    } else {
        qWarning("key press ignored; key is already active");
    }
    return accept;
}

/*!
    \qmlmethod void InputEngine::virtualKeyCancel()

    Reverts the active key state without emitting the key event.
    This method is useful when the user discards the current key and
    the key state needs to be restored.
*/
/*!
    Reverts the active key state without emitting the key event.
    This method is useful when the user discards the current key and
    the key state needs to be restored.
*/
void DeclarativeInputEngine::virtualKeyCancel()
{
    Q_D(DeclarativeInputEngine);
    VKB_DEBUG() << "DeclarativeInputEngine::virtualKeyCancel()";
    if (d->activeKey != Qt::Key_unknown) {
        d->activeKey = Qt::Key_unknown;
        d->activeKeyText = QString();
        d->activeKeyModifiers = Qt::KeyboardModifiers();
        if (d->repeatTimer) {
            killTimer(d->repeatTimer);
            d->repeatTimer = 0;
            d->repeatCount = 0;
        }
        emit activeKeyChanged(d->activeKey);
    }
}

/*!
    \qmlmethod bool InputEngine::virtualKeyRelease(int key, string text, int modifiers)

    Releases the \a key. The method emits key event for input method
    if the events has not been generated by repeating timer.
    The \a text and \a modifiers are passed on input method.

    Returns true if the key was accepted by the input engine.
*/
/*!
    Releases the \a key. The method emits key event for input method
    if the events has not been generated by repeating timer.
    The \a text and \a modifiers are passed on input method.

    Returns true if the key was accepted by the input engine.
*/
bool DeclarativeInputEngine::virtualKeyRelease(Qt::Key key, const QString& text, Qt::KeyboardModifiers modifiers)
{
    Q_D(DeclarativeInputEngine);
    VKB_DEBUG() << "DeclarativeInputEngine::virtualKeyRelease():" << key << text << modifiers;
    bool accept = false;
    if (d->activeKey == key) {
        if (!d->repeatCount) {
            accept = virtualKeyClick(key, text, modifiers);
        } else {
            accept = true;
        }
    } else {
        qWarning("key release ignored; key is not pressed");
    }
    if (d->activeKey != Qt::Key_unknown) {
        d->previousKey = d->activeKey;
        emit previousKeyChanged(d->previousKey);
        d->activeKey = Qt::Key_unknown;
        d->activeKeyText = QString();
        d->activeKeyModifiers = Qt::KeyboardModifiers();
        if (d->repeatTimer) {
            killTimer(d->repeatTimer);
            d->repeatTimer = 0;
            d->repeatCount = 0;
        }
        emit activeKeyChanged(d->activeKey);
    }
    return accept;
}

/*!
    \qmlmethod bool InputEngine::virtualKeyClick(int key, string text, int modifiers)

    Emits \a key event for input method with \a text and \a modifiers.
    Returns true if the key event was accepted by the input engine.
*/
/*!
    Emits \a key event for input method with \a text and \a modifiers.
    Returns true if the key event was accepted by the input engine.
*/
bool DeclarativeInputEngine::virtualKeyClick(Qt::Key key, const QString& text, Qt::KeyboardModifiers modifiers)
{
    Q_D(DeclarativeInputEngine);
    bool accept = false;
    if (d->inputMethod) {
        RecursiveMethodGuard guard(d->recursiveMethodLock);
        if (!guard.locked()) {
            accept = d->inputMethod->keyEvent(key, text, modifiers);
            if (!accept) {
                accept = d->defaultInputMethod->keyEvent(key, text, modifiers);
            }
            emit virtualKeyClicked(key, text, modifiers);
        }
    } else {
        qWarning() << "input method is not set";
    }
    return accept;
}

/*!
    Returns \c DeclarativeInputContext instance associated with the input engine.
*/
DeclarativeInputContext* DeclarativeInputEngine::inputContext() const
{
    Q_D(const DeclarativeInputEngine);
    return d->inputContext;
}

/*!
    Returns currently active key, or Qt::Key_unknown if no key is active.
*/
Qt::Key DeclarativeInputEngine::activeKey() const
{
    Q_D(const DeclarativeInputEngine);
    return d->activeKey;
}

/*!
    Returns previous active key, or Qt::Key_unknown if no key has been active.
*/
Qt::Key DeclarativeInputEngine::previousKey() const
{
    Q_D(const DeclarativeInputEngine);
    return d->previousKey;
}

/*!
    Returns the current active input method.
*/
AbstractInputMethod* DeclarativeInputEngine::inputMethod() const
{
    Q_D(const DeclarativeInputEngine);
    return d->inputMethod;
}

/*!
    Sets the \a inputMethod as an active input method.
*/
void DeclarativeInputEngine::setInputMethod(AbstractInputMethod* inputMethod)
{
    Q_D(DeclarativeInputEngine);
    VKB_DEBUG() << "DeclarativeInputEngine::setInputMethod():" << inputMethod;
    if (!d->inputMethod || !inputMethod || d->inputMethod->className() != inputMethod->className()) {
        update();
        if (d->inputMethod) {
            d->inputMethod->setInputEngine(0);
        }
        d->inputMethod = inputMethod;
        if (d->inputMethod) {
            d->inputMethod->setInputEngine(this);

            // Allocate selection lists for the input method
            QList<DeclarativeSelectionListModel::Type> activeSelectionLists = d->inputMethod->selectionLists();
            QList<DeclarativeSelectionListModel::Type> inactiveSelectionLists = d->selectionListModels.keys();
            foreach (const DeclarativeSelectionListModel::Type& selectionListType, activeSelectionLists) {
                if (!d->selectionListModels.contains(selectionListType)) {
                    d->selectionListModels[selectionListType] = new DeclarativeSelectionListModel(this);
                    if (selectionListType == DeclarativeSelectionListModel::WordCandidateList) {
                        emit wordCandidateListModelChanged();
                    }
                }
                d->selectionListModels[selectionListType]->setDataSource(inputMethod, selectionListType);
                if (selectionListType == DeclarativeSelectionListModel::WordCandidateList) {
                    emit wordCandidateListVisibleHintChanged();
                }
                inactiveSelectionLists.removeAll(selectionListType);
            }

            // Deallocate inactive selection lists
            foreach (const DeclarativeSelectionListModel::Type& selectionListType, inactiveSelectionLists) {
                if (d->selectionListModels.contains(selectionListType)) {
                    d->selectionListModels[selectionListType]->setDataSource(0, selectionListType);
                    if (selectionListType == DeclarativeSelectionListModel::WordCandidateList) {
                        emit wordCandidateListVisibleHintChanged();
                    }
                }
            }
        }
        emit inputMethodChanged();
        emit inputModesChanged();
    }
}

/*!
    Returns lisf of available input modes.
*/
QList<int> DeclarativeInputEngine::inputModes() const
{
    Q_D(const DeclarativeInputEngine);
    QList<InputMode> inputModeList;
    if (d->inputMethod) {
        inputModeList = d->inputMethod->inputModes(d->inputContext->locale());
    }
    if (inputModeList.isEmpty()) {
        return QList<int>();
    }
    QList<int> resultList;
    foreach (const InputMode& inputMode, inputModeList) {
        resultList.append(inputMode);
    }
    return resultList;
}

DeclarativeInputEngine::InputMode DeclarativeInputEngine::inputMode() const
{
    Q_D(const DeclarativeInputEngine);
    return d->inputMode;
}

void DeclarativeInputEngine::setInputMode(DeclarativeInputEngine::InputMode inputMode)
{
    Q_D(DeclarativeInputEngine);
    VKB_DEBUG() << "DeclarativeInputEngine::setInputMode():" << inputMode;
    if (d->inputMethod) {
        const QString locale(d->inputContext->locale());
        QList<DeclarativeInputEngine::InputMode> inputModeList(d->inputMethod->inputModes(locale));
        if (inputModeList.contains(inputMode)) {
            d->inputMethod->setInputMode(locale, d->inputMode);
            d->inputMode = inputMode;
            emit inputModeChanged();
        } else {
            qWarning() << "the input mode" << inputMode << "is not valid";
        }
    }
}

DeclarativeSelectionListModel* DeclarativeInputEngine::wordCandidateListModel() const
{
    Q_D(const DeclarativeInputEngine);
    return d->selectionListModels[DeclarativeSelectionListModel::WordCandidateList];
}

bool DeclarativeInputEngine::wordCandidateListVisibleHint() const
{
    Q_D(const DeclarativeInputEngine);
    if (!d->selectionListModels.contains(DeclarativeSelectionListModel::WordCandidateList))
        return false;
    return d->selectionListModels[DeclarativeSelectionListModel::WordCandidateList]->dataSource() != 0;
}

/*!
    \internal
    Resets input method.
*/
void DeclarativeInputEngine::reset()
{
    Q_D(DeclarativeInputEngine);
    if (d->inputMethod) {
        RecursiveMethodGuard guard(d->recursiveMethodLock);
        if (!guard.locked()) {
            emit inputMethodReset();
        }
    }
}

/*!
    \internal
    Updates input method state. This method is called when ever the input context is changed.
*/
void DeclarativeInputEngine::update()
{
    Q_D(DeclarativeInputEngine);
    if (d->inputMethod) {
        RecursiveMethodGuard guard(d->recursiveMethodLock);
        if (!guard.locked()) {
            emit inputMethodUpdate();
        }
    }
}

/*!
    \internal
    Updates text case for input method.
*/
void DeclarativeInputEngine::shiftChanged()
{
    Q_D(DeclarativeInputEngine);
    TextCase newCase = d->inputContext->shift() ? Upper : Lower;
    if (d->textCase == newCase) {
        d->textCase = newCase;
        if (d->inputMethod) {
            d->inputMethod->setTextCase(d->textCase);
        }
    }
}

/*!
    \internal
    Updates input mode when locale changes.
*/
void DeclarativeInputEngine::localeChanged()
{
    Q_D(DeclarativeInputEngine);
    update();
    setInputMode(d->inputMode);
}

/*!
    \internal
*/
void DeclarativeInputEngine::timerEvent(QTimerEvent* timerEvent)
{
    Q_D(DeclarativeInputEngine);
    if (timerEvent->timerId() == d->repeatTimer) {
        d->repeatTimer = 0;
        virtualKeyClick(d->activeKey, d->activeKeyText, d->activeKeyModifiers);
        d->repeatTimer = startTimer(50);
        d->repeatCount++;
    }
}

/*!
    \qmlproperty int InputEngine::activeKey

    Currently pressed key.
*/

/*!
    \property DeclarativeInputEngine::activeKey
    \brief the active key.

    Currently pressed key.
*/

/*!
    \qmlproperty int InputEngine::previousKey

    Previous pressed key.
*/
/*!
    \property DeclarativeInputEngine::previousKey
    \brief the previous active key.

    Previous pressed key.
*/

/*!
    \qmlproperty InputMethod InputEngine::inputMethod

    Use this property to set active input method, or monitor when the
    active input method changes.
*/

/*!
    \property DeclarativeInputEngine::inputMethod
    \brief the active input method.

    Use this property to set active input method, or monitor when the
    active input method changes.
*/

/*!
    \qmlproperty list<int> InputEngine::inputModes

    The list of available input modes is depended on input method and locale.
    This property is updated when either of the dependencies changes.
*/

/*!
    \property DeclarativeInputEngine::inputModes
    \brief the available input modes for active input method.

    The list of available input modes is depended on input method and locale.
    This property is updated when either of the dependencies changes.
*/

/*!
    \qmlproperty int InputEngine::inputMode

    Use this property to get or set the current input mode. The
    InputEngine::inputModes provides list of valid input modes
    for current input method and locale.

    Here is a list of predefined input modes.

    \list
        \li \c InputEngine.Latin The default input mode for latin text.
        \li \c InputEngine.Numeric Only numeric input is allowed.
        \li \c InputEngine.Dialable Only dialable input is allowed.
    \endlist
*/

/*!
    \property DeclarativeInputEngine::inputMode
    \brief the current input mode.

    Use this property to get or set the current input mode. The
    DeclarativeInputEngine::inputModes provides list of valid input modes
    for current input method and locale.
*/

/*!
    \qmlproperty SelectionListModel InputEngine::wordCandidateListModel

    Use this property to access the list model for the word candidate
    list.
*/

/*!
    \property DeclarativeInputEngine::wordCandidateListModel
    \brief list model for the word candidate list.

    Use this property to access the list model for the word candidate
    list.
*/

/*!
    \qmlproperty SelectionListModel InputEngine::wordCandidateListVisibleHint

    This property is true if the word candidate list should be visible
    in the UI.
*/

/*!
    \property DeclarativeInputEngine::wordCandidateListVisibleHint
    \brief active status of of the word candidate list.

    This property is true if the word candidate list should be visible
    in the UI.
*/

/*!
    \enum DeclarativeInputEngine::InputMode

    This enum specifies input mode for input method.

    \value Latin
           The default input mode for latin text.
    \value Numeric
           Only numeric input is allowed.
    \value Dialable
           Only dialable input is allowed.
*/

/*!
    \enum DeclarativeInputEngine::TextCase

    This enum specifies text case for input method.

    \value Lower
           Lower case text.
    \value Upper
           Upper case text.
*/

/*!
    \qmlsignal void InputEngine::virtualKeyClicked(int key, string text, int modifiers)

    Indicates virtual \a key was clicked with \a text and \a modifiers.
    This signal is emitted after the input method has processed the key event.
*/

/*!
    \fn void DeclarativeInputEngine::virtualKeyClicked(Qt::Key key, const QString& text, Qt::KeyboardModifiers modifiers)

    Indicates virtual \a key was clicked with \a text and \a modifiers.
    This signal is emitted after the input method has processed the key event.
*/

/*!
    \qmlsignal void InputEngine::activeKeyChanged(int key)

    Indicates active \a key has changed.
*/

/*!
    \fn void DeclarativeInputEngine::activeKeyChanged(Qt::Key key)

    Indicates active \a key has changed.
*/

/*!
    \qmlsignal void InputEngine::previousKeyChanged(int key)

    Indicates previous \a key has changed.
*/

/*!
    \fn void DeclarativeInputEngine::previousKeyChanged(Qt::Key key)

    Indicates previous \a key has changed.
*/

/*!
    \qmlsignal void InputEngine::inputMethodChanged()

    Indicates the input method has changed.
*/

/*!
    \fn void DeclarativeInputEngine::inputMethodChanged()

    Indicates the input method has changed.
*/

/*!
    \qmlsignal void InputEngine::inputMethodReset()

    Emitted when input method needs reset.

    \note This signal is automatically connected to AbstractInputMethod::reset()
    and InputMethod::reset() when the input method is activated.
*/

/*!
    \fn void DeclarativeInputEngine::inputMethodReset()

    Emitted when input method needs reset.

    \note This signal is automatically connected to AbstractInputMethod::reset()
    and InputMethod::reset() when the input method is activated.
*/

/*!
    \qmlsignal void InputEngine::inputMethodUpdate()

    \note This signal is automatically connected to AbstractInputMethod::update()
    and InputMethod::update() when the input method is activated.
*/

/*!
    \fn void DeclarativeInputEngine::inputMethodUpdate()

    \note This signal is automatically connected to AbstractInputMethod::update()
    and InputMethod::update() when the input method is activated.
*/

/*!
    \qmlsignal void InputEngine::inputModesChanged()

    Indicates that the available input modes changed.
*/

/*!
    \fn void DeclarativeInputEngine::inputModesChanged()

    Indicates that the available input modes changed.
*/

/*!
    \qmlsignal void InputEngine::inputModeChanged()

    Indicates that input mode has changed.
*/

/*!
    \fn void DeclarativeInputEngine::inputModeChanged()

    Indicates that input mode has changed.
*/
