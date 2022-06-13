// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
