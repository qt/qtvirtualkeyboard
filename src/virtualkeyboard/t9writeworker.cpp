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

#include "t9writeworker.h"
#include "virtualkeyboarddebug.h"

#include <QFile>
#include <QTime>

namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::T9WriteTask
    \internal
*/

T9WriteTask::T9WriteTask(QObject *parent) :
    QObject(parent),
    decumaSession(0),
    runSema()
{
}

void T9WriteTask::wait()
{
    runSema.acquire();
    runSema.release();
}

/*!
    \class QtVirtualKeyboard::T9WriteDictionaryTask
    \internal
*/

T9WriteDictionaryTask::T9WriteDictionaryTask(QSharedPointer<T9WriteDictionary> dictionary,
                                             const QString &dictionaryFileName,
                                             bool convertDictionary,
                                             const DECUMA_SRC_DICTIONARY_INFO &dictionaryInfo) :
    dictionary(dictionary),
    dictionaryFileName(dictionaryFileName),
    convertDictionary(convertDictionary),
    dictionaryInfo(dictionaryInfo)
{
}

void T9WriteDictionaryTask::run()
{
    VIRTUALKEYBOARD_DEBUG() << "T9WriteDictionaryTask::run()";

#ifdef QT_VIRTUALKEYBOARD_DEBUG
    QTime perf;
    perf.start();
#endif

    bool result = false;
    if (dictionary) {
        result = dictionary->load(dictionaryFileName);
        if (result && convertDictionary)
            result = dictionary->convert(dictionaryInfo);
    }

#ifdef QT_VIRTUALKEYBOARD_DEBUG
    VIRTUALKEYBOARD_DEBUG() << "T9WriteDictionaryTask::run(): time:" << perf.elapsed() << "ms";
#endif

    if (result)
        emit completed(dictionary);
}

T9WriteAddArcTask::T9WriteAddArcTask(Trace *trace) :
    trace(trace)
{
}

void T9WriteAddArcTask::run()
{
#ifdef QT_VIRTUALKEYBOARD_DEBUG
    QTime perf;
    perf.start();
#endif
    DECUMA_UINT32 arcID = (DECUMA_UINT32)trace->traceId();
    DECUMA_STATUS status = DECUMA_API(StartNewArc)(decumaSession, arcID);
    Q_ASSERT(status == decumaNoError);
    if (status != decumaNoError) {
        qWarning() << "T9WriteAddArcTask::run(): Failed to start new arc, status:" << status;
        return;
    }

    const QVariantList points = trace->points();
    Q_ASSERT(!points.isEmpty());

    for (const QVariant &p : points) {
        const QPoint pt(p.toPointF().toPoint());
        status = DECUMA_API(AddPoint)(decumaSession, (DECUMA_COORD)pt.x(),(DECUMA_COORD)pt.y(), arcID);
        if (status != decumaNoError) {
            qWarning() << "T9WriteAddArcTask::run(): Failed to add point, status:" << status;
            DECUMA_API(CancelArc)(decumaSession, arcID);
            return;
        }
    }

    status = DECUMA_API(CommitArc)(decumaSession, arcID);
    if (status != decumaNoError)
        qWarning() << "T9WriteAddArcTask::run(): Failed to commit arc, status:" << status;
#ifdef QT_VIRTUALKEYBOARD_DEBUG
    else
        VIRTUALKEYBOARD_DEBUG() << "T9WriteAddArcTask::run(): time:" << perf.elapsed() << "ms";
#endif
}

/*!
    \class QtVirtualKeyboard::T9WriteRecognitionResult
    \internal
*/

T9WriteRecognitionResult::T9WriteRecognitionResult(int id, int maxResults, int maxCharsPerWord) :
    status(decumaNoError),
    numResults(0),
    instantGesture(0),
    id(id),
    maxResults(maxResults),
    maxCharsPerWord(maxCharsPerWord)
{
    Q_ASSERT(maxResults > 0);
    Q_ASSERT(maxCharsPerWord > 0);
    results.resize(maxResults);
    int bufferLength = (maxCharsPerWord + 1);
    _chars.resize(maxResults * bufferLength);
    _symbolChars.resize(maxResults * bufferLength);
    _symbolStrokes.resize(maxResults * bufferLength);
    for (int i = 0; i < maxResults; i++) {
        DECUMA_HWR_RESULT &hwrResult = results[i];
        hwrResult.pChars = &_chars[i * bufferLength];
        hwrResult.pSymbolChars = &_symbolChars[i * bufferLength];
        hwrResult.pSymbolStrokes = &_symbolStrokes[i * bufferLength];
    }
}

