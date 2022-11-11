// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/shifthandler_p.h>
#include <QtVirtualKeyboard/private/qvirtualkeyboardinputcontext_p.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtCore/private/qobject_p.h>
#include <QSet>
#include <QGuiApplication>
#include <QElapsedTimer>
#include <QStyleHints>

QT_BEGIN_NAMESPACE

size_t qHash(QLocale::Language lang, size_t seed)
{
    return qHash(ushort(lang), seed);
}

namespace QtVirtualKeyboard {

class ShiftHandlerPrivate : public QObjectPrivate
{
public:
    ShiftHandlerPrivate() :
        QObjectPrivate(),
        inputContext(nullptr),
        sentenceEndingCharacters(QLatin1String(".!?") + QChar(Qt::Key_exclamdown) + QChar(Qt::Key_questiondown)),
        autoCapitalizationEnabled(false),
        toggleShiftEnabled(false),
        shift(false),
        shiftChanged(false),
        capsLock(false),
        resetWhenVisible(false),
        manualShiftLanguageFilter(QSet<QLocale::Language>() << QLocale::Arabic << QLocale::Persian << QLocale::Hindi << QLocale::Korean << QLocale::Thai),
        manualCapsInputModeFilter(QSet<QVirtualKeyboardInputEngine::InputMode>() << QVirtualKeyboardInputEngine::InputMode::Cangjie << QVirtualKeyboardInputEngine::InputMode::Zhuyin << QVirtualKeyboardInputEngine::InputMode::Hebrew),
        noAutoUppercaseInputModeFilter(QSet<QVirtualKeyboardInputEngine::InputMode>() << QVirtualKeyboardInputEngine::InputMode::FullwidthLatin << QVirtualKeyboardInputEngine::InputMode::Pinyin << QVirtualKeyboardInputEngine::InputMode::Cangjie << QVirtualKeyboardInputEngine::InputMode::Zhuyin << QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting << QVirtualKeyboardInputEngine::InputMode::JapaneseHandwriting << QVirtualKeyboardInputEngine::InputMode::KoreanHandwriting << QVirtualKeyboardInputEngine::InputMode::Romaji),
        allCapsInputModeFilter(QSet<QVirtualKeyboardInputEngine::InputMode>() << QVirtualKeyboardInputEngine::InputMode::Hiragana << QVirtualKeyboardInputEngine::InputMode::Katakana)
    {
    }

