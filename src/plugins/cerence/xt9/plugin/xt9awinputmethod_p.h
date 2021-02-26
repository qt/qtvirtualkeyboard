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
