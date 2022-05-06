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
