// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef ENTERKEYACTION_P_H
#define ENTERKEYACTION_P_H

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

class EnterKeyActionAttachedType;

class Q_VIRTUALKEYBOARD_EXPORT EnterKeyAction : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(EnterKeyAction)
    QML_UNCREATABLE("EnterKeyAction is an abstract type that is only available as an attached property.")
    QML_ATTACHED(EnterKeyActionAttachedType)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    enum Id {
        None,
        Go,
        Search,
        Send,
        Next,
        Done
    };

    Q_ENUM(Id)

public:
    static EnterKeyActionAttachedType *qmlAttachedProperties(QObject *object);
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

Q_DECLARE_METATYPE(QT_PREPEND_NAMESPACE(QtVirtualKeyboard)::EnterKeyAction::Id)
QML_DECLARE_TYPEINFO(QT_PREPEND_NAMESPACE(QtVirtualKeyboard)::EnterKeyAction, QML_HAS_ATTACHED_PROPERTIES)

#endif
