// Copyright (C) 2016 Pelagicore AB
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCore/qscopedpointer.h>
#include <QtCore/QString>
#include <QtQml/qqmlcomponent.h>
#include <QtQml/qqmlengine.h>
#include <QtQuick/qquickwindow.h>

class LayoutTestHelper : public QObject
{
    Q_OBJECT

public:
    LayoutTestHelper();

    QScopedPointer<QQmlComponent> component;
    QScopedPointer<QQuickWindow> window;

private:
    QQmlEngine engine;
};
