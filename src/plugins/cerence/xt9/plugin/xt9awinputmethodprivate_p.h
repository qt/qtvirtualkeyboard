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

#ifndef XT9AWINPUTMETHODPRIVATE_P_H
#define XT9AWINPUTMETHODPRIVATE_P_H

#include "xt9inputmethodprivate_p.h"
#include "xt9awinputmethod_p.h"
#include "xt9awime.h"
#include <QMetaObject>
#include <QByteArray>
#include <QLocale>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9AwInputMethodPrivate : public Xt9InputMethodPrivate
{
public:
    Q_DECLARE_PUBLIC(Xt9AwInputMethod)

protected:
    Xt9AwInputMethodPrivate(Xt9InputMethod *q_ptr, Xt9Ime *xt9Ime, const QString &aDlmFileName);

public:
    Xt9AwInputMethodPrivate(Xt9AwInputMethod *q_ptr);

    inline Xt9AwIme *xt9Ime() const;

    void uninit() override;
    void bindToSettings() override;
    void updateLdb() override;
    void selectionListSelectItem(int index) override;

    bool reselectWord(const QString &word);
    void learnWord(const QString &word);
    bool removeFromDictionary(const QString &word);

    bool isJoiner(const QChar &c) const override;
    ET9U32 inputModeToET9InputMode(QVirtualKeyboardInputEngine::InputMode aInputMode) const override;

    void onDefaultDictionaryDisabledChanged();

private:
    QMetaObject::Connection defaultDictionaryDisabledConnection;
};

Xt9AwIme *Xt9AwInputMethodPrivate::xt9Ime() const
{
    return static_cast<Xt9AwIme *>(_xt9Ime.data());
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9AWINPUTMETHODPRIVATE_P_H
