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

#include "xt9kinputmethodprivate_p.h"
#include <QVirtualKeyboardInputContext>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Xt9KInputMethodPrivate::Xt9KInputMethodPrivate(Xt9KInputMethod *q) :
    Xt9AwInputMethodPrivate(q, new Xt9KIme(this), QStringLiteral("xt9k.dlm"))
{
}

void Xt9KInputMethodPrivate::updatePreeditText()
{
    ET9KHangulWord hangul;
    ET9STATUS eStatus = XT9_API(ET9KBuildHangul, &xt9Ime()->sLingInfo, &hangul);
    if (!eStatus && hangul.wLen) {
        Q_Q(Xt9KInputMethod);
        q->inputContext()->setPreeditText(QString::fromUtf16(reinterpret_cast<const char16_t*>(hangul.sString), hangul.wLen));
    } else {
        Xt9AwInputMethodPrivate::updatePreeditText();
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
