// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
