// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "t9writewordcandidate_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

T9WriteWordCandidate::T9WriteWordCandidate(QString symbs, int resultIndex, T9WriteWordCandidate::Origin origin) :
    symbs(symbs),
    resultIndex(resultIndex),
    origin(origin)
{

}

bool operator==(const T9WriteWordCandidate &a, const T9WriteWordCandidate &b)
{
    return a.symbs == b.symbs;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
