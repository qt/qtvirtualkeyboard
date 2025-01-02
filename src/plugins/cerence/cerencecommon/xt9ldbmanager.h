// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9LDBMANAGER_H
#define XT9LDBMANAGER_H

#include <QLocale>
#include <QSharedPointer>
#include <QRegularExpression>
#include <QSet>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9DbFile;

class Xt9LdbManager
{
public:
    Xt9LdbManager();

    void addSearchPath(const QString &ldbDirectory);
    void setPhdEnabled(bool enabled);
    bool phdEnabled() const;

    bool loadDictionary(const QLocale &locale, const void *&data, qint64 &size);
    void closeAll();

    QString findDictionary(const QLocale &locale) const;

private:
    QStringList searchPaths;
    QMap<QString, QSharedPointer<Xt9DbFile>> ldbMap;
    bool _phdEnabled;
    static const QRegularExpression ldbRegex;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9LDBMANAGER_H
