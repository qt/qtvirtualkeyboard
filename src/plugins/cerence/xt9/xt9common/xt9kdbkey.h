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

#ifndef XT9KDBKEY_H
#define XT9KDBKEY_H

#include "xt9kdbelement.h"
#include <QRect>
#include <QRectF>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9KdbKey : public Xt9KdbElement
{
    Q_GADGET

public:
    enum class Type {
        regional,
        nonRegional,
        smartPunct,
        string,
        function
    };
    Q_ENUM(Type)

    // The names must match with et9kbdef.h.
    // The enum value must not be assigned.
    enum class Name {
        NONE,
        ET9KEY_BACK,
        ET9KEY_TAB,
        ET9KEY_NEW_LINE,
        ET9KEY_SPACE,
        ET9KEY_LEFT,
        ET9KEY_UP,
        ET9KEY_RIGHT,
        ET9KEY_DOWN,
        ET9KEY_SHIFT,
        ET9KEY_LANGUAGE,
    };
    Q_ENUM(Name)

    Xt9KdbKey();

    void serialize(QXmlStreamWriter &writer) const;

    QRect absolute;
    QRectF relative;
    Type type;
    Name name;
    QString label;
    QString labelShifted;
    QString codes;
    QString codesShifted;
    bool hackWriteDistinctKeysForAllCodes;

private:
    template<typename T>
    static QString joinCodeList(const T &codes);
};

template<typename T>
QString Xt9KdbKey::joinCodeList(const T &codes)
{
    static const QString HEX_VALUE = QStringLiteral("0x%1");

    QString result;
    bool first = true;

    for (const QChar &code : codes) {
        if (first)
            first = false;
        else
            result.append(QLatin1Char(','));

        result.append(HEX_VALUE.arg(code.unicode(), 0, 16));
    }

    return result;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9KDBKEY_H
