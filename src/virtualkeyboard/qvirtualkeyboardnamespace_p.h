// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDNAMESPACE_P_H
#define QVIRTUALKEYBOARDNAMESPACE_P_H

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

#include <QtCore/qmetaobject.h>
#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE

namespace QtVirtualKeyboard {

Q_VIRTUALKEYBOARD_EXPORT Q_NAMESPACE
QML_NAMED_ELEMENT(QtVirtualKeyboard)
QML_ADDED_IN_VERSION(6, 4)

enum class KeyType {
    BaseKey,
    BackspaceKey,
    ChangeLanguageKey,
    EnterKey,
    FillerKey,
    HandwritingModeKey,
    HideKeyboardKey,
    InputModeKey,
    Key,
    ModeKey,
    NumberKey,
    ShiftKey,
    SpaceKey,
    SymbolModeKey,
    FlickKey,
};
Q_ENUM_NS(KeyType)

enum class KeyboardFunction {
    HideInputPanel,
    ChangeLanguage,
    ToggleHandwritingMode,
};
Q_ENUM_NS(KeyboardFunction)

enum class KeyboardFunctionKey : quint32 {
    None = 0,
    Hide = 0x1,
    Language = 0x2,
    All = 0xffffffff,
};
Q_DECLARE_FLAGS(KeyboardFunctionKeys, KeyboardFunctionKey)
Q_DECLARE_OPERATORS_FOR_FLAGS(KeyboardFunctionKeys)
Q_FLAG_NS(KeyboardFunctionKeys)

} // namespace QtVirtualKeyboard

QT_END_NAMESPACE

#endif // QVIRTUALKEYBOARDNAMESPACE_P_H
