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

#include "lipiworker.h"
#include "virtualkeyboarddebug.h"

#include <QTime>

#include "LTKShapeRecognizer.h"
#include "LTKErrors.h"

void LipiLoadModelDataTask::run()
{
    VIRTUALKEYBOARD_DEBUG() << "LipiLoadModelDataTask::run()";
#ifdef QT_VIRTUALKEYBOARD_DEBUG
    QTime perf;
    perf.start();
#endif
    int result = shapeRecognizer->loadModelData();
#ifdef QT_VIRTUALKEYBOARD_DEBUG
    VIRTUALKEYBOARD_DEBUG() << "LipiLoadModelDataTask::run(): time:" << perf.elapsed() << "ms";
#endif
    if (result != SUCCESS)
        qWarning() << QString("Error %1: %2").arg(result).arg(getErrorMessage(result).c_str());
}

LipiRecognitionTask::LipiRecognitionTask(const LTKCaptureDevice& deviceInfo,
                                         const LTKScreenContext& screenContext,
                                         const vector<int>& inSubsetOfClasses,
                                         float confThreshold,
                                         int numChoices) :
    LipiTask(),
    deviceInfo(deviceInfo),
    screenContext(screenContext),
    inSubsetOfClasses(inSubsetOfClasses),
    confThreshold(confThreshold),
    numChoices(numChoices),
    resultVector(new vector<LTKShapeRecoResult>())
{
}

void LipiRecognitionTask::run()
{
    VIRTUALKEYBOARD_DEBUG() << "LipiRecognitionTask::run()";

    if (!shapeRecognizer || !resultVector)
        return;

    resultVector->reserve(numChoices);

    shapeRecognizer->setDeviceContext(deviceInfo);

#ifdef QT_VIRTUALKEYBOARD_DEBUG
    QTime perf;
    perf.start();
#endif
    shapeRecognizer->recognize(traceGroup, screenContext,
                               inSubsetOfClasses, confThreshold,
                               numChoices, *resultVector);
#ifdef QT_VIRTUALKEYBOARD_DEBUG
    VIRTUALKEYBOARD_DEBUG() << "LipiRecognitionTask::run(): time:" << perf.elapsed() << "ms";
#endif
}

LipiRecognitionResultsTask::LipiRecognitionResultsTask(QSharedPointer<vector<LTKShapeRecoResult> > resultVector,
                                                       const QMap<int, QChar> &unicodeMap) :
    LipiTask(),
    resultVector(resultVector),
    unicodeMap(unicodeMap)
{
}

void LipiRecognitionResultsTask::run()
{
    if (!resultVector || unicodeMap.isEmpty())
        return;

    QVariantList resultList;
    for (vector<LTKShapeRecoResult>::const_iterator i = resultVector->begin();
         i != resultVector->end(); i++) {
        QVariantMap result;
        int shapeId = i->getShapeId();
        result["shapeId"] = shapeId;
        result["unicode"] = unicodeMap.value(shapeId);
        result["confidence"] = i->getConfidence();
        resultList.append(result);
    }

    emit resultsAvailable(resultList);
}

LipiWorker::LipiWorker(LTKShapeRecognizer *shapeRecognizer, QObject *parent) :
    QThread(parent),
    taskSema(),
    taskLock(),
    shapeRecognizer(shapeRecognizer),
    abort(false)
{
}

LipiWorker::~LipiWorker()
{
    abort = true;
    taskSema.release();
    wait();
    if (shapeRecognizer)
        shapeRecognizer->unloadModelData();
}

void LipiWorker::addTask(QSharedPointer<LipiTask> task)
{
    if (task) {
        QMutexLocker guard(&taskLock);
        taskList.append(task);
        taskSema.release();
    }
}

int LipiWorker::removeAllTasks()
{
    QMutexLocker guard(&taskLock);
    int count = taskList.count();
    taskList.clear();
    if (taskSema.available())
        taskSema.acquire(taskSema.available());
    return count;
}

void LipiWorker::run()
{
    while (!abort) {
        taskSema.acquire();
        if (abort)
            break;
        QSharedPointer<LipiTask> currentTask;
        {
            QMutexLocker guard(&taskLock);
            if (!taskList.isEmpty()) {
                currentTask = taskList.front();
                taskList.pop_front();
            }
        }
        if (currentTask) {
            currentTask->shapeRecognizer = shapeRecognizer;
            currentTask->run();
        }
    }
}
