/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

#ifndef CERENCE_HWR_P_H
#define CERENCE_HWR_P_H

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

#include <QtVirtualKeyboard/private/qvirtualkeyboard_global_p.h>

#include "cerence_handwriting_api_version.h"
#if QT_CONFIG(cerence_hwr_alphabetic)
#include "decuma_hwr.h"
#endif
#if QT_CONFIG(cerence_hwr_cjk)
#include "decuma_hwr_cjk.h"
#endif

#if QT_CONFIG(cerence_hwr_cjk) && QT_CONFIG(cerence_hwr_alphabetic)
#define DECUMA_API(FUNC_NAME) (cjk ? decumaCJK ## FUNC_NAME : decumaUcr ## FUNC_NAME)
#elif QT_CONFIG(cerence_hwr_cjk)
#define DECUMA_API(FUNC_NAME) (decumaCJK ## FUNC_NAME)
#else // QT_CONFIG(cerence_hwr_alphabetic)
#define DECUMA_API(FUNC_NAME) (decumaUcr ## FUNC_NAME)
#endif

#endif // CERENCE_HWR_P_H
