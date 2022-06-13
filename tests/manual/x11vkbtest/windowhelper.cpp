// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QTextStream>

#include "windowhelper.h"

extern "C" {
#include <xdo.h>
#include <X11/X.h>
}

#include <cstdio>
#include <cstdlib>


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
