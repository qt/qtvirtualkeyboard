// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/qvirtualkeyboardabstractinputmethod_p.h>

QT_BEGIN_NAMESPACE

/*!
    \class QVirtualKeyboardAbstractInputMethodPrivate
    \internal
*/

QVirtualKeyboardAbstractInputMethodPrivate::QVirtualKeyboardAbstractInputMethodPrivate() :
    QObjectPrivate(),
    inputEngine(nullptr)
{
}

QT_END_NAMESPACE
