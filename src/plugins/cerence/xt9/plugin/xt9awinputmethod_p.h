// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9AWINPUTMETHOD_P_H
#define XT9AWINPUTMETHOD_P_H

#include "xt9inputmethod_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9AwInputMethodPrivate;

class Xt9AwInputMethod : public Xt9InputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Xt9AwInputMethod)
    QML_NAMED_ELEMENT(DefaultInputMethod)
    QML_ADDED_IN_VERSION(2, 0)

protected:
    Xt9AwInputMethod(Xt9AwInputMethodPrivate &dd, QObject *parent = nullptr);

public:
    explicit Xt9AwInputMethod(QObject *parent = nullptr);

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale);
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode);
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase);

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    QList<QVirtualKeyboardSelectionListModel::Type> selectionLists();
    int selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type);
    QVariant selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index, QVirtualKeyboardSelectionListModel::Role role);
    void selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index);
    bool selectionListRemoveItem(QVirtualKeyboardSelectionListModel::Type type, int index);

    bool reselect(int cursorPosition, const QVirtualKeyboardInputEngine::ReselectFlags &reselectFlags);

    void reset();
    void update();
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
