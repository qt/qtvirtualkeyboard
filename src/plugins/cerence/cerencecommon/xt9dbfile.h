// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9DBFILE_H
#define XT9DBFILE_H

#include <QFile>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9DbFile
{
public:
    Xt9DbFile(const QString &fileName);

    QString fileName() const;
    const void *roData();
    void *rwData(qint64 size);
    qint64 size() const;

private:
    QFile file;
    void *_data;
    qint64 _size;
    bool _rw;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9DBFILE_H
