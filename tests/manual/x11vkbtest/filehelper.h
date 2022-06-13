// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <map>

class QString;
class QVariant;

class FileHelper
{
public:
    static bool fileExists(const QString &fileName);
    static QString getFileContext(const QString &fileName);
    static bool getJsonFromFile(const QString &fileName, std::map<QString, QVariant> &jsonMap);
};

#endif // FILEHELPER_H
