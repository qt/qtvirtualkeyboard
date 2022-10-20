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

#ifndef XT9KEYBOARDGENERATOR_H
#define XT9KEYBOARDGENERATOR_H

#include <QVariantMap>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9KdbArea;
class Xt9KdbKey;

class Xt9KeyboardGenerator
{
public:
    class CodeConverter;

    Xt9KeyboardGenerator(const QVariantMap &vkbLayout, const CodeConverter *codeConverter = nullptr);

    QByteArray createXmlLayout() const;

    static const QString PRIMARY_ID;
    static const QString SECONDARY_ID;
    static const QString WIDTH;
    static const QString HEIGHT;
    static const QString KEY;
    static const QString KEYS;
    static const QString KEY_TYPE;
    static const QString TOP;
    static const QString LEFT;
    static const QString TEXT;
    static const QString ALT_KEYS;
    static const int EMOTICON_KEY;

    class CodeConverter {
    public:
        virtual ~CodeConverter();
        virtual QString convertTo(const QString &codes) const = 0;
        virtual QString convertFrom(const QString &codes) const = 0;
    };

private:
    bool convertFromVkb(Xt9KdbArea &xt9Area) const;
    bool convertFromVkb(Xt9KdbKey &xt9Key, const QVariantMap &vkbKey) const;

public:
    const QVariantMap vkbLayout;
    const double layoutWidth;
    const double layoutHeight;
    const CodeConverter *codeConverter;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9KEYBOARDGENERATOR_H
