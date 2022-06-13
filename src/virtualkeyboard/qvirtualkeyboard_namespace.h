// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARD_NAMESPACE_H
#define QVIRTUALKEYBOARD_NAMESPACE_H

#include <QMetaEnum>
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

} // namespace QtVirtualKeyboard

QT_END_NAMESPACE

#endif // QVIRTUALKEYBOARD_NAMESPACE_H
