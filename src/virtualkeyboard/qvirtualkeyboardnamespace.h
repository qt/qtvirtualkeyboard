// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDNAMESPACE_H
#define QVIRTUALKEYBOARDNAMESPACE_H

#include <QtCore/qmetaobject.h>
#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE

namespace QtVirtualKeyboard {

Q_VIRTUALKEYBOARD_EXPORT Q_NAMESPACE
QML_NAMED_ELEMENT(QtVirtualKeyboard)

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
    NoFunctionKeys = 0,
    HideFunctionKey = 0x1,
    LanguageFunctionKey = 0x2,
    AllFunctionKeys = 0xffffffff,
};
Q_DECLARE_FLAGS(KeyboardFunctionKeys, KeyboardFunctionKey)
Q_DECLARE_OPERATORS_FOR_FLAGS(KeyboardFunctionKeys)
Q_FLAG_NS(KeyboardFunctionKeys)

} // namespace QtVirtualKeyboard

QT_END_NAMESPACE

#endif // QVIRTUALKEYBOARDNAMESPACE_H
