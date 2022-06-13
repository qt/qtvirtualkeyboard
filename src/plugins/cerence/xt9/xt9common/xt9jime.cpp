// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9jime.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class KanaConverter : public Xt9KeyboardGenerator::CodeConverter {
public:
    QString convertTo(const QString &codes) const override
    {
        QString buf(codes);
        for (int i = 0; i < buf.length(); ++i) {
            const ushort uc = buf.at(i).unicode();
            if ((uc >= 0x30a1 && uc <= 0x30f6) || uc == 0x30fd || uc == 0x30fe)
                buf.replace(i, 1, QChar(uc - 0x0060));
        }
        return buf;
    }

    QString convertFrom(const QString &codes) const override
    {
        QString buf(codes);
        for (int i = 0; i < buf.length(); ++i) {
            const ushort uc = buf.at(i).unicode();
            if ((uc >= 0x30a1 && uc <= 0x30f6) || uc == 0x30fd || uc == 0x30fe)
                buf.replace(i, 1, QChar(uc + 0x0060));
        }
        return buf;
    }
};

Q_GLOBAL_STATIC(KanaConverter, kanaConverter)

Xt9JIme::Xt9JIme(Xt9RequestCallback *requestCallback) :
    Xt9AwIme(requestCallback, kanaConverter)
{
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
