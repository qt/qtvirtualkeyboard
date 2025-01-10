// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9CPINPUTMETHOD_P_H
#define XT9CPINPUTMETHOD_P_H

#include "xt9inputmethod_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9CpInputMethodPrivate;

class Xt9CpInputMethod : public Xt9InputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Xt9CpInputMethod)
    QML_NAMED_ELEMENT(PinyinInputMethod)
    QML_ADDED_IN_VERSION(2, 0)

public:
    explicit Xt9CpInputMethod(QObject *parent = nullptr);

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale);
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode);
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase);

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    QList<QVirtualKeyboardSelectionListModel::Type> selectionLists();
    int selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type);
    QVariant selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index, QVirtualKeyboardSelectionListModel::Role role);
    void selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index);

    void reset();
    void update();
};

class CangjieInputMethod : public Xt9CpInputMethod
{
    Q_OBJECT
    QML_NAMED_ELEMENT(CangjieInputMethod)
public:
    explicit CangjieInputMethod(QObject *parent = nullptr);
};

class StrokeInputMethod : public Xt9CpInputMethod
{
    Q_OBJECT
    QML_NAMED_ELEMENT(StrokeInputMethod)
public:
    explicit StrokeInputMethod(QObject *parent = nullptr);
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
