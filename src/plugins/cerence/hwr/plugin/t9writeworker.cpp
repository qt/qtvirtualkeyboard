// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "t9writeworker_p.h"
#include <QLoggingCategory>

#include <QFile>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Q_DECLARE_LOGGING_CATEGORY(lcT9Write)

/*!
    \class QtVirtualKeyboard::T9WriteTask
    \internal
*/

T9WriteTask::T9WriteTask(QObject *parent) :
    QObject(parent),
    decumaSession(nullptr),
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

T9WriteDictionaryTask::T9WriteDictionaryTask(QSharedPointer<T9WriteAbstractDictionary> dictionary,
                                             bool convertDictionary) :
    dictionary(dictionary),
    convertDictionary(convertDictionary)
{
}

void T9WriteDictionaryTask::run()
{
    qCDebug(lcT9Write) << "T9WriteDictionaryTask::run()";

    QElapsedTimer perf;
    perf.start();

    bool result = false;
    if (dictionary) {
        result = dictionary->load();
        if (result && convertDictionary)
            result = dictionary->convert();
    }

    qCDebug(lcT9Write) << "T9WriteDictionaryTask::run(): time:" << perf.elapsed() << "ms";

    if (result) {
        dictionary->state++;
        emit completed(dictionary);
    }
}

T9WriteAddArcTask::T9WriteAddArcTask(QVirtualKeyboardTrace *trace) :
    trace(trace)
{
}

void T9WriteAddArcTask::run()
{
    QElapsedTimer perf;
    perf.start();
    DECUMA_UINT32 arcID = (DECUMA_UINT32)trace->traceId();
    DECUMA_STATUS status = DECUMA_API(StartNewArc)(decumaSession, arcID);
    Q_ASSERT(status == decumaNoError);
    if (status != decumaNoError) {
        qCWarning(lcT9Write) << "T9WriteAddArcTask::run(): Failed to start new arc, status:" << status;
        return;
    }

    const QVariantList points = trace->points();
    Q_ASSERT(!points.isEmpty());

    for (const QVariant &p : points) {
        const QPoint pt(p.toPointF().toPoint());
        status = DECUMA_API(AddPoint)(decumaSession, (DECUMA_COORD)pt.x(),(DECUMA_COORD)pt.y(), arcID);
        if (status != decumaNoError) {
            qCWarning(lcT9Write) << "T9WriteAddArcTask::run(): Failed to add point, status:" << status;
            DECUMA_API(CancelArc)(decumaSession, arcID);
            return;
        }
    }

    status = DECUMA_API(CommitArc)(decumaSession, arcID);
    if (status != decumaNoError)
        qCWarning(lcT9Write) << "T9WriteAddArcTask::run(): Failed to commit arc, status:" << status;
    else
        qCDebug(lcT9Write) << "T9WriteAddArcTask::run(): time:" << perf.elapsed() << "ms";
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

T9WriteRecognitionTask::T9WriteRecognitionTask(QSharedPointer<T9WriteRecognitionResult> result) :
    T9WriteTask(),
    result(result),
    stateCancelled(false)
{
}

void T9WriteRecognitionTask::run()
{
    if (!decumaSession)
        return;

    perf.start();

    while (true) {
        DECUMA_BG_REC_STATE bgRecState = bgRecIdle;
        DECUMA_STATUS status = DECUMA_API(GetBackgroundRecognitionState(decumaSession, &bgRecState));
        if (status) {
            qCDebug(lcT9Write) << "T9WriteRecognitionTask::run(): GetBackgroundRecognitionState failed, status:" << status;
            break;
        }

        if (bgRecState != bgRecStarted) {
            qCDebug(lcT9Write) << "T9WriteRecognitionTask::run(): state:" << bgRecState << "time:" << perf.elapsed() << "ms";
            break;
        }

        if (checkCancelled())
            return;

        QThread::msleep(25);

        if (checkCancelled())
            return;
    }

    result->status = DECUMA_API(Recognize)(decumaSession, result->results.data(), result->results.size(), &result->numResults, result->maxCharsPerWord, nullptr, nullptr);
    if (result->status != decumaNoError)
        qCWarning(lcT9Write) << "T9WriteRecognitionTask::run(): Recognition failed, status:" << result->status;

    if (checkCancelled())
        return;

    qCDebug(lcT9Write) << "T9WriteRecognitionTask::run(): time:" << perf.elapsed() << "ms";
}

bool T9WriteRecognitionTask::cancelRecognition()
{
    QMutexLocker stateGuard(&stateLock);
    Q_UNUSED(stateGuard)
    stateCancelled = true;
    return true;
}

bool T9WriteRecognitionTask::checkCancelled()
{
    QMutexLocker stateGuard(&stateLock);
    Q_UNUSED(stateGuard)
    if (stateCancelled) {
        result.reset();
        qCDebug(lcT9Write) << "T9WriteRecognitionTask cancelled, time:" << perf.elapsed() << "ms";
        return true;
    }

    return false;
}

int T9WriteRecognitionTask::resultId() const
{
    return result != nullptr ? result->id : -1;
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
            QString symbol(QString::fromUtf16(reinterpret_cast<const char16_t *>(&hwrResult.pChars[charPos]), symbolLength));
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

        resultMap[QLatin1String("resultId")] = result->id;
        resultMap[QLatin1String("chars")] = resultString;
        resultMap[QLatin1String("symbolStrokes")] = symbolStrokes;
        if (!gesture.isEmpty())
            resultMap[QLatin1String("gesture")] = gesture;

        resultList.append(resultMap);
    }

    if (resultList.isEmpty()) {
        qCDebug(lcT9Write) << "T9WriteRecognitionResultsTask::run(): no results available";
        return;
    }

    qCDebug(lcT9Write) << "T9WriteRecognitionResultsTask::run():" << resultList.size() << "results available";
    emit resultsAvailable(resultList);
}

