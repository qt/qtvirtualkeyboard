/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

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
