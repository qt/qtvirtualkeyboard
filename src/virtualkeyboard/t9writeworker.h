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

#ifndef T9WRITEWORKER_H
#define T9WRITEWORKER_H

#include "declarativetrace.h"

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QStringList>
#include <QSharedPointer>
#include <QPointer>
#include <QMap>
#include <QVector>

#include "decuma_hwr.h"

class T9WriteTask : public QObject
{
    Q_OBJECT
public:
    explicit T9WriteTask(QObject *parent = 0);

    virtual void run() = 0;

    void wait();

    friend class T9WriteWorker;

protected:
    DECUMA_SESSION *decumaSession;

private:
    QSemaphore runSema;
};

class T9WriteDictionaryTask : public T9WriteTask
{
    Q_OBJECT
public:
    explicit T9WriteDictionaryTask(const QString &fileUri,
                                   const DECUMA_MEM_FUNCTIONS &memFuncs);

    void run();

    const QString fileUri;
    const DECUMA_MEM_FUNCTIONS &memFuncs;

signals:
    void completed(const QString &fileUri, void *dictionary);
};

class T9WriteRecognitionResult
{
    Q_DISABLE_COPY(T9WriteRecognitionResult)

public:
    explicit T9WriteRecognitionResult(int id, int maxResults, int maxCharsPerWord);

    QVector<DECUMA_HWR_RESULT> results;
    DECUMA_UINT16 numResults;
    int instantGesture;
    const int id;
    const int maxResults;
    const int maxCharsPerWord;
private:
    QVector<DECUMA_UNICODE> _chars;
    QVector<DECUMA_INT16> _symbolChars;
    QVector<DECUMA_INT16> _symbolStrokes;
};

class T9WriteRecognitionTask : public T9WriteTask
{
    Q_OBJECT
public:
    explicit T9WriteRecognitionTask(QSharedPointer<T9WriteRecognitionResult> result,
                                    const DECUMA_INSTANT_GESTURE_SETTINGS &instantGestureSettings,
                                    BOOST_LEVEL boostLevel,
                                    const QString &stringStart);

    void run();
    bool cancelRecognition();
    int resultId() const;

private:
    static int shouldAbortRecognize(void *pUserData);
    friend int shouldAbortRecognize(void *pUserData);

private:
    QSharedPointer<T9WriteRecognitionResult> result;
    DECUMA_INSTANT_GESTURE_SETTINGS instantGestureSettings;
    BOOST_LEVEL boostLevel;
    QString stringStart;
    QMutex stateLock;
    bool stateCancelled;
};

class T9WriteRecognitionResultsTask : public T9WriteTask
{
    Q_OBJECT
public:
    explicit T9WriteRecognitionResultsTask(QSharedPointer<T9WriteRecognitionResult> result);

    void run();

signals:
    void resultsAvailable(const QVariantList &resultList);

private:
    QSharedPointer<T9WriteRecognitionResult> result;
};

class T9WriteWorker : public QThread
{
    Q_OBJECT
public:
    explicit T9WriteWorker(DECUMA_SESSION *decumaSession, QObject *parent = 0);
    ~T9WriteWorker();

    void addTask(QSharedPointer<T9WriteTask> task);
    int removeTask(QSharedPointer<T9WriteTask> task);
    int removeAllTasks();

    template <class X>
    int removeAllTasks() {
        QMutexLocker guard(&taskLock);
        int count = 0;
        for (int i = 0; i < taskList.size();) {
            QSharedPointer<X> task(taskList[i].objectCast<X>());
            if (task) {
                taskList.removeAt(i);
                ++count;
            } else {
                ++i;
            }
        }
        return count;
    }

protected:
    void run();

private:
    QList<QSharedPointer<T9WriteTask> > taskList;
    QSemaphore taskSema;
    QMutex taskLock;
    DECUMA_SESSION *decumaSession;
    bool abort;
};

#endif // T9WRITEWORKER_H
