/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#ifndef T9WRITE_P_H
#define T9WRITE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

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

#endif // T9WRITE_P_H
