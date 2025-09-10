// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "examplehwrinputmethod_p.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QtVirtualKeyboard/qvirtualkeyboardtrace.h>
#include <QtVirtualKeyboard/private/handwritinggesturerecognizer_p.h>
#include <QtVirtualKeyboard/private/settings_p.h>
#include <QtVirtualKeyboard/private/qvirtualkeyboardabstractinputmethod_p.h>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QLoggingCategory>
#include <QLocale>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Q_LOGGING_CATEGORY(lcExampleHwr, "qt.virtualkeyboard.example.hwr")

class ExampleHwrInputMethodPrivate : public QVirtualKeyboardAbstractInputMethodPrivate
{
public:
    Q_DECLARE_PUBLIC(ExampleHwrInputMethod)

    ExampleHwrInputMethodPrivate(ExampleHwrInputMethod *q_ptr) :
        QVirtualKeyboardAbstractInputMethodPrivate(),
        q_ptr(q_ptr)
    {
    }

    bool setInputMode(const QLocale &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
    {
        Q_UNUSED(locale);
        finishRecognition();
        this->inputMode = inputMode;
        return true;
    }

    QByteArray getContext(QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
                          const QVariantMap &traceCaptureDeviceInfo,
                          const QVariantMap &traceScreenInfo) const
    {
        QCryptographicHash hash(QCryptographicHash::Md5);

        hash.addData(QByteArrayView(reinterpret_cast<const char *>(&patternRecognitionMode), sizeof(patternRecognitionMode)));

        QByteArray mapData;
        QDataStream ds(&mapData, QIODevice::WriteOnly);
        ds << traceCaptureDeviceInfo;
        ds << traceScreenInfo;
        hash.addData(mapData);

        return hash.result();
    }

    void setContext(QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
                    const QVariantMap &traceCaptureDeviceInfo,
                    const QVariantMap &traceScreenInfo,
                    const QByteArray &context)
    {
        Q_UNUSED(patternRecognitionMode);
        Q_UNUSED(traceScreenInfo);
        if (context == currentContext)
            return;
        currentContext = context;

        qCDebug(lcExampleHwr) << "setContext:" << QLatin1String((context.toHex()));

        // Finish recognition, but preserve current input
        const int dpi = traceCaptureDeviceInfo.value(QLatin1String("dpi"), 96).toInt();
        static const int INSTANT_GESTURE_WIDTH_THRESHOLD_MM = 25;
        gestureWidthThreshold = qRound(INSTANT_GESTURE_WIDTH_THRESHOLD_MM / 25.4 * dpi);

        gestureRecognizer.setDpi(dpi);
    }

    QVirtualKeyboardTrace *traceBegin(
            int traceId, QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
            const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo)
    {
        // The result id follows the trace id so that the (previous)
        // results completed during the handwriting can be rejected.
        resultId = traceId;

        QByteArray context = getContext(patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo);
        if (context != currentContext) {
            setContext(patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo, context);
        }

        Q_Q(ExampleHwrInputMethod);
        QVirtualKeyboardTrace *trace = new QVirtualKeyboardTrace(q);
        traceList.append(trace);

        return trace;
    }

    void traceEnd(QVirtualKeyboardTrace *trace)
    {
        if (trace->isCanceled()) {
            traceList.removeOne(trace);
            delete trace;
        } else if (handleGesture()) {
            finishRecognition();
            return;
        }
        if (!traceList.isEmpty()) {
            if (countActiveTraces() == 0)
                restartRecognition();
        }
    }

    int countActiveTraces() const
    {
        int count = 0;
        for (QVirtualKeyboardTrace *trace : std::as_const(traceList)) {
            if (!trace->isFinal())
                count++;
        }
        return count;
    }

    void clearTraces()
    {
        qDeleteAll(traceList);
        traceList.clear();
    }

    bool applyGesture(const QChar &gesture)
    {
        Q_Q(ExampleHwrInputMethod);
        QVirtualKeyboardInputContext *ic = q->inputContext();
        switch (gesture.unicode()) {
        case '\b':
            return ic->inputEngine()->virtualKeyClick(Qt::Key_Backspace, QString(), Qt::NoModifier);
        case '\r':
            return ic->inputEngine()->virtualKeyClick(Qt::Key_Return, QLatin1String("\n"), Qt::NoModifier);
        case ' ':
            return ic->inputEngine()->virtualKeyClick(Qt::Key_Space, QLatin1String(" "), Qt::NoModifier);
        default:
            return false;
        }
    }

    bool handleGesture()
    {
        if (countActiveTraces() > 0)
            return false;

        QVariantMap gesture(gestureRecognizer.recognize(traceList.mid(traceList.size() - 1, 1)));
        if (gesture.isEmpty())
            return false;

        qCDebug(lcExampleHwr) << "handleGesture:" << gesture;

        if (gesture[QLatin1String("type")].toString() == QLatin1String("swipe")) {

            static const int SWIPE_ANGLE_THRESHOLD = 15;    // degrees +-

            qreal swipeLength = gesture[QLatin1String("length")].toReal();
            if (swipeLength >= gestureWidthThreshold) {

                Q_Q(ExampleHwrInputMethod);
                QVirtualKeyboardInputContext *ic = q->inputContext();
                if (!ic)
                    return false;

                qreal swipeAngle = gesture[QLatin1String("angle_degrees")].toReal();
                int swipeTouchCount = gesture[QLatin1String("touch_count")].toInt();

                // Swipe left
                if (swipeAngle <= 180 + SWIPE_ANGLE_THRESHOLD && swipeAngle >= 180 - SWIPE_ANGLE_THRESHOLD) {
                    if (swipeTouchCount == 1) {
                        // Single swipe: backspace
                        ic->inputEngine()->virtualKeyClick(Qt::Key_Backspace, QString(), Qt::NoModifier);
                        return true;
                    }
                    return false;
                }

                // Swipe right
                if (swipeAngle <= SWIPE_ANGLE_THRESHOLD || swipeAngle >= 360 - SWIPE_ANGLE_THRESHOLD) {
                    if (swipeTouchCount == 1) {
                        // Single swipe: space
                        ic->inputEngine()->virtualKeyClick(Qt::Key_Space, QLatin1String(" "), Qt::NoModifier);
                        return true;
                    }
                    return false;
                }

                // Swipe up
                if (swipeAngle <= 270 + SWIPE_ANGLE_THRESHOLD && swipeAngle >= 270 - SWIPE_ANGLE_THRESHOLD) {
                    if (swipeTouchCount == 1) {
                        // Single swipe: toggle input mode
                        select();
                        if (!(ic->inputMethodHints() & (Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly))) {
                            QList<int> inputModes = ic->inputEngine()->inputModes();
                            // Filter out duplicate numeric mode (in favor of Numeric)
                            int indexOfNumericInputMode = inputModes.indexOf(static_cast<int>(QVirtualKeyboardInputEngine::InputMode::Numeric));
                            int indexOfDialableInputMode = inputModes.indexOf(static_cast<int>(QVirtualKeyboardInputEngine::InputMode::Dialable));
                            if (indexOfNumericInputMode != -1 && indexOfDialableInputMode != -1)
                                inputModes.removeAt(inputMode != QVirtualKeyboardInputEngine::InputMode::Dialable ?
                                            indexOfDialableInputMode :
                                            indexOfNumericInputMode);
                            if (inputModes.size() > 1) {
                                int inputModeIndex = inputModes.indexOf(static_cast<int>(inputMode)) + 1;
                                if (inputModeIndex >= inputModes.size())
                                    inputModeIndex = 0;
                                ic->inputEngine()->setInputMode(static_cast<QVirtualKeyboardInputEngine::InputMode>(inputModes.at(inputModeIndex)));
                            }
                        }
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool isValidInputChar(const QChar &c) const
    {
        if (c.isLetterOrNumber())
            return true;
        if (isJoiner(c))
            return true;
        return false;
    }

    bool isJoiner(const QChar &c) const
    {
        if (c.isPunct() || c.isSymbol()) {
            Q_Q(const ExampleHwrInputMethod);
            QVirtualKeyboardInputContext *ic = q->inputContext();
            if (ic) {
                Qt::InputMethodHints inputMethodHints = ic->inputMethodHints();
                if (inputMethodHints.testFlag(Qt::ImhUrlCharactersOnly) || inputMethodHints.testFlag(Qt::ImhEmailCharactersOnly))
                    return QString(QStringLiteral(":/?#[]@!$&'()*+,;=-_.%")).contains(c);
            }
            ushort unicode = c.unicode();
            if (unicode == Qt::Key_Apostrophe || unicode == Qt::Key_Minus)
                return true;
        }
        return false;
    }

    void restartRecognition()
    {
        qCDebug(lcExampleHwr) << "restartRecognition";

        resetResultTimer(Settings::instance()->hwrTimeoutForAlphabetic());
    }

    bool finishRecognition(bool emitSelectionListChanged = true)
    {
        qCDebug(lcExampleHwr) << "finishRecognition";
        bool result = !traceList.isEmpty();

        stopResultTimer();
        clearTraces();

        if (!wordCandidates.isEmpty()) {
            wordCandidates.clear();
            activeWordIndex = -1;
            if (emitSelectionListChanged) {
                Q_Q(ExampleHwrInputMethod);
                emit q->selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
                emit q->selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, activeWordIndex);
            }
            result = true;
        }

        return result;
    }

    void select(int index = -1)
    {
        Q_Q(ExampleHwrInputMethod);
        QVirtualKeyboardInputContext *ic = q->inputContext();
        if (!ic)
            return;

        if (!wordCandidates.isEmpty())
            ic->commit(wordCandidates.at(index != -1 ? index : 0));

        finishRecognition();
    }

    void processResult()
    {
        qCDebug(lcExampleHwr) << "processResult";

        Q_Q(ExampleHwrInputMethod);
        QVirtualKeyboardInputContext *ic = q->inputContext();
        if (!ic)
            return;

        QStringList newWordCandidates;
        QString word = !wordCandidates.isEmpty() ? wordCandidates.at(0) : QString();
        switch (inputMode) {
        case QVirtualKeyboardInputEngine::InputMode::Latin:
            appendRandomChar(word);
            break;
        case QVirtualKeyboardInputEngine::InputMode::Numeric:
        case QVirtualKeyboardInputEngine::InputMode::Dialable:
            appendRandomDigit(word);
            break;
        default:
            break;
        }
        newWordCandidates.append(word);
        activeWordIndex = 0;
        wordCandidates = newWordCandidates;
        qCDebug(lcExampleHwr) << "wordCandidates" << wordCandidates;
        ic->setPreeditText(word);

        emit q->selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
        emit q->selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, activeWordIndex);
    }

    static void appendRandomChar(QString& word)
    {
        word.append(QChar('a' + QRandomGenerator::global()->bounded(26)));
    }

    static void appendRandomDigit(QString& word)
    {
        word.append(QChar('0' + QRandomGenerator::global()->bounded(10)));
    }

    void resetResultTimer(int interval = 500)
    {
        qCDebug(lcExampleHwr) << "resetResultTimer:" << interval;
        Q_Q(ExampleHwrInputMethod);
        stopResultTimer();
        resultTimer = q->startTimer(interval);
    }

    void stopResultTimer()
    {
        if (resultTimer) {
            qCDebug(lcExampleHwr) << "stopResultTimer";
            Q_Q(ExampleHwrInputMethod);
            q->killTimer(resultTimer);
            resultTimer = 0;
        }
    }

    ExampleHwrInputMethod *q_ptr = nullptr;
    QVirtualKeyboardInputEngine::InputMode inputMode = QVirtualKeyboardInputEngine::InputMode::Latin;
    QByteArray currentContext;
    int gestureWidthThreshold = 0;
    int resultId = 0;
    int lastResultId = 0;
    int resultTimer = 0;
    QList<QVirtualKeyboardTrace *> traceList;
    HandwritingGestureRecognizer gestureRecognizer;
    QStringList wordCandidates;
    int activeWordIndex = -1;
};

/*!
    \class QtVirtualKeyboard::ExampleHwrInputMethod
    \internal
*/

ExampleHwrInputMethod::ExampleHwrInputMethod(QObject *parent) :
    QVirtualKeyboardAbstractInputMethod(*new ExampleHwrInputMethodPrivate(this), parent)
{
}

ExampleHwrInputMethod::~ExampleHwrInputMethod()
{
}

QList<QVirtualKeyboardInputEngine::InputMode> ExampleHwrInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale);
    QList<QVirtualKeyboardInputEngine::InputMode> availableInputModes = {
        QVirtualKeyboardInputEngine::InputMode::Latin,
        QVirtualKeyboardInputEngine::InputMode::Numeric,
    };
    return availableInputModes;
}

bool ExampleHwrInputMethod::setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
{
    Q_D(ExampleHwrInputMethod);
    d->select();
    return d->setInputMode(QLocale(locale), inputMode);
}

bool ExampleHwrInputMethod::setTextCase(QVirtualKeyboardInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase);
    return true;
}

bool ExampleHwrInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);
    Q_D(ExampleHwrInputMethod);
    switch (key) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Tab:
    case Qt::Key_Space:
        d->select();
        update();
        break;

    case Qt::Key_Backspace:
        {
            QVirtualKeyboardInputContext *ic = inputContext();
            QString preeditText = ic->preeditText();
            if (preeditText.length() > 1) {
                preeditText.chop(1);
                ic->setPreeditText(preeditText);
                emit selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
                emit selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, d->activeWordIndex);
                return true;
            } else {
                bool result = !preeditText.isEmpty();
                if (result)
                    ic->clear();
                d->finishRecognition();
                return result;
            }
        }

    default:
        if (text.length() > 0) {
            QVirtualKeyboardInputContext *ic = inputContext();
            QString preeditText = ic->preeditText();
            QChar c = text.at(0);
            bool addToWord = d->isValidInputChar(c) && (!preeditText.isEmpty() || !d->isJoiner(c));
            if (addToWord) {
                preeditText.append(text);
                ic->setPreeditText(preeditText);
                d->finishRecognition(false);
                d->wordCandidates.append(preeditText);
                d->activeWordIndex = 0;
                emit selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
                emit selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, d->activeWordIndex);
                return true;
            } else {
                ic->commit();
                d->finishRecognition();
            }
            break;
        }
    }
    return false;
}

