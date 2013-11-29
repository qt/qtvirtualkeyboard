/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
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

#ifndef VKBDEBUG_H
#define VKBDEBUG_H

#include <QDebug>

//#define QT_VKB_DEBUG
#ifdef QT_VKB_DEBUG
#  define VKB_DEBUG qDebug
#else
#  define VKB_DEBUG if (false) qDebug
#endif

#endif // VKBDEBUG_H
