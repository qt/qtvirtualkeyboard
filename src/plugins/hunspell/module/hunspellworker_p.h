// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef HUNSPELLWORKER_P_H
#define HUNSPELLWORKER_P_H

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

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QStringList>
#include <QSharedPointer>
#include <QList>
#include <QLoggingCategory>
#include <QStringDecoder>
#include <QStringEncoder>
#include <hunspell/hunspell.h>
#include "hunspellwordlist_p.h"

QT_BEGIN_NAMESPACE

namespace QtVirtualKeyboard {

Q_DECLARE_LOGGING_CATEGORY(lcHunspell)

class HunspellTask : public QObject
{
    Q_OBJECT
public:
    explicit HunspellTask(QObject *parent = nullptr) :
        QObject(parent),
        hunspell(nullptr)
    {}

    virtual void run() = 0;

    Hunhandle *hunspell;
};

class HunspellLoadDictionaryTask : public HunspellTask
{
    Q_OBJECT
public:
    explicit HunspellLoadDictionaryTask(const QString &locale, const QStringList &searchPaths);

    void run() override;

signals:
    void completed(bool success);

public:
    Hunhandle **hunspellPtr;
    const QString locale;
    const QStringList searchPaths;
};

class HunspellBuildSuggestionsTask : public HunspellTask
{
    Q_OBJECT
public:
    QSharedPointer<HunspellWordList> wordList;
    bool autoCorrect;

    void run() override;
    bool spellCheck(const QString &word);
    int levenshteinDistance(const QString &s, const QString &t);
    QString removeAccentsAndDiacritics(const QString& s);

private:
    QStringDecoder textDecoder;
    QStringEncoder textEncoder;
};

class HunspellUpdateSuggestionsTask : public HunspellTask
{
    Q_OBJECT
public:
    QSharedPointer<HunspellWordList> wordList;

    void run() override;

signals:
    void updateSuggestions(const QSharedPointer<HunspellWordList> &wordList, int tag);

public:
    int tag;
};

class HunspellAddWordTask : public HunspellTask
{
    Q_OBJECT
public:
    QSharedPointer<HunspellWordList> wordList;

    void run() override;

    static bool alternativeForm(const QString &word, QString &alternativeForm);
};

class HunspellRemoveWordTask : public HunspellTask
{
    Q_OBJECT
public:
    QSharedPointer<HunspellWordList> wordList;

    void run() override;
};

class HunspellLoadWordListTask : public HunspellTask
{
    Q_OBJECT
public:
    QSharedPointer<HunspellWordList> wordList;
    QString filePath;

    void run() override;
};

class HunspellSaveWordListTask : public HunspellTask
{
    Q_OBJECT
public:
    QSharedPointer<HunspellWordList> wordList;
    QString filePath;

    void run() override;
};

class HunspellFilterWordTask : public HunspellTask
{
    Q_OBJECT
public:
    HunspellFilterWordTask() :
        HunspellTask(),
        startIndex(1)
    {}

    QSharedPointer<HunspellWordList> wordList;
    QSharedPointer<HunspellWordList> filterList;
    int startIndex;

    void run() override;
};

class HunspellBoostWordTask : public HunspellTask
{
    Q_OBJECT
public:
    HunspellBoostWordTask() :
        HunspellTask()
    {}

    QSharedPointer<HunspellWordList> wordList;
    QSharedPointer<HunspellWordList> boostList;

    void run() override;
};

class HunspellWorker : public QThread
{
    Q_OBJECT
public:
    explicit HunspellWorker(QObject *parent = nullptr);
    ~HunspellWorker();

    void addTask(QSharedPointer<HunspellTask> task);
    void removeAllTasks();
    void waitForAllTasks();

    template <class X>
    void removeAllTasksOfType() {
        QMutexLocker guard(&taskLock);
        for (int i = 0; i < taskList.size();) {
            QSharedPointer<X> task(taskList[i].objectCast<X>());
            if (task) {
                qCDebug(lcHunspell) << "Remove task" << QLatin1String(task->metaObject()->className());
                taskList.removeAt(i);
            } else {
                i++;
            }
        }
    }

protected:
    void run() override;

private:
    void createHunspell();

private:
    friend class HunspellLoadDictionaryTask;
    QList<QSharedPointer<HunspellTask> > taskList;
    QSemaphore idleSema;
    QSemaphore taskSema;
    QMutex taskLock;
    Hunhandle *hunspell;
    QBasicAtomicInt abort;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // HUNSPELLWORKER_P_H
