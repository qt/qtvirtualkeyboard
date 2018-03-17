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

#include "lipiinputmethod.h"
#include "lipisharedrecognizer.h"
#include "inputengine.h"
#include "inputcontext.h"
#include "shifthandler.h"
#include "virtualkeyboarddebug.h"
#include "trace.h"
#include "handwritinggesturerecognizer.h"

#ifdef HAVE_HUNSPELL
#include "hunspellinputmethod_p.h"
#endif

#include "LTKCaptureDevice.h"
#include "LTKScreenContext.h"
#include "LTKTraceGroup.h"
#include "LTKChannel.h"
#include "LTKTraceFormat.h"
#include "LTKTrace.h"
#include "LTKShapeRecoResult.h"

#include <QCryptographicHash>

#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
#include "unipentrace.h"
#include <QStandardPaths>
#endif

#ifdef HAVE_HUNSPELL
#define LipiInputMethodPrivateBase HunspellInputMethodPrivate
#else
#define LipiInputMethodPrivateBase AbstractInputMethodPrivate
#endif

namespace QtVirtualKeyboard {

class LipiInputMethodPrivate : public LipiInputMethodPrivateBase
{
    Q_DECLARE_PUBLIC(LipiInputMethod)
public:
    LipiInputMethodPrivate(LipiInputMethod *q_ptr) :
#ifdef HAVE_HUNSPELL
        LipiInputMethodPrivateBase(static_cast<HunspellInputMethod *>(q_ptr)),
#else
        LipiInputMethodPrivateBase(),
#endif
        q_ptr(q_ptr),
        recognizeTimer(0),
        textCase(InputEngine::Lower)
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
        , unipenTrace(0)
#endif
    {
    }

    ~LipiInputMethodPrivate()
    {
        cancelRecognition();
    }

    QByteArray getContext(InputEngine::PatternRecognitionMode patternRecognitionMode,
                          const QVariantMap &traceCaptureDeviceInfo,
                          const QVariantMap &traceScreenInfo) const
    {
        QCryptographicHash hash(QCryptographicHash::Md5);

        hash.addData((const char *)&patternRecognitionMode, sizeof(patternRecognitionMode));

        QByteArray mapData;
        QDataStream ds(&mapData, QIODevice::WriteOnly);
        ds << traceCaptureDeviceInfo;
        ds << traceScreenInfo;
        hash.addData(mapData);

        return hash.result();
    }

    void setContext(InputEngine::PatternRecognitionMode patternRecognitionMode,
                    const QVariantMap &traceCaptureDeviceInfo,
                    const QVariantMap &traceScreenInfo)
    {
        QByteArray context = getContext(patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo);
        if (context == currentContext)
            return;

        VIRTUALKEYBOARD_DEBUG() << "LipiInputMethodPrivate::setContext():" << QString(context.toHex());

        clearTraces();

        deviceInfo.reset(new LTKCaptureDevice());
        deviceInfo->setSamplingRate(traceCaptureDeviceInfo.value("sampleRate", 60).toInt());
        deviceInfo->setXDPI(traceCaptureDeviceInfo.value("dpi", 96).toInt());
        deviceInfo->setYDPI(deviceInfo->getXDPI());
        deviceInfo->setLatency(traceCaptureDeviceInfo.value("latency", 0.0).toFloat());
        deviceInfo->setUniformSampling(traceCaptureDeviceInfo.value("uniform", false).toBool());

        screenContext.reset(new LTKScreenContext());
        QRectF boundingBox(traceScreenInfo.value("boundingBox").toRectF());
        if (!boundingBox.isEmpty()) {
            screenContext->setBboxLeft(boundingBox.left());
            screenContext->setBboxTop(boundingBox.top());
            screenContext->setBboxRight(boundingBox.right());
            screenContext->setBboxBottom(boundingBox.bottom());
        }

        QVariantList horizontalRulers(traceScreenInfo.value("horizontalRulers", QVariantList()).toList());
        if (!horizontalRulers.isEmpty()) {
            for (QVariantList::ConstIterator i = horizontalRulers.constBegin();
                 i != horizontalRulers.constEnd(); i++) {
                screenContext->addHLine(i->toFloat());
            }
        }

        QVariantList verticalRulers(traceScreenInfo.value("verticalRulers", QVariantList()).toList());
        if (!horizontalRulers.isEmpty()) {
            for (QVariantList::ConstIterator i = verticalRulers.constBegin();
                 i != verticalRulers.constEnd(); i++) {
                screenContext->addVLine(i->toFloat());
            }
        }

        gestureRecognizer.setDpi(deviceInfo->getXDPI());

        currentContext = context;
    }