void ExampleHwrInputMethod::reset()
{
    Q_D(ExampleHwrInputMethod);
    qCDebug(lcExampleHwr) << "reset";
    d->finishRecognition();
}

void ExampleHwrInputMethod::update()
{
    Q_D(ExampleHwrInputMethod);
    qCDebug(lcExampleHwr) << "update";
    d->select();
}

QList<QVirtualKeyboardSelectionListModel::Type> ExampleHwrInputMethod::selectionLists()
{
    return QList<QVirtualKeyboardSelectionListModel::Type>() << QVirtualKeyboardSelectionListModel::Type::WordCandidateList;
}

int ExampleHwrInputMethod::selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type)
{
    Q_UNUSED(type);
    Q_D(ExampleHwrInputMethod);
    return d->wordCandidates.size();
}

QVariant ExampleHwrInputMethod::selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index, QVirtualKeyboardSelectionListModel::Role role)
{
    QVariant result;
    Q_D(ExampleHwrInputMethod);
    switch (role) {
    case QVirtualKeyboardSelectionListModel::Role::Display:
        result = QVariant(d->wordCandidates.at(index));
        break;
    case QVirtualKeyboardSelectionListModel::Role::WordCompletionLength:
        result.setValue(0);
        break;
    case QVirtualKeyboardSelectionListModel::Role::Dictionary:
    {
        QVirtualKeyboardSelectionListModel::DictionaryType dictionaryType =
                QVirtualKeyboardSelectionListModel::DictionaryType::Default;
        result = QVariant(static_cast<int>(dictionaryType));
        break;
    }
    case QVirtualKeyboardSelectionListModel::Role::CanRemoveSuggestion:
        result = QVariant(false);
        break;
    default:
        result = QVirtualKeyboardAbstractInputMethod::selectionListData(type, index, role);
        break;
    }
    return result;
}

