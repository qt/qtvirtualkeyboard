// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9dbfile.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Xt9DbFile::Xt9DbFile(const QString &fileName) :
    file(fileName),
    _data(nullptr),
    _size(0),
    _rw(false)
{

}

QString Xt9DbFile::fileName() const
{
    return file.fileName();
}

const void *Xt9DbFile::roData()
{
    if (_data == nullptr) {
        if (file.open(QIODevice::ReadOnly)) {
            _rw = false;
            _size = file.size();
            _data = file.map(0, _size, QFile::NoOptions);
            if (!_data) {
                _size = 0;
            }
            file.close();
        }
    }

    return _data;
}

void *Xt9DbFile::rwData(qint64 size)
{
    if (_data == nullptr || !_rw) {
        if (!_rw) {
            file.unmap(static_cast<uchar *>(_data));
            _data = nullptr;
            _rw = false;
        }
        if (file.open(QIODevice::ReadWrite)) {
            _rw = true;
            _size = file.size();
            if (_size == 0) {
                _size = size;
                file.resize(_size);
            }
            _data = file.map(0, _size, QFile::NoOptions);
            if (!_data) {
                _size = 0;
            }
            file.close();
        }
    }

    return _data;
}

qint64 Xt9DbFile::size() const
{
    return _size;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
