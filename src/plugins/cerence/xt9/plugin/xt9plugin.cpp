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

#include "xt9plugin.h"
#include "xt9awinputmethod_p.h"
#include "xt9cpinputmethod_p.h"
#include "xt9kinputmethod_p.h"
#include "xt9jinputmethod_p.h"
#include "xt9thaiinputmethod_p.h"
#include <QtQml>

QT_BEGIN_NAMESPACE

using namespace QtVirtualKeyboard;

void QtVirtualKeyboardXt9Plugin::registerTypes(const char *uri) const
{
#ifdef HAVE_XT9_RESOURCE
    Q_INIT_RESOURCE(qmake_cerencecommondata_db);
#endif
    qmlRegisterType<Xt9AwInputMethod>(uri, 2, 0, "DefaultInputMethod");
    qmlRegisterType<Xt9CpInputMethod>(uri, 2, 0, "PinyinInputMethod");
    qmlRegisterType<Xt9CpInputMethod>(uri, 2, 0, "CangjieInputMethod");
    qmlRegisterType<Xt9CpInputMethod>(uri, 2, 0, "StrokeInputMethod");
    qmlRegisterType<Xt9KInputMethod>(uri, 2, 0, "HangulInputMethod");
    qmlRegisterType<Xt9JInputMethod>(uri, 2, 0, "JapaneseInputMethod");
    qmlRegisterType<Xt9ThaiInputMethod>(uri, 2, 0, "ThaiInputMethod");
}

QT_END_NAMESPACE
