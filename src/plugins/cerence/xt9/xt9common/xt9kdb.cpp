// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9kdb.h"
#include <QXmlStreamWriter>
#include <QBuffer>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

QByteArray Xt9Kdb::generate(const Xt9KdbLayout &layout, bool prettyPrint)
{
    QByteArray result;
    QXmlStreamWriter writer(&result);

    writer.setAutoFormatting(prettyPrint);
    writer.writeStartDocument();
    layout.serialize(writer);
    writer.writeEndDocument();

    return result;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
