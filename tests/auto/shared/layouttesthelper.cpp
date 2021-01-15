/****************************************************************************
**
** Copyright (C) 2016 Pelagicore AB
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

#include "layouttesthelper.h"

#include <QtTest/qtest.h>

LayoutTestHelper::LayoutTestHelper()
{
    component.reset(new QQmlComponent(&engine));
    component->setData("\
       import QtQuick 2.8 \n \
       import QtQuick.Window 2.2 \n \
       import QtQuick.VirtualKeyboard 2.1 \n \
       import QtQuick.VirtualKeyboard.Settings 2.1 \n \
       Window { \
           property var settings: VirtualKeyboardSettings; \
           InputPanel { \
               id: inputPanel \
           } \
       }", QUrl());
    window.reset(qobject_cast<QQuickWindow*>(component->create()));
    QVERIFY2(component->status() == QQmlComponent::Ready, qPrintable(component->errorString()));
    QVERIFY(window);
}
