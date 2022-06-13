// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9CPALLBACKS_H
#define XT9CPALLBACKS_H

#include <et9api.h>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9RequestCallback {
public:
    virtual ET9STATUS request(ET9_Request *const pRequest) = 0;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9CPALLBACKS_H
