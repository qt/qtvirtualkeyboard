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

#include "lipisharedrecognizer.h"
#include "virtualkeyboarddebug.h"
#include "lipiworker.h"

#include "LTKMacros.h"
#include "LTKInc.h"
#include "LTKTypes.h"
#include "LTKOSUtil.h"
#include "LTKOSUtilFactory.h"
#include "LTKErrorsList.h"
#include "LTKErrors.h"
#include "LTKLogger.h"
#include "LTKConfigFileReader.h"
#include "LTKException.h"
#include "LTKLipiEngineInterface.h"

#include <QDir>
#include <QtCore/QLibraryInfo>

int LipiSharedRecognizer::s_lipiEngineRefCount = 0;
const QString LipiSharedRecognizer::s_lipiRoot = QDir(QLibraryInfo::location(QLibraryInfo::DataPath) + "/qtvirtualkeyboard/lipi_toolkit").absolutePath();
void *LipiSharedRecognizer::s_lipiEngineHandle = 0;
LipiSharedRecognizer::FN_PTR_CREATELTKLIPIENGINE LipiSharedRecognizer::s_createLTKLipiEngine = 0;
LipiSharedRecognizer::FN_PTR_DELETELTKLIPIENGINE LipiSharedRecognizer::s_deleteLTKLipiEngine = 0;
LTKLipiEngineInterface *LipiSharedRecognizer::s_lipiEngine = 0;
LTKShapeRecognizer *LipiSharedRecognizer::s_shapeRecognizer = 0;
LipiWorker *LipiSharedRecognizer::s_lipiWorker = 0;
QMap<int, QChar> LipiSharedRecognizer::s_unicodeMap;
QString LipiSharedRecognizer::s_activeModel;
stringStringMap LipiSharedRecognizer::s_lipiEngineConfigEntries;

LipiSharedRecognizer::LipiSharedRecognizer()
{
    loadLipiInterface();
}

LipiSharedRecognizer::~LipiSharedRecognizer()
{
    unloadLipiInterface();
}

QString LipiSharedRecognizer::model() const
{
    return s_activeModel;
}

bool LipiSharedRecognizer::setModel(const QString &modelName)
{
    VIRTUALKEYBOARD_DEBUG() << "LipiSharedRecognizer::setModel():" << modelName;

    if (!s_lipiEngine) {
        qWarning() << "Engine not initialized";
        return false;
    }

    if (modelName.isEmpty())
        return false;

    if (modelName == s_activeModel)
        return true;

    unloadModelData();

    return loadModelData(modelName) == SUCCESS;
}

void LipiSharedRecognizer::subsetOfClasses(const QString &charset, vector<int> &outSubsetOfClasses) const
{
    outSubsetOfClasses.clear();
    outSubsetOfClasses.reserve(charset.length());
#ifdef QT_VIRTUALKEYBOARD_DEBUG
    QString notFound;
#endif
    for (int i = 0; i < charset.length(); i++) {
        int classId = s_unicodeMap.key(charset.at(i), -1);
        if (classId != -1)
            outSubsetOfClasses.push_back(classId);
#ifdef QT_VIRTUALKEYBOARD_DEBUG
        else
            notFound.append(charset.at(i));
#endif
    }
#ifdef QT_VIRTUALKEYBOARD_DEBUG
    if (!notFound.isEmpty())
        VIRTUALKEYBOARD_DEBUG() << "LipiSharedRecognizer::subsetOfClasses(): unrecognized characters" << notFound;
#endif
}

QSharedPointer<LipiRecognitionTask> LipiSharedRecognizer::newRecognition(const LTKCaptureDevice& deviceInfo,
                                                                         const LTKScreenContext& screenContext,
                                                                         const vector<int>& inSubsetOfClasses,
                                                                         float confThreshold,
                                                                         int numChoices)
{
    if (!s_lipiEngine || !s_shapeRecognizer || !s_lipiWorker)
        return QSharedPointer<LipiRecognitionTask>();

    QSharedPointer<LipiRecognitionTask> task(new LipiRecognitionTask(deviceInfo,
                                                                     screenContext,
                                                                     inSubsetOfClasses,
                                                                     confThreshold,
                                                                     numChoices));

    return task;
}

