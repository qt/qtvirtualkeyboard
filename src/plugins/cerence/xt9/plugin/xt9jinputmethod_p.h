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
