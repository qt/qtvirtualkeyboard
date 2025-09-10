// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