/*!
    \class QtVirtualKeyboard::T9WriteRecognitionTask
    \internal
*/

T9WriteRecognitionTask::T9WriteRecognitionTask(QSharedPointer<T9WriteRecognitionResult> result,
                                               const DECUMA_INSTANT_GESTURE_SETTINGS &instantGestureSettings,
                                               BOOST_LEVEL boostLevel,
                                               const QString &stringStart) :
    T9WriteTask(),
    result(result),
    instantGestureSettings(instantGestureSettings),
    boostLevel(boostLevel),
    stringStart(stringStart),
    stateCancelled(false)
{
    VIRTUALKEYBOARD_DEBUG() << "T9WriteRecognitionTask():" << "boostLevel:" << boostLevel << "stringStart:" << stringStart;
}

void T9WriteRecognitionTask::run()
{
    if (!decumaSession)
        return;

    {
        QMutexLocker stateGuard(&stateLock);
        Q_UNUSED(stateGuard);
        if (stateCancelled)
            return;
    }

    //In a normal text composition case boostDictWords and canBeContinued are the preffered settings
    DECUMA_RECOGNITION_SETTINGS recSettings;
    memset(&recSettings, 0, sizeof(recSettings));
    recSettings.boostLevel = boostLevel;
    recSettings.stringCompleteness = canBeContinued;
    if (!stringStart.isEmpty())
        recSettings.pStringStart = (DECUMA_UNICODE *)stringStart.utf16();

#ifdef QT_VIRTUALKEYBOARD_DEBUG
    QTime perf;
    perf.start();
#endif

#if SUPPORTS_ABORTRECOGNITION
    DECUMA_INTERRUPT_FUNCTIONS interruptFunctions;
    interruptFunctions.pShouldAbortRecognize = shouldAbortRecognize;
    interruptFunctions.pUserData = (void *)this;
    DECUMA_INTERRUPT_FUNCTIONS *pInterruptFunctions = &interruptFunctions;
#else
    DECUMA_INTERRUPT_FUNCTIONS *pInterruptFunctions = NULL;
#endif
    result->status = DECUMA_API(Recognize)(decumaSession, result->results.data(), result->results.size(), &result->numResults, result->maxCharsPerWord, &recSettings, pInterruptFunctions);
    if (result->status != decumaNoError)
        qWarning() << "T9WriteRecognitionTask::run(): Recognition failed, status:" << result->status;

#ifdef QT_VIRTUALKEYBOARD_DEBUG
    int perfElapsed = perf.elapsed();
#endif

    {
        QMutexLocker stateGuard(&stateLock);
        Q_UNUSED(stateGuard)
        if (stateCancelled)
            result.reset();
#ifdef QT_VIRTUALKEYBOARD_DEBUG
        VIRTUALKEYBOARD_DEBUG() << "T9WriteRecognitionTask::run(): time:" << perfElapsed << "ms" << (stateCancelled ? "(cancelled)" : "");
#endif
    }
}

int T9WriteRecognitionTask::shouldAbortRecognize(void *pUserData)
{
    T9WriteRecognitionTask *pThis = (T9WriteRecognitionTask *)pUserData;
    QMutexLocker stateGuard(&pThis->stateLock);
    Q_UNUSED(stateGuard)
    return pThis->stateCancelled;
}

bool T9WriteRecognitionTask::cancelRecognition()
{
    QMutexLocker stateGuard(&stateLock);
    Q_UNUSED(stateGuard)
    stateCancelled = true;
    return true;
}

int T9WriteRecognitionTask::resultId() const
{
    return result != 0 ? result->id : -1;
}

/*!
    \class QtVirtualKeyboard::T9WriteRecognitionResultsTask
    \internal
*/

