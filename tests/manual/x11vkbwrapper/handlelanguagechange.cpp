/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

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
