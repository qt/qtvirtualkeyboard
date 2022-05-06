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
