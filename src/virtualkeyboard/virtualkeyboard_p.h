// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef VIRTUALKEYBOARD_P_H
#define VIRTUALKEYBOARD_P_H

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

#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class VirtualKeyboardAttachedType;

class Q_VIRTUALKEYBOARD_EXPORT VirtualKeyboard : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(VirtualKeyboard)
    QML_UNCREATABLE("VirtualKeyboard is an abstract type that is only available as an attached property.")
    QML_ATTACHED(VirtualKeyboardAttachedType)
    QML_ADDED_IN_VERSION(6, 1)

public:
    static VirtualKeyboardAttachedType *qmlAttachedProperties(QObject *object);
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QT_PREPEND_NAMESPACE(QtVirtualKeyboard)::VirtualKeyboard, QML_HAS_ATTACHED_PROPERTIES)

#endif