    Trace *traceBegin(int traceId, InputEngine::PatternRecognitionMode patternRecognitionMode,
                      const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo)
    {
        Q_UNUSED(traceId)

        stopRecognizeTimer();

        setContext(patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo);

        if (recognitionTask) {
            recognizer.cancelRecognitionTask(recognitionTask);
            recognitionTask.reset();
            delayedResult.clear();
        }

#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
        if (!unipenTrace) {
            Q_Q(LipiInputMethod);
            unipenTrace = new UnipenTrace(traceCaptureDeviceInfo, traceScreenInfo, q);
        }
#endif

        Trace *trace = new Trace();
        trace->setChannels(QStringList("t"));
        traceList.append(trace);

        return trace;
    }

    void traceEnd(Trace *trace)
    {
        if (trace->isCanceled()) {
            VIRTUALKEYBOARD_DEBUG() << "LipiInputMethodPrivate::traceEnd(): discarded" << trace;
            traceList.removeOne(trace);
            delete trace;
        } else {
            addPointsToTraceGroup(trace);
        }
        handleGesture();
        if (!traceList.isEmpty() && countActiveTraces() == 0)
            restartRecognition();
    }

    int countActiveTraces() const
    {
        int count = 0;
        for (Trace *trace : qAsConst(traceList)) {
            if (!trace->isFinal())
                count++;
        }
        return count;
    }

