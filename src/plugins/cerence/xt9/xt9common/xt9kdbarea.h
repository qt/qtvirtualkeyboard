// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9KDBAREA_H
#define XT9KDBAREA_H

#include "xt9kdbelement.h"
#include "xt9kdbkey.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9KdbArea : public Xt9KdbElement
{
public:
    void serialize(QXmlStreamWriter &writer) const;

    QString conditionValue;
    QList<Xt9KdbKey> keys;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9KDBAREA_H
