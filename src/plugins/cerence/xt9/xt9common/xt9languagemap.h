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

#ifndef XT9LANGUAGEMAP_H
#define XT9LANGUAGEMAP_H

#include <QLocale>
#include <et9api.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9LanguageMap
{
private:
    Xt9LanguageMap();

public:
    static ET9U32 languageId(const QLocale &locale);
    static QLocale locale(ET9U32 languageId);

private:
    struct SimpleLanguageMapEntry {
        ET9U32 languageId;
        QLocale::Language localeLanguage;
    };

    struct LanguageMapEntry {
        ET9U32 languageId;
        QLocale locale;
    };

    static const SimpleLanguageMapEntry SIMPLE_LANGUAGE_MAP[];
    static const struct LanguageMapEntry LANGUAGE_MAP[];
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9LANGUAGEMAP_H
