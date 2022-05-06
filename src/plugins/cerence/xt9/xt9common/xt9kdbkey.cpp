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

#include "xt9kdbkey.h"
#include <QMetaEnum>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

static const QString DP_VALUE = QStringLiteral("%1dp");
static const QString PC_VALUE = QStringLiteral("%1%");
const QString HEX_VALUE = QStringLiteral("0x%1");

static bool isPrintable(const QString &str)
{
    for (const QChar &chr : str) {
        if (!QChar::isPrint(chr.unicode()))
            return false;
    }
    return true;
}

Xt9KdbKey::Xt9KdbKey() :
    type(Type::nonRegional),
    name(Name::NONE)
{

}

void Xt9KdbKey::serialize(QXmlStreamWriter &writer) const
{
    /* WORKAROUND:
     *
     * This workaround generates a key for each alternate key. This ensures that
     * ET9KDB_ProcessKeyBySymbol finds the key and that ET9KDB_ModifyCurrentKey
     * works.
     */
    if (hackWriteDistinctKeysForAllCodes && !codes.isEmpty()) {
        Xt9KdbKey tmpKey;
        tmpKey = *this;
        tmpKey.hackWriteDistinctKeysForAllCodes = false;
        tmpKey.codes.clear();
        tmpKey.codesShifted.clear();
        if (!absolute.isEmpty()) {
            tmpKey.absolute.adjust(0, 0, (tmpKey.absolute.width() / (codes.size() + 1)) - tmpKey.absolute.width(), 0);
        } else if (!relative.isEmpty()) {
            tmpKey.relative.adjust(0, 0, (tmpKey.relative.width() / (codes.size() + 1)) - tmpKey.relative.width(), 0);
        }
        tmpKey.serialize(writer);
        if (!absolute.isEmpty()) {
            tmpKey.absolute.adjust(tmpKey.absolute.width(), 0, tmpKey.absolute.width(), 0);
        } else if (!relative.isEmpty()) {
            tmpKey.relative.adjust(tmpKey.relative.width(), 0, tmpKey.relative.width(), 0);
        }
        for (const QChar &code : codes) {
            tmpKey.label = code;
            if (!labelShifted.isEmpty())
                tmpKey.labelShifted = code.toUpper();
            tmpKey.serialize(writer);
            if (!absolute.isEmpty()) {
                tmpKey.absolute.adjust(tmpKey.absolute.width(), 0, tmpKey.absolute.width(), 0);
            } else if (!relative.isEmpty()) {
                tmpKey.relative.adjust(tmpKey.relative.width(), 0, tmpKey.relative.width(), 0);
            }
        }
        return;
    }
    /* WORKAROUND END */
    if (!absolute.isEmpty()) {
        writer.writeStartElement(QStringLiteral("key"));
        writer.writeAttribute(QStringLiteral("keyLeft"), DP_VALUE.arg(absolute.left()));
        writer.writeAttribute(QStringLiteral("keyTop"), DP_VALUE.arg(absolute.top()));
        writer.writeAttribute(QStringLiteral("keyWidth"), DP_VALUE.arg(absolute.width()));
        writer.writeAttribute(QStringLiteral("keyHeight"), DP_VALUE.arg(absolute.height()));
    } else if (!relative.isEmpty()) {
        writer.writeStartElement(QStringLiteral("key"));
        writer.writeAttribute(QStringLiteral("keyLeft"), PC_VALUE.arg(relative.left() * 100.));
        writer.writeAttribute(QStringLiteral("keyTop"), PC_VALUE.arg(relative.top() * 100.));
        writer.writeAttribute(QStringLiteral("keyWidth"), PC_VALUE.arg(relative.width() * 100.));
        writer.writeAttribute(QStringLiteral("keyHeight"), PC_VALUE.arg(relative.height() * 100.));
    } else {
        // No geometry, skip
        return;
    }
    writer.writeAttribute(QStringLiteral("keyType"), QMetaEnum::fromType<Xt9KdbKey::Type>().key(static_cast<int>(type)));
    if (name != Name::NONE)
        writer.writeAttribute(QStringLiteral("keyName"), QMetaEnum::fromType<Xt9KdbKey::Name>().key(static_cast<int>(name)));
    if (!label.isEmpty())
        writer.writeAttribute(QStringLiteral("keyLabel"), isPrintable(label) ? label : joinCodeList(label));
    if (!labelShifted.isEmpty())
        writer.writeAttribute(QStringLiteral("keyLabelShifted"), isPrintable(labelShifted) ? labelShifted : joinCodeList(labelShifted));
    if (!codes.isEmpty())
        writer.writeAttribute(QStringLiteral("keyCodes"), joinCodeList(codes));
    if (!codesShifted.isEmpty())
        writer.writeAttribute(QStringLiteral("keyCodesShifted"), joinCodeList(codesShifted));
    writer.writeEndElement();
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
