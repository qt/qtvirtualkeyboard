/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
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

#ifndef T9WRITE_H
#define T9WRITE_H

#include "t9write_api_version.h"
#ifdef HAVE_T9WRITE_ALPHABETIC
#include "decuma_hwr.h"
#endif
#ifdef HAVE_T9WRITE_CJK
#include "decuma_hwr_cjk.h"
#endif
#include "decumaFunctionalSupport.h"

#if defined(HAVE_T9WRITE_CJK) && defined(HAVE_T9WRITE_ALPHABETIC)
#define DECUMA_API(FUNC_NAME) (cjk ? decumaCJK ## FUNC_NAME : decuma ## FUNC_NAME)
#elif defined(HAVE_T9WRITE_CJK)
#define DECUMA_API(FUNC_NAME) (decumaCJK ## FUNC_NAME)
#else // defined(HAVE_T9WRITE_ALPHABETIC)
#define DECUMA_API(FUNC_NAME) (decuma ## FUNC_NAME)
#endif

#endif // T9WRITE_H
