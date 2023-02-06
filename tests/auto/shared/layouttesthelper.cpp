// Copyright (C) 2016 Pelagicore AB
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
               id: inputPanel; \
               width: parent.width; \
           } \
       }", QUrl());
    window.reset(qobject_cast<QQuickWindow*>(component->create()));
    QVERIFY2(component->status() == QQmlComponent::Ready, qPrintable(component->errorString()));
    QVERIFY(window);
}
