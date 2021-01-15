/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#ifndef COLORS_H
#define COLORS_H

namespace {
#define RST  "\x1B[0m"
#define KRed  "\x1B[31m"
#define KGreen  "\x1B[32m"

#define FRed(x) KRed x RST
#define FGreen(x) KGreen x RST
#define FBold(x) "\x1B[1m" x RST
};

#endif // COLORS_H
