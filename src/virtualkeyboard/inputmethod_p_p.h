// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef INPUTMETHOD_P_P_H
#define INPUTMETHOD_P_P_H

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

#include <private/qvirtualkeyboardabstractinputmethod_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class InputMethodPrivate : public QVirtualKeyboardAbstractInputMethodPrivate
{
public:
    bool resetLock = false;
    bool updateLock = false;
    bool clearInputModeLock = false;
};

}
QT_END_NAMESPACE

#endif // INPUTMETHOD_P_P_H
