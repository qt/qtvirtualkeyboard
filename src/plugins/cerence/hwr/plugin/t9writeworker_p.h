// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef T9WRITEWORKER_H
#define T9WRITEWORKER_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtVirtualKeyboard/qvirtualkeyboardtrace.h>

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QStringList>
#include <QSharedPointer>
#include <QPointer>
#include <QMap>
#include <QList>
#include <QElapsedTimer>

#include "cerence_hwr_p.h"
#include "t9writedictionary_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class T9WriteTask : public QObject
{
    Q_OBJECT
public:
    explicit T9WriteTask(QObject *parent = nullptr);

    virtual void run() = 0;

    void wait();

    friend class T9WriteWorker;

protected:
    DECUMA_SESSION *decumaSession;
    bool cjk;

private:
    QSemaphore runSema;
};

class T9WriteDictionaryTask : public T9WriteTask
{
    Q_OBJECT
public:
    explicit T9WriteDictionaryTask(QSharedPointer<T9WriteAbstractDictionary> dictionary,
                                   bool convertDictionary);

    void run();

    QSharedPointer<T9WriteAbstractDictionary> dictionary;
    QSharedPointer<T9WriteAbstractSource> source;
    const QString dictionaryFileName;
    bool convertDictionary;

signals:
    void completed(QSharedPointer<T9WriteAbstractDictionary> dictionary);
};

class T9WriteAddArcTask : public T9WriteTask
{
    Q_OBJECT
public:
    explicit T9WriteAddArcTask(QVirtualKeyboardTrace *trace);

    void run();

private:
    QVirtualKeyboardTrace *trace;
};

class T9WriteRecognitionResult
{
    Q_DISABLE_COPY(T9WriteRecognitionResult)

public:
    explicit T9WriteRecognitionResult(int id, int maxResults, int maxCharsPerWord);

    DECUMA_STATUS status;
    QList<DECUMA_HWR_RESULT> results;
    DECUMA_UINT16 numResults;
    int instantGesture;
    const int id;
    const int maxResults;
    const int maxCharsPerWord;

private:
    QList<DECUMA_UNICODE> _chars;
    QList<DECUMA_INT16> _symbolChars;
    QList<DECUMA_INT16> _symbolStrokes;
};

class T9WriteRecognitionTask : public T9WriteTask
{
    Q_OBJECT
public:
    explicit T9WriteRecognitionTask(QSharedPointer<T9WriteRecognitionResult> result);

    void run();
    bool cancelRecognition();
    bool checkCancelled();
    int resultId() const;

private:
    void waitForBackgroundRecognition();

private:
    QSharedPointer<T9WriteRecognitionResult> result;
    QMutex stateLock;
    bool stateCancelled;
    QElapsedTimer perf;
};

class T9WriteRecognitionResultsTask : public T9WriteTask
{
    Q_OBJECT
public:
    explicit T9WriteRecognitionResultsTask(QSharedPointer<T9WriteRecognitionResult> result);

    void run();

signals:
    void resultsAvailable(const QVariantList &resultList);
    void recognitionError(int status);

private:
    QSharedPointer<T9WriteRecognitionResult> result;
};

class T9WriteDlmWordTask : public T9WriteTask
{
    Q_OBJECT
public:
    explicit T9WriteDlmWordTask(QSharedPointer<T9WriteAbstractDictionary> dlmDictionary, const QString &word, const QString &stringStart);

    void run();

protected:
    void persist();

protected:
    QSharedPointer<T9WriteAbstractDictionary> dlmDictionary;
    const QString word;
    const QString stringStart;
};

class T9WriteDlmRemoveWordTask : public T9WriteDlmWordTask
{
    Q_OBJECT
public:
    explicit T9WriteDlmRemoveWordTask(QSharedPointer<T9WriteAbstractDictionary> dlmDictionary, const QString &word);

    void run();
};

class T9WriteWorker : public QThread
{
    Q_OBJECT
public:
    explicit T9WriteWorker(DECUMA_SESSION *decumaSession, const bool cjk, QObject *parent = nullptr);
    ~T9WriteWorker();

    void addTask(QSharedPointer<T9WriteTask> task);
    int removeTask(QSharedPointer<T9WriteTask> task);
    int removeAllTasks();
    void waitForAllTasks();
    int numberOfPendingTasks();

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

    template <class X>
    void waitForAllTasksOfType() {
        QSharedPointer<X> task;
        {
            QMutexLocker guard(&taskLock);
            for (int i = taskList.size() - 1; i >= 0; --i) {
                task = taskList[i].objectCast<X>();
                if (task)
                    break;
            }
        }
        if (task)
            task->wait();
    }

protected:
    void run();

private:
    QList<QSharedPointer<T9WriteTask> > taskList;
    QSemaphore idleSema;
    QSemaphore taskSema;
    QMutex taskLock;
    DECUMA_SESSION *decumaSession;
    QBasicAtomicInt abort;
    const bool cjk;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // T9WRITEWORKER_H
