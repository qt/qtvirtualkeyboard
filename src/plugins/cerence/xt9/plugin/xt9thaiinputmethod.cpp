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

#include "xt9thaiinputmethod_p.h"
#include "xt9thaiinputmethodprivate_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::Xt9ThaiInputMethod
    \internal
*/

Xt9ThaiInputMethod::Xt9ThaiInputMethod(QObject *parent) :
    Xt9AwInputMethod(*new Xt9ThaiInputMethodPrivate(this), parent)
{
}

bool Xt9ThaiInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    const bool isMark = text.length() == 2 && text.at(0) == QLatin1Char(' ');
    if (isMark) {
        const QString mark(text.right(1));
        return Xt9AwInputMethod::keyEvent(static_cast<Qt::Key>(mark.at(0).unicode()),
                                          mark, modifiers);
    }
    return Xt9AwInputMethod::keyEvent(key, text, modifiers);
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
