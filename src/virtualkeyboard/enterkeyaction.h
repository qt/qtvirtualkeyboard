/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#ifndef ENTERKEYACTION_H
#define ENTERKEYACTION_H

#include <qqml.h>

class EnterKeyActionAttachedType;

class EnterKeyAction : public QObject
{
    Q_OBJECT
    Q_ENUMS(Id)

public:
    enum Id {
        None,
        Go,
        Search,
        Send,
        Next,
        Done
    };

public:
    static EnterKeyActionAttachedType *qmlAttachedProperties(QObject *object);
};

Q_DECLARE_METATYPE(EnterKeyAction::Id)
QML_DECLARE_TYPEINFO(EnterKeyAction, QML_HAS_ATTACHED_PROPERTIES)

#endif