    void handleGesture()
    {
        if (countActiveTraces() > 0)
            return;

        QVariantMap gesture = gestureRecognizer.recognize(traceList);
        if (gesture.isEmpty())
            return;

        VIRTUALKEYBOARD_DEBUG() << "LipiInputMethodPrivate::handleGesture():" << gesture;

        if (gesture[QLatin1String("type")].toString() == QLatin1String("swipe")) {

            static const int SWIPE_MIN_LENGTH = 25;         // mm
            static const int SWIPE_ANGLE_THRESHOLD = 15;    // degrees +-

            qreal swipeLength = gesture[QLatin1String("length_mm")].toReal();
            if (swipeLength >= SWIPE_MIN_LENGTH) {

                Q_Q(LipiInputMethod);
                InputContext *ic = q->inputContext();
                if (!ic)
                    return;

                qreal swipeAngle = gesture[QLatin1String("angle_degrees")].toReal();
                int swipeTouchCount = gesture[QLatin1String("touch_count")].toInt();

                // Swipe left
                if (swipeAngle <= 180 + SWIPE_ANGLE_THRESHOLD && swipeAngle >= 180 - SWIPE_ANGLE_THRESHOLD) {
                    if (swipeTouchCount == 1) {
                        // Single swipe: backspace
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
                        dumpTraces();
                        saveTraces(Qt::Key_Backspace, 100);
#endif
                        cancelRecognition();
                        ic->inputEngine()->virtualKeyClick(Qt::Key_Backspace, QString(), Qt::NoModifier);
                    } else if (swipeTouchCount == 2) {
                        // Double swipe: reset word, or backspace
                        cancelRecognition();
                        if (!ic->preeditText().isEmpty()) {
                            q->reset();
                            ic->setPreeditText(QString());
                        } else {
                            ic->inputEngine()->virtualKeyClick(Qt::Key_Backspace, QString(), Qt::NoModifier);
                        }
                    }
                    return;
                }

                // Swipe right
                if (swipeAngle <= SWIPE_ANGLE_THRESHOLD || swipeAngle >= 360 - SWIPE_ANGLE_THRESHOLD) {
                    if (swipeTouchCount == 1) {
                        // Single swipe: space
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
                        dumpTraces();
                        saveTraces(Qt::Key_Space, 100);
#endif
                        cancelRecognition();
                        ic->inputEngine()->virtualKeyClick(Qt::Key_Space, QString(" "), Qt::NoModifier);
                    } else if (swipeTouchCount == 2) {
                        // Double swipe: commit word, or insert space
                        cancelRecognition();
#ifdef HAVE_HUNSPELL
                        if (activeWordIndex != -1) {
                            q->selectionListItemSelected(SelectionListModel::WordCandidateList, activeWordIndex);
                            return;
                        }
#endif
                        ic->inputEngine()->virtualKeyClick(Qt::Key_Space, QString(" "), Qt::NoModifier);
                    }
                    return;
                }

                // Swipe up
                if (swipeAngle <= 270 + SWIPE_ANGLE_THRESHOLD && swipeAngle >= 270 - SWIPE_ANGLE_THRESHOLD) {
                    if (swipeTouchCount == 1) {
                        // Single swipe: toggle input mode
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
                        dumpTraces();
                        saveTraces(Qt::Key_Mode_switch, 100);
#endif
                        cancelRecognition();
                        if (!(ic->inputMethodHints() & (Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly))) {
                            InputEngine::InputMode inputMode = ic->inputEngine()->inputMode();
                            inputMode = inputMode == InputEngine::Latin ?
                                        InputEngine::Numeric : InputEngine::Latin;
                            ic->inputEngine()->setInputMode(inputMode);
                        }
                    } else if (swipeTouchCount == 2) {
                        // Double swipe: toggle text case
                        cancelRecognition();
                        ic->shiftHandler()->toggleShift();
                    }
                    return;
                }
            }
        }
    }

    void clearTraces()
    {
        qDeleteAll(traceList);
        traceList.clear();
        traceGroup.emptyAllTraces();
    }

    void addPointsToTraceGroup(Trace *trace)
    {
        vector<LTKChannel> channels;
        channels.push_back(LTKChannel("X", DT_INT, true));
        channels.push_back(LTKChannel("Y", DT_INT, true));
        bool hasTime = trace->channels().contains("t");
        if (hasTime)
            channels.push_back(LTKChannel("T", DT_FLOAT, true));
        LTKTraceFormat traceFormat(channels);
        LTKTrace ltktrace(traceFormat);

        const QVariantList points = trace->points();
        const QVariantList timeData = hasTime ? trace->channelData("t") : QVariantList();
        QVariantList::ConstIterator t = timeData.constBegin();
        for (const QVariant &p : points) {
            const QPointF pt(p.toPointF());
            vector<float> point;
            point.push_back(pt.x());
            point.push_back(pt.y());
            if (hasTime) {
                point.push_back(t->toFloat());
                t++;
            }
            ltktrace.addPoint(point);
        }
        traceGroup.addTrace(ltktrace);
    }

    void finishRecognition()
    {
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
        dumpTraces();
#endif
        stopRecognizeTimer();
        clearTraces();
        if (recognitionTask && !delayedResult.isEmpty() && recognitionTask->resultId() == delayedResult["resultId"].toInt())
            processResult(delayedResult);
        delayedResult.clear();
        recognitionTask.reset();
    }

    void restartRecognition()
    {
        recognitionTask = recognizer.newRecognition(*deviceInfo, *screenContext, subsetOfClasses, 0.0f, 4);
        if (recognitionTask) {
            Q_Q(LipiInputMethod);

            recognitionTask->traceGroup = traceGroup;

            QSharedPointer<LipiRecognitionResultsTask> resultsTask = recognizer.startRecognition(recognitionTask);
            q->connect(resultsTask.data(), SIGNAL(resultsAvailable(const QVariantList &)), SLOT(resultsAvailable(const QVariantList &)));

            resetRecognizeTimer();
        } else {
            stopRecognizeTimer();
        }
    }

