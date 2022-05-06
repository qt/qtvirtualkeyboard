/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

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
