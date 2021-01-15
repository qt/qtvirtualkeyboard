/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#include <QTextStream>
#include <cstdlib>

extern "C" {
#include <xdo.h>
#include <X11/X.h>
}

#include <cstdio>
#include <cstdlib>

#include "windowhelper.h"

WindowHelper::WindowHelper(QObject *parent) :
    QObject(parent),
    m_xdo(xdo_new(nullptr))
{
}

WindowHelper::~WindowHelper()
{
    xdo_free(m_xdo);
}

Window WindowHelper::findWindowByPid(const qint64 appPid) const
{
    xdo_search_t search;
    memset(&search, 0, sizeof(xdo_search_t));

    search.require = xdo_search::SEARCH_ANY;
    search.searchmask = SEARCH_PID;
    search.pid = static_cast<int>(appPid);
    search.max_depth = -1;

    Window *list;
    quint32 nwindows = 0;

    xdo_search_windows(m_xdo, &search, &list, &nwindows);

    return nwindows > 0 ? list[nwindows-1] : 0;
}

QPair<quint16, quint16> WindowHelper::getWindowDimension(const Window winId) const
{
    Display *display = XOpenDisplay(nullptr);
    XWindowAttributes winAttributes;
    XGetWindowAttributes(display, winId, &winAttributes);

    XCloseDisplay(display);

    return {static_cast<quint16>(winAttributes.width), static_cast<quint16>(winAttributes.height)};
}
