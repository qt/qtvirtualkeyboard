// Copyright (C) MyScript. Contact: https://www.myscript.com/about/contact-us/sales-inquiry/
// Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB). Contact: https://www.qt.io/licensing/
// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MYSCRIPTINPUTMETHOD_P_P_H
#define MYSCRIPTINPUTMETHOD_P_P_H

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

#include <QObject>
#include <QString>
#include <QThread>

typedef struct VOIM_ENGINE voimEngine;
typedef struct VOIM_RECOGNIZER voimRecognizer;
typedef struct CANDIDATE_ITEM CandidateItem;

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class MyScriptRecognizeWorker : public QObject
{
    Q_OBJECT

public:
    MyScriptRecognizeWorker(voimEngine* engine, voimRecognizer* recognizer);

public slots:
    void manageRecognitionEnded();
    void manageRecognitionCommitted();

signals:
    void recognitionEnded();
    void recognitionCommitted();
    void gestureDetected(const int gestureType, const int gestureCount);
    void preeditChanged(const QString &preedit, const bool isCommitted);
    void clearItem();
    void newItem(const int itemIndex, const int candidateIndex, const QStringList &candidates);
    void newCandidates(const QStringList &candidates, const QString &word, int wordIndex);
    void clearTraces();

private:
    void manageRecognitionResult(voimEngine *engine, voimRecognizer *recognizer, const bool isCommitted);
    int isGesture(const QString label);

    voimEngine* m_engine;
    voimRecognizer* m_recognizer;
    QString m_resultLabel;
};

class MyScriptInputMethodPrivate;

class MyScriptRecognizeController : public QObject
{
    Q_OBJECT
public:
    MyScriptRecognizeController(MyScriptInputMethodPrivate *d, voimEngine *engine, voimRecognizer *recognizer);
    ~MyScriptRecognizeController();

    void emitRecognitionEnded();
    void emitRecognitionCommitted();

public slots:
    void handleRecognitionEnded();
    void handleRecognitionCommitted();
    void handelGestureDetected(const int gestureType, const int gestureCount);
    void handlePreeditChanged(const QString &preedit, const bool isCommitted);
    void handleClearItem();
    void handleNewItem(const int itemIndex, const int candidateIndex, const QStringList &candidates);
    void handleNewCandidates(const QStringList &candidates, const QString &word, int wordIndex);
    void handleClearTraces();

signals:
    void recognitionEnded();
    void recognitionCommitted();

private:
    QThread workerThread;
    MyScriptInputMethodPrivate *d;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // MYSCRIPTINPUTMETHOD_P_P_H