T9WriteRecognitionResultsTask::T9WriteRecognitionResultsTask(QSharedPointer<T9WriteRecognitionResult> result) :
    T9WriteTask(),
    result(result)
{
}

void T9WriteRecognitionResultsTask::run()
{
    if (!result)
        return;

    if (result->status != decumaNoError) {
        emit recognitionError(result->status);
        return;
    }

    QVariantList resultList;
    for (int i = 0; i < result->numResults; i++)
    {
        QVariantMap resultMap;
        QString resultString;
        QString gesture;
        const DECUMA_HWR_RESULT &hwrResult = result->results.at(i);
        resultString.reserve(hwrResult.nChars);
        QVariantList symbolStrokes;
        int charPos = 0;
        for (int symbolIndex = 0; symbolIndex < hwrResult.nSymbols; symbolIndex++) {
            int symbolLength = hwrResult.pSymbolChars[symbolIndex];
            QString symbol(QString::fromUtf16(&hwrResult.pChars[charPos], symbolLength));
            // Do not append gesture symbol to result string
            if (hwrResult.bGesture) {
                gesture = symbol.right(1);
                symbol.chop(1);
            }
            resultString.append(symbol);
            charPos += symbolLength;
            if (hwrResult.pSymbolStrokes)
                symbolStrokes.append(QVariant((int)hwrResult.pSymbolStrokes[symbolIndex]));
        }

        resultMap["resultId"] = result->id;
        resultMap["chars"] = resultString;
        resultMap["symbolStrokes"] = symbolStrokes;
        if (!gesture.isEmpty())
            resultMap["gesture"] = gesture;

        resultList.append(resultMap);
    }

    if (resultList.isEmpty())
        return;

    emit resultsAvailable(resultList);
}

/*!
    \class QtVirtualKeyboard::T9WriteWorker
    \internal
*/

T9WriteWorker::T9WriteWorker(DECUMA_SESSION *decumaSession, const bool cjk, QObject *parent) :
    QThread(parent),
    taskSema(),
    taskLock(),
    decumaSession(decumaSession),
    cjk(cjk)
{
    abort = false;
}

T9WriteWorker::~T9WriteWorker()
{
    abort = true;
    taskSema.release();
    wait();
}

void T9WriteWorker::addTask(QSharedPointer<T9WriteTask> task)
{
    if (task) {
        QMutexLocker guard(&taskLock);
        task->moveToThread(this);
        taskList.append(task);
        taskSema.release();
    }
}

int T9WriteWorker::removeTask(QSharedPointer<T9WriteTask> task)
{
    int count = 0;
    if (task) {
        QMutexLocker guard(&taskLock);
        count = taskList.removeAll(task);
        taskSema.acquire(qMin(count, taskSema.available()));
    }
    return count;
}

int T9WriteWorker::removeAllTasks()
{
    QMutexLocker guard(&taskLock);
    int count = taskList.count();
    taskList.clear();
    if (taskSema.available())
        taskSema.acquire(taskSema.available());
    return count;
}

void T9WriteWorker::waitForAllTasks()
{
    while (isRunning()) {
        idleSema.acquire();
        QMutexLocker guard(&taskLock);
        if (taskList.isEmpty()) {
            idleSema.release();
            break;
        }
        idleSema.release();
    }
}

int T9WriteWorker::numberOfPendingTasks()
{
    QMutexLocker guard(&taskLock);
    return taskList.count() + !idleSema.available() ? 1 : 0;
}

void T9WriteWorker::run()
{
    while (!abort) {
        idleSema.release();
        taskSema.acquire();
        if (abort)
            break;
        idleSema.acquire();
        QSharedPointer<T9WriteTask> currentTask;
        {
            QMutexLocker guard(&taskLock);
            if (!taskList.isEmpty()) {
                currentTask = taskList.front();
                taskList.pop_front();
            }
        }
        if (currentTask) {
            currentTask->decumaSession = decumaSession;
            currentTask->cjk  = cjk;
            currentTask->run();
            currentTask->runSema.release();
        }
    }
}

} // namespace QtVirtualKeyboard
