/****************************************************************************
**
** Copyright (C) 2015 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

#include "lipiinputmethod.h"
#include "lipisharedrecognizer.h"
#include "declarativeinputengine.h"
#include "declarativeinputcontext.h"
#include "virtualkeyboarddebug.h"
#include "declarativetrace.h"

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

#ifdef HAVE_HUNSPELL
#define LipiInputMethodPrivateBase HunspellInputMethodPrivate
#else
#define LipiInputMethodPrivateBase AbstractInputMethodPrivate
#endif

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
        textCase(DeclarativeInputEngine::Lower)
    {
    }

    ~LipiInputMethodPrivate()
    {
        cancelRecognition();
    }

    QByteArray getContext(DeclarativeInputEngine::PatternRecognitionMode patternRecognitionMode,
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

    void setContext(DeclarativeInputEngine::PatternRecognitionMode patternRecognitionMode,
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

        currentContext = context;
    }

    DeclarativeTrace *traceBegin(DeclarativeInputEngine::PatternRecognitionMode patternRecognitionMode,
                                 const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo)
    {
        stopRecognizeTimer();

        setContext(patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo);

        if (!recognitionTask) {
            recognitionTask = recognizer.newRecognition(*deviceInfo, *screenContext, subsetOfClasses, 0.0f, 4);
            if (!recognitionTask)
                return 0;
        }

        DeclarativeTrace *trace = new DeclarativeTrace();
        trace->setChannels(QStringList("t"));
        traceList.append(trace);

        return trace;
    }

    void traceEnd(DeclarativeTrace *trace)
    {
        if (trace->isCanceled()) {
            VIRTUALKEYBOARD_DEBUG() << "LipiInputMethodPrivate::traceEnd(): discarded" << trace;
            traceList.removeOne(trace);
            delete trace;
        } else {
            addPointsToTraceGroup(trace);
        }
        if (!traceList.isEmpty() && countActiveTraces() == 0)
            resetRecognizeTimer();
    }

    int countActiveTraces() const {
        int count = 0;
        foreach (DeclarativeTrace *trace, traceList) {
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

    void addPointsToTraceGroup(DeclarativeTrace *trace)
    {
        if (!recognitionTask)
            return;
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
        foreach (const QVariant &p, points) {
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
        recognitionTask->traceGroup.addTrace(ltktrace);
    }

    void recognize()
    {
        stopRecognizeTimer();
        clearTraces();

        if (recognitionTask) {
            Q_Q(LipiInputMethod);

            QSharedPointer<LipiRecognitionResultsTask> resultsTask = recognizer.startRecognition(recognitionTask);
            q->connect(resultsTask.data(), SIGNAL(resultsAvailable(const QVariantList &)), SLOT(resultsAvailable(const QVariantList &)));

            recognitionTask.reset();
        }
    }

    bool cancelRecognition()
    {
        stopRecognizeTimer();
        clearTraces();
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

    LipiInputMethod *q_ptr;
    LipiSharedRecognizer recognizer;
    QByteArray currentContext;
    QScopedPointer<LTKCaptureDevice> deviceInfo;
    QScopedPointer<LTKScreenContext> screenContext;
    QSharedPointer<LipiRecognitionTask> recognitionTask;
    QList<DeclarativeTrace *> traceList;
    int recognizeTimer;
    DeclarativeInputEngine::TextCase textCase;
    vector<int> subsetOfClasses;
};

LipiInputMethod::LipiInputMethod(QObject *parent) :
    LipiInputMethodBase(*new LipiInputMethodPrivate(this), parent)
{
}

LipiInputMethod::~LipiInputMethod()
{
}

QList<DeclarativeInputEngine::InputMode> LipiInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale)
    return QList<DeclarativeInputEngine::InputMode>()
            << DeclarativeInputEngine::Latin
            << DeclarativeInputEngine::Numeric;
}

bool LipiInputMethod::setInputMode(const QString &locale, DeclarativeInputEngine::InputMode inputMode)
{
    Q_UNUSED(locale)
    Q_D(LipiInputMethod);
#ifdef HAVE_HUNSPELL
    HunspellInputMethod::setInputMode(locale, inputMode);
#endif
    bool result = d->recognizer.setModel(QStringLiteral("SHAPEREC_ALPHANUM"));
    if (!result)
        return false;
    d->subsetOfClasses.clear();
    switch (inputMode) {
    case DeclarativeInputEngine::Latin:
        d->recognizer.subsetOfClasses(QStringLiteral("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz?,.@"), d->subsetOfClasses);
        break;
    case DeclarativeInputEngine::Numeric:
        d->recognizer.subsetOfClasses(QStringLiteral("1234567890,."), d->subsetOfClasses);
        break;
    default:
        break;
    }
    return true;
}

bool LipiInputMethod::setTextCase(DeclarativeInputEngine::TextCase textCase)
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

void LipiInputMethod::selectionListItemSelected(DeclarativeSelectionListModel::Type type, int index)
{
    LipiInputMethodBase::selectionListItemSelected(type, index);
    Q_D(LipiInputMethod);
    d->cancelRecognition();
}

QList<DeclarativeInputEngine::PatternRecognitionMode> LipiInputMethod::patternRecognitionModes() const
{
    return QList<DeclarativeInputEngine::PatternRecognitionMode>()
            << DeclarativeInputEngine::HandwritingRecoginition;
}

DeclarativeTrace *LipiInputMethod::traceBegin(DeclarativeInputEngine::PatternRecognitionMode patternRecognitionMode,
                                              const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo)
{
    Q_D(LipiInputMethod);
    return d->traceBegin(patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo);
}

bool LipiInputMethod::traceEnd(DeclarativeTrace *trace)
{
    Q_D(LipiInputMethod);
    d->traceEnd(trace);
    return true;
}

void LipiInputMethod::timerEvent(QTimerEvent *timerEvent)
{
    Q_D(LipiInputMethod);
    if (timerEvent->timerId() == d->recognizeTimer) {
        d->recognize();
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
    if (!resultList.isEmpty()) {
        Q_D(LipiInputMethod);
        QVariantMap result = resultList.at(0).toMap();
        QChar ch = result["unicode"].toChar().toUpper();
        inputContext()->inputEngine()->virtualKeyClick((Qt::Key)ch.unicode(),
                    d->textCase == DeclarativeInputEngine::Lower ? QString(ch.toLower()) : QString(ch),
                    Qt::NoModifier);
    }
}
