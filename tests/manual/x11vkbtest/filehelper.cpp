/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QFile>
#include <QTextStream>
#include <QLoggingCategory>
#include <QJsonDocument>
#include <QJsonObject>
#include <fstream>

#include "filehelper.h"

Q_LOGGING_CATEGORY(lcFileHelper, "qt.virtualkeyboard.tests.manual.x11vkbtest.filehelper")

bool FileHelper::fileExists(const QString &fileName)
{
    std::ifstream stream(fileName.toLatin1());
    return stream.good();
}


QString FileHelper::getFileContext(const QString &fileName)
{
    QString result = "";
    QFile file(fileName);

    if (!(!file.open(QFile::ReadOnly | QFile::Text))) {
        QTextStream in(&file);
        result = in.readAll();
        file.close();
    }

    return result;
}

bool FileHelper::getJsonFromFile(const QString &fileName, std::map<QString, QVariant> &jsonMap)
{
    bool result = true;

    if (!fileExists(fileName)) {
        qCDebug(lcFileHelper) << "File:" << fileName << "doesn't exist";
        result = false;
    } else {
        QString jsonString = FileHelper::getFileContext(fileName);
        QByteArray jsonBytes = jsonString.toLocal8Bit();

        auto jsonDoc = QJsonDocument::fromJson(jsonBytes);

        if (jsonDoc.isNull()) {
            qCDebug(lcFileHelper) << "jsonDoc is Null";
            result = false;
        } else if (!jsonDoc.isObject()) {
            qCDebug(lcFileHelper) << "jsonDoc is NOT an object";
            result = false;
        } else {
            QJsonObject jsonObj = jsonDoc.object();

            if (jsonObj.isEmpty()) {
                qCDebug(lcFileHelper) << "jsonObj is Empty";
                result = false;
            } else {
                auto jsonIter = jsonObj.constBegin();
                jsonMap.insert({jsonIter.key(), jsonIter.value()});
            }
        }
    }
    return result;
}
