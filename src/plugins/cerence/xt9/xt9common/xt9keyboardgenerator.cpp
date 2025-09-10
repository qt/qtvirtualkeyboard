// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9keyboardgenerator.h"
#include "xt9kdblayout.h"
#include "xt9kdb.h"
#include <QtVirtualKeyboard/qvirtualkeyboard_namespace.h>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

const QString Xt9KeyboardGenerator::PRIMARY_ID = QStringLiteral("primaryId");
const QString Xt9KeyboardGenerator::SECONDARY_ID = QStringLiteral("secondaryId");
const QString Xt9KeyboardGenerator::WIDTH = QStringLiteral("width");
const QString Xt9KeyboardGenerator::HEIGHT = QStringLiteral("height");
const QString Xt9KeyboardGenerator::KEY = QStringLiteral("key");
const QString Xt9KeyboardGenerator::KEYS = QStringLiteral("keys");
const QString Xt9KeyboardGenerator::KEY_TYPE = QStringLiteral("keyType");
const QString Xt9KeyboardGenerator::TOP = QStringLiteral("top");
const QString Xt9KeyboardGenerator::LEFT = QStringLiteral("left");
const QString Xt9KeyboardGenerator::TEXT = QStringLiteral("text");
const QString Xt9KeyboardGenerator::ALT_KEYS = QStringLiteral("altKeys");
const int Xt9KeyboardGenerator::EMOTICON_KEY = 0xE000;

Xt9KeyboardGenerator::Xt9KeyboardGenerator(const QVariantMap &vkbLayout, const CodeConverter *keyConverter) :
    vkbLayout(vkbLayout),
    layoutWidth(vkbLayout[WIDTH].toDouble()),
    layoutHeight(vkbLayout[HEIGHT].toDouble()),
    codeConverter(keyConverter)
{

}

QByteArray Xt9KeyboardGenerator::createXmlLayout() const
{
    if (layoutWidth <= 0 || layoutHeight <= 0)
        return QByteArray();

    Xt9KdbLayout kdbLayout;
    kdbLayout.primaryId = vkbLayout[PRIMARY_ID].toInt();
    kdbLayout.secondaryId = vkbLayout[SECONDARY_ID].toInt();
    kdbLayout.defaultLayoutWidth = qRound(layoutWidth);
    kdbLayout.defaultLayoutHeight = qRound(layoutHeight);

    Xt9KdbArea xt9Area;
    if (convertFromVkb(xt9Area))
        kdbLayout.areas.append(xt9Area);

    return Xt9Kdb::generate(kdbLayout, true);
}

bool Xt9KeyboardGenerator::convertFromVkb(Xt9KdbArea &xt9Area) const
{
    QVariantList vkbKeys = vkbLayout[KEYS].toList();

    for (const QVariant &i : vkbKeys) {
        Xt9KdbKey xt9Key;
        if (convertFromVkb(xt9Key, i.toMap()))
            xt9Area.keys.append(xt9Key);
    }

    return true;
}

bool Xt9KeyboardGenerator::convertFromVkb(Xt9KdbKey &xt9Key, const QVariantMap &vkbKey) const
{
    const KeyType vkbKeyType = static_cast<KeyType>(vkbKey[KEY_TYPE].toInt());

    switch (vkbKeyType) {
    case KeyType::BackspaceKey:
        xt9Key.type = Xt9KdbKey::Type::function;
        xt9Key.name = Xt9KdbKey::Name::ET9KEY_BACK;
        break;

    case KeyType::EnterKey:
        xt9Key.type = Xt9KdbKey::Type::function;
        xt9Key.name = Xt9KdbKey::Name::ET9KEY_NEW_LINE;
        break;

    case KeyType::Key:
    case KeyType::FlickKey:
        xt9Key.hackWriteDistinctKeysForAllCodes = (vkbKeyType == KeyType::FlickKey);
        switch (vkbKey[KEY].toInt()) {
        case Qt::Key_Space:
            xt9Key.type = Xt9KdbKey::Type::function;
            xt9Key.name = Xt9KdbKey::Name::ET9KEY_SPACE;
            break;

        case EMOTICON_KEY:
            xt9Key.type = Xt9KdbKey::Type::string;
            break;

        default:
            xt9Key.type = Xt9KdbKey::Type::nonRegional;
            break;
        }
        break;

    case KeyType::SpaceKey:
        xt9Key.type = Xt9KdbKey::Type::function;
        xt9Key.name = Xt9KdbKey::Name::ET9KEY_SPACE;
        break;

    default:
        return false;
    }

    xt9Key.relative.setLeft(vkbKey[LEFT].toDouble() / layoutWidth);
    xt9Key.relative.setTop(vkbKey[TOP].toDouble() / layoutHeight);
    xt9Key.relative.setWidth(vkbKey[WIDTH].toDouble() / layoutWidth);
    xt9Key.relative.setHeight(vkbKey[HEIGHT].toDouble() / layoutHeight);

    switch (xt9Key.type) {
    case Xt9KdbKey::Type::regional:
    case Xt9KdbKey::Type::nonRegional:
    case Xt9KdbKey::Type::string:
        xt9Key.label = vkbKey[TEXT].toString().toUpper();
        if (xt9Key.label.isEmpty())
            return false;
        xt9Key.codes = vkbKey[ALT_KEYS].toString();
        if (codeConverter) {
            xt9Key.label = codeConverter->convertTo(xt9Key.label);
            xt9Key.codes = codeConverter->convertTo(xt9Key.codes);
        }
        break;

    default:
        break;
    }

    return true;
}

Xt9KeyboardGenerator::CodeConverter::~CodeConverter()
{

}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
