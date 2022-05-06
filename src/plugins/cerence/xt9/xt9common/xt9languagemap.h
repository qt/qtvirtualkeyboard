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
