// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9KDBELEMENT_H
#define XT9KDBELEMENT_H

#include <QXmlStreamWriter>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9KdbElement
{
public:
    virtual ~Xt9KdbElement();

    virtual void serialize(QXmlStreamWriter &writer) const = 0;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9KDBELEMENT_H