    QVirtualKeyboardInputContext *inputContext;
    QString sentenceEndingCharacters;
    bool autoCapitalizationEnabled;
    bool toggleShiftEnabled;
    bool shift;
    bool shiftChanged;
    bool capsLock;
    bool resetWhenVisible;
    QLocale locale;
    QElapsedTimer timer;
    const QSet<QLocale::Language> manualShiftLanguageFilter;
    const QSet<QVirtualKeyboardInputEngine::InputMode> manualCapsInputModeFilter;
    const QSet<QVirtualKeyboardInputEngine::InputMode> noAutoUppercaseInputModeFilter;
    const QSet<QVirtualKeyboardInputEngine::InputMode> allCapsInputModeFilter;
};

/*!
    \qmltype ShiftHandler
    \inqmlmodule QtQuick.VirtualKeyboard
    \ingroup qtvirtualkeyboard-internal-qml
    \instantiates QtVirtualKeyboard::ShiftHandler
    \brief Manages the shift state.
*/

/*!
    \class QtVirtualKeyboard::ShiftHandler
    \internal
    \inmodule QtVirtualKeyboard
    \brief Manages the shift state.
*/

ShiftHandler::ShiftHandler(QVirtualKeyboardInputContext *parent) :
    QObject(*new ShiftHandlerPrivate(), parent)
{
    Q_D(ShiftHandler);
    d->inputContext = parent;
}

void ShiftHandler::init()
{
    Q_D(ShiftHandler);
    connect(d->inputContext, SIGNAL(inputMethodHintsChanged()), SLOT(restart()));
    connect(d->inputContext->priv(), SIGNAL(inputItemChanged()), SLOT(restart()));
    connect(d->inputContext->inputEngine(), SIGNAL(inputModeChanged()), SLOT(restart()));
    connect(d->inputContext, SIGNAL(preeditTextChanged()), SLOT(autoCapitalize()));
    connect(d->inputContext, SIGNAL(surroundingTextChanged()), SLOT(autoCapitalize()));
    connect(d->inputContext, SIGNAL(cursorPositionChanged()), SLOT(autoCapitalize()));
    connect(d->inputContext, SIGNAL(localeChanged()), SLOT(localeChanged()));
    connect(qGuiApp->inputMethod(), SIGNAL(visibleChanged()), SLOT(inputMethodVisibleChanged()));
    d->locale = QLocale(d->inputContext->locale());
}

/*!
    \internal
*/
ShiftHandler::~ShiftHandler()
{

}

QString ShiftHandler::sentenceEndingCharacters() const
{
    Q_D(const ShiftHandler);
    return d->sentenceEndingCharacters;
}

void ShiftHandler::setSentenceEndingCharacters(const QString &value)
{
    Q_D(ShiftHandler);
    if (d->sentenceEndingCharacters != value) {
        d->sentenceEndingCharacters = value;
        autoCapitalize();
        emit sentenceEndingCharactersChanged();
    }
}

bool ShiftHandler::isAutoCapitalizationEnabled() const
{
    Q_D(const ShiftHandler);
    return d->autoCapitalizationEnabled;
}

bool ShiftHandler::isToggleShiftEnabled() const
{
    Q_D(const ShiftHandler);
    return d->toggleShiftEnabled;
}

bool ShiftHandler::isShiftActive() const
{
    Q_D(const ShiftHandler);
    return d->shift;
}

void ShiftHandler::setShiftActive(bool active)
{
    Q_D(ShiftHandler);
    if (d->shift != active) {
        d->shift = active;
        d->shiftChanged = true;
        emit shiftActiveChanged();
        if (!d->capsLock)
            emit uppercaseChanged();
    }
}

bool ShiftHandler::isCapsLockActive() const
{
    Q_D(const ShiftHandler);
    return d->capsLock;
}

void ShiftHandler::setCapsLockActive(bool active)
{
    Q_D(ShiftHandler);
    if (d->capsLock != active) {
        d->capsLock = active;
        emit capsLockActiveChanged();
        if (!d->shift)
            emit uppercaseChanged();
    }
}

bool ShiftHandler::isUppercase() const
{
    Q_D(const ShiftHandler);
    return d->shift || d->capsLock;
}

/*!
    \since 1.2

    \qmlmethod void ShiftHandler::toggleShift()

    Toggles the current shift state.

    This method provides the functionality of the shift key.

    \sa toggleShiftEnabled
*/
/*!
    \since 1.2
    \internal

    \fn void QtVirtualKeyboard::ShiftHandler::toggleShift()

    Toggles the current shift state.

    This method provides the functionality of the shift key.

    \sa toggleShiftEnabled
*/
void ShiftHandler::toggleShift()
{
    Q_D(ShiftHandler);
    if (!d->toggleShiftEnabled)
        return;
    if (d->manualShiftLanguageFilter.contains(d->locale.language())) {
        setCapsLockActive(false);
        setShiftActive(!d->shift);
    } else if (d->manualCapsInputModeFilter.contains(d->inputContext->inputEngine()->inputMode())) {
        bool capsLock = d->capsLock;
        setCapsLockActive(!capsLock);
        setShiftActive(!capsLock);
    } else {
        if (d->capsLock) {
            setCapsLockActive(!d->capsLock && d->shift && !d->shiftChanged);
        }

        QStyleHints *style = QGuiApplication::styleHints();

        if (!d->timer.isValid() || d->timer.elapsed() > style->mouseDoubleClickInterval()) {
            d->timer.restart();
        } else if (d->timer.elapsed() < style->mouseDoubleClickInterval() && !d->capsLock) {
            setCapsLockActive(!d->capsLock && d->shift && !d->shiftChanged);
        }

        setShiftActive(d->capsLock || !d->shift);
        d->shiftChanged = false;
    }
}

/*! Clears the toggle shift timer.
    \internal

*/
void ShiftHandler::clearToggleShiftTimer()
{
    Q_D(ShiftHandler);
    d->timer.invalidate();
}

void ShiftHandler::reset()
{
    Q_D(ShiftHandler);
    if (d->inputContext->priv()->inputItem() || QT_VIRTUALKEYBOARD_FORCE_EVENTS_WITHOUT_FOCUS) {
        Qt::InputMethodHints inputMethodHints = d->inputContext->inputMethodHints();
        QVirtualKeyboardInputEngine::InputMode inputMode = d->inputContext->inputEngine()->inputMode();
        bool preferUpperCase = (inputMethodHints & (Qt::ImhPreferUppercase | Qt::ImhUppercaseOnly));
        bool autoCapitalizationEnabled = !(d->inputContext->inputMethodHints() & (Qt::ImhNoAutoUppercase |
              Qt::ImhUppercaseOnly | Qt::ImhLowercaseOnly | Qt::ImhEmailCharactersOnly |
              Qt::ImhUrlCharactersOnly | Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly |
              Qt::ImhDigitsOnly)) && !d->noAutoUppercaseInputModeFilter.contains(inputMode);
        bool toggleShiftEnabled = !(inputMethodHints & (Qt::ImhUppercaseOnly | Qt::ImhLowercaseOnly));
        // For filtered languages reset the initial shift status to lower case
        // and allow manual shift change
        if (d->manualShiftLanguageFilter.contains(d->locale.language()) ||
                d->manualCapsInputModeFilter.contains(inputMode)) {
            preferUpperCase = false;
            autoCapitalizationEnabled = false;
            toggleShiftEnabled = true;
        } else if (d->allCapsInputModeFilter.contains(inputMode)) {
            preferUpperCase = true;
            autoCapitalizationEnabled = false;
            toggleShiftEnabled = false;
        }
        setToggleShiftEnabled(toggleShiftEnabled);
        setAutoCapitalizationEnabled(autoCapitalizationEnabled);
        setCapsLockActive(preferUpperCase);
        if (preferUpperCase)
            setShiftActive(preferUpperCase);
        else
            autoCapitalize();
    }
}

void ShiftHandler::autoCapitalize()
{
    Q_D(ShiftHandler);
    if (d->capsLock)
        return;
    if (!d->autoCapitalizationEnabled || !d->inputContext->preeditText().isEmpty()) {
        setShiftActive(false);
    } else {
        int cursorPosition = d->inputContext->cursorPosition();
        bool preferLowerCase = d->inputContext->inputMethodHints() & Qt::ImhPreferLowercase;
        if (cursorPosition == 0) {
            setShiftActive(!preferLowerCase);
        } else { // space after sentence-ending character triggers auto-capitalization
            QString text = d->inputContext->surroundingText();
            text.truncate(cursorPosition);
            if (text.trimmed().size() == 0)
                setShiftActive(!preferLowerCase);
            else if (text.endsWith(QLatin1Char(' ')))
                setShiftActive(d->sentenceEndingCharacters.contains(QStringView{text}.right(2)[0])
                               && !preferLowerCase);
            else
                setShiftActive(false);
        }
    }
}

void ShiftHandler::restart()
{
    Q_D(ShiftHandler);
    const QGuiApplication *app = qGuiApp;
    if (!app || !app->inputMethod()->isVisible()) {
        d->resetWhenVisible = true;
        return;
    }
    reset();
}

void ShiftHandler::localeChanged()
{
    Q_D(ShiftHandler);
    d->locale = QLocale(d->inputContext->locale());
    restart();
}

void ShiftHandler::inputMethodVisibleChanged()
{
    Q_D(ShiftHandler);
    if (!d->resetWhenVisible)
        return;

    const QGuiApplication *app = qGuiApp;
    if (app && app->inputMethod()->isVisible()) {
        d->resetWhenVisible = false;
        reset();
    }
}

void ShiftHandler::setAutoCapitalizationEnabled(bool enabled)
{
    Q_D(ShiftHandler);
    if (d->autoCapitalizationEnabled != enabled) {
        d->autoCapitalizationEnabled = enabled;
        emit autoCapitalizationEnabledChanged();
    }
}

void ShiftHandler::setToggleShiftEnabled(bool enabled)
{
    Q_D(ShiftHandler);
    if (d->toggleShiftEnabled != enabled) {
        d->toggleShiftEnabled = enabled;
        emit toggleShiftEnabledChanged();
    }
}

/*!
    \property QtVirtualKeyboard::ShiftHandler::sentenceEndingCharacters

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

/*!
    \since 1.2

    \property QtVirtualKeyboard::ShiftHandler::autoCapitalizationEnabled

    This property provides the current state of the automatic
    capitalization feature.
*/

/*!
    \since 1.2

    \qmlproperty bool ShiftHandler::autoCapitalizationEnabled

    This property provides the current state of the automatic
    capitalization feature.
*/

/*!
    \since 1.2

    \property QtVirtualKeyboard::ShiftHandler::toggleShiftEnabled

    This property provides the current state of the toggleShift()
    method. When true, the current shift state can be changed by
    calling the toggleShift() method.
*/

/*!
    \since 1.2

    \qmlproperty bool ShiftHandler::toggleShiftEnabled

    This property provides the current state of the toggleShift()
    method. When true, the current shift state can be changed by
    calling the toggleShift() method.
*/

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
