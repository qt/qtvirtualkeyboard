/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#ifndef HUNSPELLWORKER_H
#define HUNSPELLWORKER_H

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QStringList>
#include <QSharedPointer>
#include <hunspell/hunspell.h>

class HunspellTask : public QObject
{
    Q_OBJECT
public:
    explicit HunspellTask(QObject *parent = 0) :
        QObject(parent),
        hunspell(0)
    {}

    virtual void run() = 0;

    Hunhandle *hunspell;
};

class HunspellWordList
{
public:
    HunspellWordList() :
        list(),
        index(-1)
    {}

    QStringList list;
    int index;
};

class QTextCodec;

class HunspellBuildSuggestionsTask : public HunspellTask
{
    Q_OBJECT
    const QTextCodec *textCodec;
public:
    QString word;
    QSharedPointer<HunspellWordList> wordList;

    void run();
    bool spellCheck(const QString &word);
    int levenshteinDistance(const QString &s, const QString &t);
    QString removeAccentsAndDiacritics(const QString& s);
};

class HunspellUpdateSuggestionsTask : public HunspellTask
{
    Q_OBJECT
public:
    QSharedPointer<HunspellWordList> wordList;

    void run();

signals:
    void updateSuggestions(const QStringList &wordList, int activeWordIndex);
};

class HunspellWorker : public QThread
{
    Q_OBJECT
public:
    explicit HunspellWorker(Hunhandle *hunspell, QObject *parent = 0);
    ~HunspellWorker();

    void addTask(QSharedPointer<HunspellTask> task);
    void removeAllTasks();

protected:
    void run();

private:
    QList<QSharedPointer<HunspellTask> > taskList;
    QSemaphore taskSema;
    QMutex taskLock;
    Hunhandle *hunspell;
    bool abort;
};

#endif // HUNSPELLWORKER_H
