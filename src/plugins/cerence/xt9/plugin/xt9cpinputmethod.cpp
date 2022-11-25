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

#include "xt9cpinputmethod_p.h"
#include "xt9cpinputmethodprivate_p.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QtVirtualKeyboard/qvirtualkeyboardobserver.h>
#include <QLoggingCategory>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::Xt9CpInputMethod
    \internal
*/

Xt9CpInputMethod::Xt9CpInputMethod(QObject *parent) :
    Xt9InputMethod(*new Xt9CpInputMethodPrivate(this), parent)
{
}

QList<QVirtualKeyboardInputEngine::InputMode> Xt9CpInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale)
    QList<QVirtualKeyboardInputEngine::InputMode> result;
    result.append(QVirtualKeyboardInputEngine::InputMode::Pinyin);
    result.append(QVirtualKeyboardInputEngine::InputMode::Cangjie);
    result.append(QVirtualKeyboardInputEngine::InputMode::Stroke);
    return result;
}

bool Xt9CpInputMethod::setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
{
    Q_D(Xt9CpInputMethod);

    return d->init(QLocale(locale), inputMode);
}

bool Xt9CpInputMethod::setTextCase(QVirtualKeyboardInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase)
    return true;
}

bool Xt9CpInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers)
    Q_D(Xt9CpInputMethod);

    switch (key) {
    case Qt::Key_Backspace:
        return d->processBackspace();

    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Tab:
    case Qt::Key_Space:
        if (d->xt9Ime()->hasActiveInput() && !d->selectionList.isEmpty() && d->defaultListIndex >= 0) {
            selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, d->defaultListIndex);
            return key == Qt::Key_Space;
        }

        update();
        break;

    case Qt::Key_Shift:
        break;

    case Qt::Key_Apostrophe:
        d->cycleTones();
        return true;

    default:
        if (text.length() > 0) {
            if (text.length() == 1) {
                QString symbs = (d->inputMode == QVirtualKeyboardInputEngine::InputMode::Cangjie) ?
                    d->xt9Ime()->getCangjieConverter()->convertFrom(text) : text;
                if (!d->processKeyBySymbol(symbs.at(0))) {
                    inputContext()->sendKeyClick(key, text, modifiers);
                }
            } else {
                update();
                inputContext()->commit(text);
            }
            return true;
        }
        break;
    }

    return false;
}

QList<QVirtualKeyboardSelectionListModel::Type> Xt9CpInputMethod::selectionLists()
{
    return QList<QVirtualKeyboardSelectionListModel::Type>() << QVirtualKeyboardSelectionListModel::Type::WordCandidateList;
}

int Xt9CpInputMethod::selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type)
{
    Q_UNUSED(type)
    Q_D(Xt9CpInputMethod);
    return d->selectionList.count();
}

QVariant Xt9CpInputMethod::selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index, QVirtualKeyboardSelectionListModel::Role role)
{
    QVariant result;
    Q_D(Xt9CpInputMethod);
    switch (role) {
    case QVirtualKeyboardSelectionListModel::Role::Display:
        result = QVariant(d->selectionList.at(index));
        break;
    case QVirtualKeyboardSelectionListModel::Role::WordCompletionLength:
        result.setValue(0);
        break;
    default:
        result = QVirtualKeyboardAbstractInputMethod::selectionListData(type, index, role);
        break;
    }
    return result;
}

void Xt9CpInputMethod::selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index)
{
    Q_UNUSED(type)
    Q_D(Xt9CpInputMethod);

    d->selectionListSelectItem(index);
}

void Xt9CpInputMethod::reset()
{
    Q_D(Xt9CpInputMethod);

    d->reset();
}

void Xt9CpInputMethod::update()
{
    Q_D(Xt9CpInputMethod);

    if (d->xt9Ime()->hasActiveInput() && !d->selectionList.isEmpty() && d->defaultListIndex >= 0) {
        d->selectionListSelectItem(d->defaultListIndex);
    }

    inputContext()->clear();

    d->reset();
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
