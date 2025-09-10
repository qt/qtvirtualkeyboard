// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef T9WRITEWORDCANDIDATE_H
#define T9WRITEWORDCANDIDATE_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QString>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class T9WriteWordCandidate
{
public:
    enum class Origin {
        None,
        T9Write,
        XT9
    };

    T9WriteWordCandidate(QString symbs, int resultIndex = -1, Origin origin = Origin::None);

public:
    QString symbs;
    int resultIndex;
    Origin origin;
};

bool operator==(const T9WriteWordCandidate &a, const T9WriteWordCandidate &b);

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // T9WRITEWORDCANDIDATE_H
