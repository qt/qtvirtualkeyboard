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

#include "hunspellplugin.h"
#include <QtHunspellInputMethod/private/hunspellinputmethod_p.h>
#include <QtQml>

QT_BEGIN_NAMESPACE

using namespace QtVirtualKeyboard;

void QtVirtualKeyboardHunspellPlugin::registerTypes(const char *uri) const
{
    qmlRegisterType<HunspellInputMethod>(uri, 1, 0, "HunspellInputMethod");
    qmlRegisterType<HunspellInputMethod>(uri, 2, 0, "HunspellInputMethod");
    qmlRegisterType<HunspellInputMethod>(uri, 2, 3, "DefaultInputMethod");
}

QT_END_NAMESPACE