void ExampleHwrInputMethod::selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index)
{
    Q_UNUSED(type);
    Q_D(ExampleHwrInputMethod);
    d->select(index);
}

QList<QVirtualKeyboardInputEngine::PatternRecognitionMode> ExampleHwrInputMethod::patternRecognitionModes() const
{
    return QList<QVirtualKeyboardInputEngine::PatternRecognitionMode>()
            << QVirtualKeyboardInputEngine::PatternRecognitionMode::Handwriting;
}

QVirtualKeyboardTrace *ExampleHwrInputMethod::traceBegin(
        int traceId, QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
        const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo)
{
    Q_D(ExampleHwrInputMethod);
    return d->traceBegin(traceId, patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo);
}

bool ExampleHwrInputMethod::traceEnd(QVirtualKeyboardTrace *trace)
{
    Q_D(ExampleHwrInputMethod);
    d->traceEnd(trace);
    return true;
}

bool ExampleHwrInputMethod::reselect(int cursorPosition, const QVirtualKeyboardInputEngine::ReselectFlags &reselectFlags)
{
    Q_D(ExampleHwrInputMethod);

    QVirtualKeyboardInputContext *ic = inputContext();
    if (!ic)
        return false;

    const int maxLength = 32;
    const QString surroundingText = ic->surroundingText();
    int replaceFrom = 0;
    QString stringStart;

    if (cursorPosition > surroundingText.length())
        return false;

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordBeforeCursor)) {
        for (int i = cursorPosition - 1; i >= 0 && stringStart.length() < maxLength; --i) {
            QChar c = surroundingText.at(i);
            if (!d->isValidInputChar(c))
                break;
            stringStart.insert(0, c);
            --replaceFrom;
        }

        while (replaceFrom < 0 && d->isJoiner(stringStart.at(0))) {
            stringStart.remove(0, 1);
            ++replaceFrom;
        }
    }

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordAtCursor) && replaceFrom == 0) {
        stringStart.clear();
        return false;
    }

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordAfterCursor)) {
        for (int i = cursorPosition; i < surroundingText.length() && stringStart.length() < maxLength; ++i) {
            QChar c = surroundingText.at(i);
            if (!d->isValidInputChar(c))
                break;
            stringStart.append(c);
        }

        while (replaceFrom > -stringStart.length()) {
            int lastPos = stringStart.length() - 1;
            if (!d->isJoiner(stringStart.at(lastPos)))
                break;
            stringStart.remove(lastPos, 1);
        }
    }

    if (stringStart.isEmpty())
        return false;

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordAtCursor) && replaceFrom == -stringStart.length() && stringStart.length() < maxLength) {
        stringStart.clear();
        return false;
    }

    if (d->isJoiner(stringStart.at(0))) {
        stringStart.clear();
        return false;
    }

    if (d->isJoiner(stringStart.at(stringStart.length() - 1))) {
        stringStart.clear();
        return false;
    }

    ic->setPreeditText(stringStart, QList<QInputMethodEvent::Attribute>(), replaceFrom, stringStart.length());
    d->activeWordIndex = 0;
    d->wordCandidates = {stringStart};
    emit selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
    emit selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, d->activeWordIndex);

    return true;
}

void ExampleHwrInputMethod::timerEvent(QTimerEvent *timerEvent)
{
    Q_D(ExampleHwrInputMethod);
    int timerId = timerEvent->timerId();
    qCDebug(lcExampleHwr) << "timerEvent():" << timerId;
    if (timerId == d->resultTimer) {
        if (!d->countActiveTraces()) {
            d->stopResultTimer();
            d->processResult();
            d->clearTraces();
        }
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
