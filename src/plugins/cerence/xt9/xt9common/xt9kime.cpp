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

#include "xt9kime.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class JamoConverter : public Xt9KeyboardGenerator::CodeConverter {
public:
    QString convertTo(const QString &codes) const override
    {
        QVector<ushort> jamoBuf(codes.size());
        memcpy(jamoBuf.data(), codes.utf16(), static_cast<size_t>(jamoBuf.size()) * sizeof(ushort));
        XT9_VAPI(ET9KCompatibilityJamoToJamo, jamoBuf.data(), static_cast<ET9U32>(jamoBuf.length()));
        return QString::fromUtf16(reinterpret_cast<const char16_t *>(jamoBuf.constData()), jamoBuf.length());
    }

    QString convertFrom(const QString &codes) const override
    {
        QVector<ushort> jamoBuf(codes.size());
        memcpy(jamoBuf.data(), codes.utf16(), static_cast<size_t>(jamoBuf.size()) * sizeof(ushort));
        XT9_VAPI(ET9KJamoToCompatibilityJamo, jamoBuf.data(), static_cast<ET9U32>(jamoBuf.length()));
        return QString::fromUtf16(reinterpret_cast<const char16_t *>(jamoBuf.constData()), jamoBuf.length());
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