QSharedPointer<LipiRecognitionResultsTask> LipiSharedRecognizer::startRecognition(QSharedPointer<LipiRecognitionTask> &recognitionTask)
{
    if (!s_lipiEngine || !s_shapeRecognizer || !s_lipiWorker)
        return QSharedPointer<LipiRecognitionResultsTask>();

    QSharedPointer<LipiRecognitionResultsTask> resultsTask(new LipiRecognitionResultsTask(recognitionTask->resultVector,
                                                                                          s_unicodeMap));

    s_lipiWorker->addTask(recognitionTask);
    s_lipiWorker->addTask(resultsTask);

    return resultsTask;
}

bool LipiSharedRecognizer::cancelRecognition()
{
    if (!s_lipiEngine || !s_shapeRecognizer || !s_lipiWorker)
        return false;

    return s_lipiWorker->removeAllTasks() > 0;
}

int LipiSharedRecognizer::loadLipiInterface()
{
    VIRTUALKEYBOARD_DEBUG() << "LipiSharedRecognizer::loadLipiInterface():" << s_lipiEngineRefCount;

    if (++s_lipiEngineRefCount == 1) {
        qputenv("LIPI_ROOT", s_lipiRoot.toLatin1());

        QScopedPointer<LTKOSUtil> osUtil(LTKOSUtilFactory::getInstance());
        const string lipiRootPath(QDir::toNativeSeparators(s_lipiRoot).toStdString());

        int result = osUtil->loadSharedLib(lipiRootPath, LIPIENGINE_MODULE_STR, &s_lipiEngineHandle);
        if (result != SUCCESS) {
            qWarning() << QString("Error %1: %2").arg(result).arg(getErrorMessage(result).c_str());
            return result;
        }

        result = loadLipiEngineConfig();
        if (result != SUCCESS)
            return result;

        result = osUtil->getFunctionAddress(s_lipiEngineHandle, "createLTKLipiEngine", (void **)&s_createLTKLipiEngine);
        if (result != SUCCESS) {
            qWarning() << QString("Error %1: %2").arg(result).arg(getErrorMessage(result).c_str());
            return result;
        }

        result = osUtil->getFunctionAddress(s_lipiEngineHandle, "deleteLTKLipiEngine", (void **)&s_deleteLTKLipiEngine);
        if (result != SUCCESS) {
            qWarning() << QString("Error %1: %2").arg(result).arg(getErrorMessage(result).c_str());
            return result;
        }

        s_lipiEngine = s_createLTKLipiEngine();
        s_lipiEngine->setLipiRootPath(lipiRootPath);
#if 0
        s_lipiEngine->setLipiLogFileName(QDir::toNativeSeparators(QString("%1/lipi.log").arg(s_lipiRoot)).toStdString());
        s_lipiEngine->setLipiLogLevel("DEBUG");
#endif

        result = s_lipiEngine->initializeLipiEngine();
        if (result != SUCCESS) {
            qWarning() << QString("Error %1: %2").arg(result).arg(getErrorMessage(result).c_str());
            return result;
        }
    }

    return SUCCESS;
}

void LipiSharedRecognizer::unloadLipiInterface()
{
    VIRTUALKEYBOARD_DEBUG() << "LipiSharedRecognizer::unloadLipiInterface():" << s_lipiEngineRefCount;

    Q_ASSERT(s_lipiEngineRefCount > 0);
    if (--s_lipiEngineRefCount == 0) {
        unloadModelData();
        if (s_lipiEngine) {
            s_deleteLTKLipiEngine();
            s_lipiEngine = 0;
        }
        s_createLTKLipiEngine = 0;
        s_deleteLTKLipiEngine = 0;
        QScopedPointer<LTKOSUtil> osUtil(LTKOSUtilFactory::getInstance());
        osUtil->unloadSharedLib(s_lipiEngineHandle);
        s_lipiEngineHandle = 0;
    }
}

int LipiSharedRecognizer::loadLipiEngineConfig()
{
    s_lipiEngineConfigEntries.clear();

    const QString &lipiEngineConfigFile(QDir::toNativeSeparators(QString("%1/projects/lipiengine.cfg").arg(s_lipiRoot)));
    if (!QFileInfo(lipiEngineConfigFile).exists()) {
        qWarning() << "File not found" << lipiEngineConfigFile;
        return FAILURE;
    }

    try {
        LTKConfigFileReader configReader(lipiEngineConfigFile.toStdString());
        s_lipiEngineConfigEntries = configReader.getCfgFileMap();
    } catch (LTKException e) {
        return e.getErrorCode();
    }

    return SUCCESS;
}

