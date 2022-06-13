// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QLoggingCategory>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>

#include "handlelanguagechange.h"

namespace {
const QString KFilePath = "/x11vkbwrapper_language/";
const QString KFilePathName = KFilePath + "currentLang.json";
}

Q_LOGGING_CATEGORY(lcHandleLanguageChange, "qt.virtualkeyboard.tests.manual.x11vkbwrapper.handlelanguagechange")

/**
 * @brief HandleJson::HandleJson
 *  Class is only for testing purpose
 * @param parent
 */
HandleLanguageChange::HandleLanguageChange(QObject *parent) : QObject(parent)
{

}

/**
 * @brief HandleLanguageChange::languageChanged
 *  Signal emitted on QML when a language is changed
 * @param language
 */
void HandleLanguageChange::languageChanged(const QString &language) const
{
    qCDebug(lcHandleLanguageChange) << Q_FUNC_INFO << QDir::homePath();
    QJsonDocument langDoc;
    QJsonObject langObj;
    langObj["language"] = language;
    langDoc.setObject(langObj);

    if (!QDir(QDir::homePath() + KFilePath).exists()) {
        QDir dir;
        dir.mkdir(QDir::homePath() + KFilePath);
    }

    QFile jsonFile(QDir::homePath() + KFilePathName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(langDoc.toJson());
    jsonFile.flush();
    jsonFile.close();
}
