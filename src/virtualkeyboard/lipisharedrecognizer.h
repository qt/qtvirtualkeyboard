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

#ifndef LIPISHAREDRECOGNIZER_H
#define LIPISHAREDRECOGNIZER_H

#include <QString>
#include <QMap>

#include "lipiworker.h"

class LTKLipiEngineInterface;

class LipiSharedRecognizer
{
    Q_DISABLE_COPY(LipiSharedRecognizer)
public:
    LipiSharedRecognizer();
    ~LipiSharedRecognizer();

    QString model() const;
    bool setModel(const QString &modelName);

    void subsetOfClasses(const QString &charset, vector<int> &outSubsetOfClasses) const;

    QSharedPointer<LipiRecognitionTask> newRecognition(const LTKCaptureDevice& deviceInfo,
                                                       const LTKScreenContext& screenContext,
                                                       const vector<int>& inSubsetOfClasses,
                                                       float confThreshold,
                                                       int numChoices);
    QSharedPointer<LipiRecognitionResultsTask> startRecognition(QSharedPointer<LipiRecognitionTask> &recognitionTask);
    bool cancelRecognition();

private:
    static int loadLipiInterface();
    static void unloadLipiInterface();
    static int loadLipiEngineConfig();
    static int resolveLogicalNameToProjectProfile(const QString &logicalName, QString &outProjectName, QString &outProfileName);
    static int loadModelData(const QString &logicalName);
    static void unloadModelData();
    static int loadMapping(const QString &mapFile);

    typedef LTKLipiEngineInterface* (*FN_PTR_CREATELTKLIPIENGINE)(void);
    typedef void (*FN_PTR_DELETELTKLIPIENGINE)(void);

    static int s_lipiEngineRefCount;
    const static QString s_lipiRoot;
    static void *s_lipiEngineHandle;
    static FN_PTR_CREATELTKLIPIENGINE s_createLTKLipiEngine;
    static FN_PTR_DELETELTKLIPIENGINE s_deleteLTKLipiEngine;
    static LTKLipiEngineInterface *s_lipiEngine;
    static LTKShapeRecognizer *s_shapeRecognizer;
    static LipiWorker *s_lipiWorker;
    static QMap<int, QChar> s_unicodeMap;
    static QString s_activeModel;
    static stringStringMap s_lipiEngineConfigEntries;
};

#endif // LIPISHAREDRECOGNIZER_H
