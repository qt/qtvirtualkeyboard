/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
