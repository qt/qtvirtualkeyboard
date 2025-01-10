// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9THAIINPUTMETHOD_P_H
#define XT9THAIINPUTMETHOD_P_H

#include "xt9awinputmethod_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9ThaiInputMethodPrivate;

class Xt9ThaiInputMethod : public Xt9AwInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Xt9ThaiInputMethod)
    QML_NAMED_ELEMENT(ThaiInputMethod)
    QML_ADDED_IN_VERSION(2, 0)

public:
    explicit Xt9ThaiInputMethod(QObject *parent = nullptr);

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
