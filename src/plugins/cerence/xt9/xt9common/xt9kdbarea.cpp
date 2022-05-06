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

#include "xt9kdbarea.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

void Xt9KdbArea::serialize(QXmlStreamWriter &writer) const
{
    writer.writeStartElement(QStringLiteral("area"));
    if (!conditionValue.isEmpty())
        writer.writeAttribute(QStringLiteral("conditionValue"), conditionValue);
    for (const Xt9KdbKey &key : keys) {
        key.serialize(writer);
    }
    writer.writeEndElement();
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