    bool cancelRecognition()
    {
        stopRecognizeTimer();
        clearTraces();
        delayedResult.clear();
        bool result = !recognitionTask.isNull();
        recognitionTask.reset();
        return recognizer.cancelRecognition() || result;
    }

    void resetRecognizeTimer()
    {
        Q_Q(LipiInputMethod);
        stopRecognizeTimer();
        recognizeTimer = q->startTimer(300);
    }

    void stopRecognizeTimer()
    {
        if (recognizeTimer) {
            Q_Q(LipiInputMethod);
            q->killTimer(recognizeTimer);
            recognizeTimer = 0;
        }
    }

    void resultsAvailable(const QVariantList &resultList)
    {
        if (!resultList.isEmpty()) {
            const QVariantMap result = resultList.at(0).toMap();
            if (recognitionTask && recognitionTask->resultId() == result["resultId"].toInt())
                delayedResult = result;
            else
                processResult(result);
        }
    }

    void processResult(const QVariantMap &result)
    {
        const QChar ch = result["unicode"].toChar();
        const QChar chUpper = ch.toUpper();
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
        // In recording mode, the text case must match with the current text case
        if (unipenTrace) {
            if (!ch.isLetter() || (ch.isUpper() == (textCase == InputEngine::Upper)))
                saveTraces(ch.unicode(), qRound(result["confidence"].toDouble() * 100));
            delete unipenTrace;
            unipenTrace = 0;
        }
#endif
        Q_Q(LipiInputMethod);
        q->inputContext()->inputEngine()->virtualKeyClick((Qt::Key)chUpper.unicode(),
                    textCase == InputEngine::Lower ? QString(ch.toLower()) : QString(chUpper),
                    Qt::NoModifier);
    }

#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
    void dumpTraces()
    {
        if (unipenTrace)
            unipenTrace->record(traceList);
    }

    void saveTraces(uint unicode, uint confidence)
    {
        if (!unipenTrace)
            return;

        QStringList homeLocations = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
        if (!homeLocations.isEmpty()) {
            QString filePath = QStringLiteral("%1/%2").arg(homeLocations.at(0)).arg("VIRTUAL_KEYBOARD_TRACES");
            unipenTrace->setDirectory(filePath);
            unipenTrace->save(unicode, confidence);
        }
    }
#endif

    LipiInputMethod *q_ptr;
    LipiSharedRecognizer recognizer;
    QByteArray currentContext;
    QScopedPointer<LTKCaptureDevice> deviceInfo;
    QScopedPointer<LTKScreenContext> screenContext;
    QSharedPointer<LipiRecognitionTask> recognitionTask;
    LTKTraceGroup traceGroup;
    QList<Trace *> traceList;
    int recognizeTimer;
    InputEngine::TextCase textCase;
    vector<int> subsetOfClasses;
    QVariantMap delayedResult;
    HandwritingGestureRecognizer gestureRecognizer;
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
    UnipenTrace *unipenTrace;
#endif
};

/*!
    \class QtVirtualKeyboard::LipiInputMethod
    \internal
*/

LipiInputMethod::LipiInputMethod(QObject *parent) :
    LipiInputMethodBase(*new LipiInputMethodPrivate(this), parent)
{
}

LipiInputMethod::~LipiInputMethod()
{
}

QList<InputEngine::InputMode> LipiInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale)
    QList<InputEngine::InputMode> availableInputModes;
    const Qt::InputMethodHints inputMethodHints(inputContext()->inputMethodHints());

    if (inputMethodHints.testFlag(Qt::ImhDialableCharactersOnly) || inputMethodHints.testFlag(Qt::ImhDigitsOnly)) {
        availableInputModes.append(InputEngine::Dialable);
    } else if (inputMethodHints.testFlag(Qt::ImhFormattedNumbersOnly)) {
        availableInputModes.append(InputEngine::Numeric);
    } else {
        availableInputModes.append(InputEngine::Latin);
        availableInputModes.append(InputEngine::Numeric);
    }

    return availableInputModes;
}

