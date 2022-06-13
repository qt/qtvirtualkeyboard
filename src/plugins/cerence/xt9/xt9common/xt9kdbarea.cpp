// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
