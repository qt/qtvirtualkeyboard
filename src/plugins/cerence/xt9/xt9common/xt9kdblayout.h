// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9KDBLAYOUT_H
#define XT9KDBLAYOUT_H

#include "xt9kdbarea.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9KdbLayout : public Xt9KdbElement
{
public:
    Xt9KdbLayout();

    void serialize(QXmlStreamWriter &writer) const;

    int primaryId;
    int secondaryId;
    int defaultLayoutWidth;
    int defaultLayoutHeight;
    bool supportsExact;
    bool smartTouchActive;
    QList<Xt9KdbArea> areas;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9KDBLAYOUT_H