bool LipiInputMethod::setInputMode(const QString &locale, InputEngine::InputMode inputMode)
{
    Q_D(LipiInputMethod);
#ifdef HAVE_HUNSPELL
    HunspellInputMethod::setInputMode(locale, inputMode);
#else
    Q_UNUSED(locale)
#endif
    bool result = d->recognizer.setModel(QStringLiteral("SHAPEREC_ALPHANUM"));
    if (!result)
        return false;
    d->subsetOfClasses.clear();
    switch (inputMode) {
    case InputEngine::Latin:
        d->recognizer.subsetOfClasses(QStringLiteral("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz?,.@"), d->subsetOfClasses);
        break;
    case InputEngine::Numeric:
    case InputEngine::Dialable:
        d->recognizer.subsetOfClasses(QStringLiteral("1234567890,.+"), d->subsetOfClasses);
        break;
    default:
        break;
    }
    return true;
}

bool LipiInputMethod::setTextCase(InputEngine::TextCase textCase)
{
    Q_D(LipiInputMethod);
    d->textCase = textCase;
#ifdef HAVE_HUNSPELL
    HunspellInputMethod::setTextCase(textCase);
#endif
    return true;
}

bool LipiInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
#ifdef HAVE_HUNSPELL
    Q_D(LipiInputMethod);
    switch (key) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        d->cancelRecognition();
        break;
    case Qt::Key_Backspace:
        if (d->cancelRecognition())
            return true;
        break;
    default:
        break;
    }
    return HunspellInputMethod::keyEvent(key, text, modifiers);
#else
    Q_UNUSED(key)
    Q_UNUSED(text)
    Q_UNUSED(modifiers)
    return false;
#endif
}

void LipiInputMethod::reset()
{
    LipiInputMethodBase::reset();
    Q_D(LipiInputMethod);
    d->cancelRecognition();
}

void LipiInputMethod::update()
{
    LipiInputMethodBase::update();
}

void LipiInputMethod::selectionListItemSelected(SelectionListModel::Type type, int index)
{
    LipiInputMethodBase::selectionListItemSelected(type, index);
    Q_D(LipiInputMethod);
    d->cancelRecognition();
}

QList<InputEngine::PatternRecognitionMode> LipiInputMethod::patternRecognitionModes() const
{
    return QList<InputEngine::PatternRecognitionMode>()
            << InputEngine::HandwritingRecoginition;
}

Trace *LipiInputMethod::traceBegin(int traceId, InputEngine::PatternRecognitionMode patternRecognitionMode,
                                   const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo)
{
    Q_D(LipiInputMethod);
    return d->traceBegin(traceId, patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo);
}

bool LipiInputMethod::traceEnd(Trace *trace)
{
    Q_D(LipiInputMethod);
    d->traceEnd(trace);
    return true;
}

void LipiInputMethod::timerEvent(QTimerEvent *timerEvent)
{
    Q_D(LipiInputMethod);
    if (timerEvent->timerId() == d->recognizeTimer) {
        d->finishRecognition();
    }
}

void LipiInputMethod::resultsAvailable(const QVariantList &resultList)
{
#ifdef QT_VIRTUALKEYBOARD_DEBUG
    {
        VIRTUALKEYBOARD_DEBUG() << "LipiInputMethod::resultsAvailable():";
        for (int i = 0; i < resultList.size(); i++) {
            QVariantMap result = resultList.at(i).toMap();
            VIRTUALKEYBOARD_DEBUG() << QString("%1: %2 (%3)").arg(i + 1).arg(result["unicode"].toChar()).arg(result["confidence"].toFloat()).toUtf8().constData();
        }
    }
#endif
    Q_D(LipiInputMethod);
    d->resultsAvailable(resultList);
}

} // namespace QtVirtualKeyboard
