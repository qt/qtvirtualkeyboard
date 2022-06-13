// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9kdblayout.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Xt9KdbLayout::Xt9KdbLayout() :
    primaryId(0),
    secondaryId(0),
    defaultLayoutWidth(0),
    defaultLayoutHeight(0),
    supportsExact(false),
    smartTouchActive(false)
{

}

void Xt9KdbLayout::serialize(QXmlStreamWriter &writer) const
{
    writer.writeStartElement(QStringLiteral("keyboard"));
    writer.writeAttribute(QStringLiteral("primaryId"), QString::number(primaryId));
    writer.writeAttribute(QStringLiteral("secondaryId"), QString::number(secondaryId));
    if (defaultLayoutWidth > 0 && defaultLayoutHeight > 0) {
        writer.writeAttribute(QStringLiteral("defaultLayoutWidth"), QString::number(defaultLayoutWidth));
        writer.writeAttribute(QStringLiteral("defaultLayoutHeight"), QString::number(defaultLayoutHeight + 1));
    }
    if (supportsExact)
        writer.writeAttribute(QStringLiteral("supportsExact"), QString(QStringLiteral("%1")).arg(supportsExact));
    if (smartTouchActive)
        writer.writeAttribute(QStringLiteral("smartTouchActive"), QString(QStringLiteral("%1")).arg(smartTouchActive));
    for (const Xt9KdbArea &area : areas) {
        area.serialize(writer);
    }
    writer.writeEndElement();
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
