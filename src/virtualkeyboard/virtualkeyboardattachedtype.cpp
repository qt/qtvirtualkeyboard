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
