// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9kime.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class JamoConverter : public Xt9KeyboardGenerator::CodeConverter {
public:
    QString convertTo(const QString &codes) const override
    {
        QVector<ushort> jamoBuf(codes.size());
        memcpy(jamoBuf.data(), codes.utf16(), static_cast<size_t>(jamoBuf.size()) * sizeof(ushort));
        XT9_VAPI(ET9KCompatibilityJamoToJamo, jamoBuf.data(), static_cast<ET9U32>(jamoBuf.size()));
        return QString::fromUtf16(reinterpret_cast<const char16_t *>(jamoBuf.constData()), jamoBuf.size());
    }

    QString convertFrom(const QString &codes) const override
    {
        QVector<ushort> jamoBuf(codes.size());
        memcpy(jamoBuf.data(), codes.utf16(), static_cast<size_t>(jamoBuf.size()) * sizeof(ushort));
        XT9_VAPI(ET9KJamoToCompatibilityJamo, jamoBuf.data(), static_cast<ET9U32>(jamoBuf.size()));
        return QString::fromUtf16(reinterpret_cast<const char16_t *>(jamoBuf.constData()), jamoBuf.size());
    }
};

Q_GLOBAL_STATIC(JamoConverter, jamoConverter)

Xt9KIme::Xt9KIme(Xt9RequestCallback *requestCallback) :
    Xt9AwIme(requestCallback, jamoConverter)
{
}

void Xt9KIme::sysInit()
{
    Xt9AwIme::sysInit();
    memset(&sKLingCmn, 0, sizeof(sKLingCmn));
    XT9_API(ET9KSysActivate, &sLingInfo, &sKLingCmn, 1);
}

QString Xt9KIme::exactWord(int *wordCompLen)
{
    return jamoConverter->convertFrom(Xt9AwIme::exactWord(wordCompLen));
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
