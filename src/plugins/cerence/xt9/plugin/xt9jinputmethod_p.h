// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9JINPUTMETHOD_P_H
#define XT9JINPUTMETHOD_P_H

#include "xt9awinputmethod_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9JInputMethodPrivate;

class Xt9JInputMethod : public Xt9AwInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Xt9JInputMethod)
    Q_PROPERTY(bool modifyKeyEnabled READ isModifyKeyEnabled NOTIFY modifyKeyEnabledChanged)
    QML_NAMED_ELEMENT(JapaneseInputMethod)
    QML_ADDED_IN_VERSION(2, 0)

public:
    explicit Xt9JInputMethod(QObject *parent = nullptr);

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale) override;
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode) override;

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;

    bool isModifyKeyEnabled() const;

signals:
    void modifyKeyEnabledChanged();
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
