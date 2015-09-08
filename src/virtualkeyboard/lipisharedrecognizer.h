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
    bool cancelRecognitionTask(QSharedPointer<LipiRecognitionTask> &recognitionTask);

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
    static QString s_lipiRoot;
    static void *s_lipiEngineHandle;
    static FN_PTR_CREATELTKLIPIENGINE s_createLTKLipiEngine;
    static FN_PTR_DELETELTKLIPIENGINE s_deleteLTKLipiEngine;
    static LTKLipiEngineInterface *s_lipiEngine;
    static LTKShapeRecognizer *s_shapeRecognizer;
    static LipiWorker *s_lipiWorker;
    static QMap<int, QChar> s_unicodeMap;
    static QString s_activeModel;
    static stringStringMap s_lipiEngineConfigEntries;
    static int s_recognitionCount;
};

#endif // LIPISHAREDRECOGNIZER_H
