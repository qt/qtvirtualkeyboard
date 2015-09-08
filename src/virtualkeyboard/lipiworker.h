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

#ifndef LIPIWORKER_H
#define LIPIWORKER_H

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QStringList>
#include <QSharedPointer>
#include <QMap>

#include "LTKTypes.h"
#include "LTKCaptureDevice.h"
#include "LTKScreenContext.h"
#include "LTKTraceGroup.h"
#include "LTKChannel.h"
#include "LTKTraceFormat.h"
#include "LTKTrace.h"
#include "LTKShapeRecognizer.h"
#include "LTKShapeRecoResult.h"

class LipiTask : public QObject
{
    Q_OBJECT
public:
    explicit LipiTask(QObject *parent = 0) :
        QObject(parent),
        shapeRecognizer(0)
    {}

    virtual void run() = 0;

    LTKShapeRecognizer *shapeRecognizer;
};

class LipiLoadModelDataTask : public LipiTask
{
    Q_OBJECT
public:
    void run();
};

class LipiRecognitionTask : public LipiTask
{
    Q_OBJECT
public:
    explicit LipiRecognitionTask(const LTKCaptureDevice& deviceInfo,
                                 const LTKScreenContext& screenContext,
                                 const vector<int>& inSubsetOfClasses,
                                 float confThreshold,
                                 int numChoices,
                                 int resultId);

    void run();
    bool cancelRecognition();
    int resultId() const;

    LTKTraceGroup traceGroup;

private:
    friend class LipiSharedRecognizer;
    const QMap<int, QChar> unicodeMap;
    const LTKCaptureDevice deviceInfo;
    const LTKScreenContext screenContext;
    const vector<int> inSubsetOfClasses;
    const float confThreshold;
    const int numChoices;
    QSharedPointer<vector<LTKShapeRecoResult> > resultVector;
    const int _resultId;
    QMutex stateLock;
    bool stateRunning;
    bool stateCancelled;
};

class LipiRecognitionResultsTask : public LipiTask
{
    Q_OBJECT
public:
    explicit LipiRecognitionResultsTask(QSharedPointer<vector<LTKShapeRecoResult> > resultVector,
                                        const QMap<int, QChar> &unicodeMap,
                                        int resultId);

    void run();

signals:
    void resultsAvailable(const QVariantList &resultList);

private:
    QSharedPointer<vector<LTKShapeRecoResult> > resultVector;
    const QMap<int, QChar> &unicodeMap;
    const int _resultId;
};

class LipiWorker : public QThread
{
    Q_OBJECT
public:
    explicit LipiWorker(LTKShapeRecognizer *shapeRecognizer, QObject *parent = 0);
    ~LipiWorker();

    void addTask(QSharedPointer<LipiTask> task);
    int removeTask(QSharedPointer<LipiTask> task);
    int removeAllTasks();

protected:
    void run();

private:
    QList<QSharedPointer<LipiTask> > taskList;
    QSemaphore taskSema;
    QMutex taskLock;
    LTKShapeRecognizer *shapeRecognizer;
    bool abort;
};

#endif // LIPIWORKER_H