int LipiSharedRecognizer::resolveLogicalNameToProjectProfile(const QString &logicalName, QString &outProjectName, QString &outProfileName)
{
    outProjectName.clear();
    outProfileName.clear();

    stringStringMap::const_iterator configEntry = s_lipiEngineConfigEntries.find(logicalName.toStdString());
    if (configEntry == s_lipiEngineConfigEntries.end())
        return FAILURE;

    QStringList parts = QString(configEntry->second.c_str()).split('(', QString::SkipEmptyParts);
    if (parts.length() != 2)
        return FAILURE;

    parts[1].replace(')', "");

    outProjectName = parts[0].trimmed();
    outProfileName = parts[1].trimmed();

    return SUCCESS;
}

int LipiSharedRecognizer::loadModelData(const QString &logicalName)
{
    VIRTUALKEYBOARD_DEBUG() << "LipiSharedRecognizer::loadModelData():" << logicalName;

    Q_ASSERT(s_shapeRecognizer == 0);
    Q_ASSERT(s_lipiWorker == 0);

#ifdef QT_VIRTUALKEYBOARD_DEBUG
    QTime perf;
    perf.start();
#endif

    s_activeModel = logicalName;

    QString project;
    QString profile;
    int result = resolveLogicalNameToProjectProfile(logicalName, project, profile);
    if (result == SUCCESS) {
        string strProject = project.toStdString();
        string strProfile = profile.toStdString();
        int result = s_lipiEngine->createShapeRecognizer(strProject, strProfile, &s_shapeRecognizer);
        if (result == SUCCESS) {
            result = loadMapping(QDir::toNativeSeparators(QString("%1/projects/%2/config/unicodeMapfile_%2.ini").arg(s_lipiRoot).arg(project)));
            if (result == SUCCESS) {
                s_lipiWorker = new LipiWorker(s_shapeRecognizer);
                QSharedPointer<LipiLoadModelDataTask> loadModelDataTask(new LipiLoadModelDataTask());
                s_lipiWorker->addTask(loadModelDataTask);
                s_lipiWorker->start();
            }
        }
    }

#ifdef QT_VIRTUALKEYBOARD_DEBUG
    if (result == SUCCESS)
        VIRTUALKEYBOARD_DEBUG() << "LipiSharedRecognizer::loadModelData(): time:" << perf.elapsed() << "ms";
#endif

    if (result != SUCCESS) {
        qWarning() << QString("Error %1: %2").arg(result).arg(getErrorMessage(result).c_str());
        unloadModelData();
    }

    return result;
}

void LipiSharedRecognizer::unloadModelData()
{
    if (!s_shapeRecognizer)
        return;

    VIRTUALKEYBOARD_DEBUG() << "LipiSharedRecognizer::unloadModelData():" << s_activeModel;

#ifdef QT_VIRTUALKEYBOARD_DEBUG
    QTime perf;
    perf.start();
#endif

    if (s_lipiWorker) {
        delete s_lipiWorker;
        s_lipiWorker = 0;
    }

    s_lipiEngine->deleteShapeRecognizer(s_shapeRecognizer);
    s_shapeRecognizer = 0;
    s_unicodeMap.clear();
    s_activeModel.clear();

#ifdef QT_VIRTUALKEYBOARD_DEBUG
    VIRTUALKEYBOARD_DEBUG() << "LipiSharedRecognizer::unloadModelData(): time:" << perf.elapsed() << "ms";
#endif
}

int LipiSharedRecognizer::loadMapping(const QString &mapFile)
{
    if (!QFileInfo(mapFile).exists()) {
        qWarning() << "File not found" << mapFile;
        return FAILURE;
    }

    try {
        LTKConfigFileReader configfilereader(mapFile.toStdString());
        const stringStringMap &cfgFileMap = configfilereader.getCfgFileMap();

        for (stringStringMap::const_iterator i = cfgFileMap.begin(); i != cfgFileMap.end(); i++) {
            if (i->first.empty())
                continue;
            if (!QChar(i->first.at(0)).isDigit())
                continue;

            bool ok;
            int id = QString(i->first.c_str()).toInt(&ok, 10);
            if (!ok)
                continue;

            QChar ch = QChar(QString(i->second.c_str()).toInt(&ok, 16));
            if (!ok)
                continue;

            s_unicodeMap[id] = ch;
        }
    } catch (LTKException) {
        return FAILURE;
    }

    VIRTUALKEYBOARD_DEBUG() << s_unicodeMap;

    return SUCCESS;
}
