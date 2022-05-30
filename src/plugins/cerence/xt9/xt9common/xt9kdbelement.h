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
