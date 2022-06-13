// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/virtualkeyboardattachedtype_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::VirtualKeyboardAttachedType
    \internal
*/

VirtualKeyboardAttachedType::VirtualKeyboardAttachedType(QObject *parent) :
    QObject(parent)
{
}

QStringList QtVirtualKeyboard::VirtualKeyboardAttachedType::extraDictionaries() const
{
    return _extraDictionaries;
}

void QtVirtualKeyboard::VirtualKeyboardAttachedType::setExtraDictionaries(const QStringList &extraDictionaries)
{
    if (_extraDictionaries != extraDictionaries) {
        _extraDictionaries = extraDictionaries;
        emit extraDictionariesChanged();
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