/*!
    \class QtVirtualKeyboard::T9WriteLearnWordTask
    \internal
*/

T9WriteDlmWordTask::T9WriteDlmWordTask(QSharedPointer<T9WriteAbstractDictionary> dlmDictionary, const QString &word, const QString &stringStart) :
    T9WriteTask(),
    dlmDictionary(dlmDictionary),
    word(word),
    stringStart(stringStart)
{

}

void T9WriteDlmWordTask::run()
{
    DECUMA_RECOGNITION_SETTINGS recSettings;
    memset(&recSettings, 0, sizeof(recSettings));
    recSettings.boostLevel = boostDictWords;
    recSettings.stringCompleteness = canBeContinued;
    if (!stringStart.isEmpty())
        recSettings.pStringStart = const_cast<DECUMA_UNICODE *>(stringStart.utf16());

    DECUMA_UINT16 nDictionaries = 0;
    DECUMA_STATUS status = DECUMA_API(GetNAttachedDictionaries)(decumaSession, &nDictionaries);
    if (status)
        return;

    bool wordFound = false;
    if (nDictionaries != 0) {
        QVector<DECUMA_MATCH_RESULT> matchResults;
        matchResults.resize(nDictionaries);
        status = DECUMA_API(MatchWord)(decumaSession, word.utf16(),
                                       static_cast<DECUMA_UINT16>(word.length()),
                                       &recSettings, matchResults.data());
        if (!status) {
            for (const auto &matchResult : std::as_const(matchResults)) {
                qCDebug(lcT9Write) << "T9WriteDlmWordTask::run(): MatchWord string type" << matchResult.stringType;
                if (matchResult.stringType != notFromDictionary) {
                    wordFound = true;
                    break;
                }
            }
        } else {
            qCDebug(lcT9Write) << "T9WriteDlmWordTask::run(): MatchWord failed" << status;
            return;
        }
    }

    if (!wordFound) {
        qCDebug(lcT9Write) << "T9WriteDlmWordTask::run(): DynamicDictionaryAddWord";
        status = DECUMA_API(DynamicDictionaryAddWord)(
                    const_cast<DECUMA_DYNAMIC_DICTIONARY *>(
                        reinterpret_cast<const DECUMA_DYNAMIC_DICTIONARY *>(dlmDictionary->data())),
                    word.utf16());

        if (!status) {
            persist();
        }
    }
}

void T9WriteDlmWordTask::persist()
{
    T9WriteDynamicDictionary *dictionary = static_cast<T9WriteDynamicDictionary *>(dlmDictionary.data());

    QElapsedTimer perf;
    perf.start();

    dictionary->save();

    qCDebug(lcT9Write) << "T9WriteDlmWordTask::persist(): time:" << perf.elapsed() << "ms";
}

/*!
    \class QtVirtualKeyboard::T9WriteDlmRemoveWordTask
    \internal
*/

T9WriteDlmRemoveWordTask::T9WriteDlmRemoveWordTask(QSharedPointer<T9WriteAbstractDictionary> dlmDictionary, const QString &word) :
    T9WriteDlmWordTask(dlmDictionary, word, QString())
{

}

void T9WriteDlmRemoveWordTask::run()
{
    T9WriteDynamicDictionary *dictionary = static_cast<T9WriteDynamicDictionary *>(dlmDictionary.data());
    if (dictionary->removeWord(word)) {
        persist();
    }
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
        const bool isRunning = taskList.indexOf(task) == 0;
        if (isRunning) {
            task->wait();
        } else if (taskList.removeOne(task)) {
            ++count;
            task->runSema.release();
        }
    }
    return count;
}

int T9WriteWorker::removeAllTasks()
{
    idleSema.acquire();
    QMutexLocker guard(&taskLock);
    int count = taskList.size();
    for (QSharedPointer<T9WriteTask> task : taskList) {
        task->runSema.release();
    }
    taskList.clear();
    idleSema.release();
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
    return taskList.size();
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
            }
        }
        if (currentTask) {
            currentTask->decumaSession = decumaSession;
            currentTask->cjk  = cjk;
            currentTask->run();
            currentTask->runSema.release();
            QMutexLocker guard(&taskLock);
            taskList.removeOne(currentTask);
        }
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
