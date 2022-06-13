// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "qtquickvirtualkeyboardstylesplugin.h"
#include "svgimageprovider.h"

#include <QtQml/qqml.h>
#include <QtCore/QLibraryInfo>

QT_BEGIN_NAMESPACE

extern void qml_register_types_QtQuick_VirtualKeyboard_Styles();
Q_GHS_KEEP_REFERENCE(qml_register_types_QtQuick_VirtualKeyboard_Styles);

/*!
    \qmlmodule QtQuick.VirtualKeyboard.Styles
    \title Qt Quick Virtual Keyboard Styles QML Types
    \ingroup qmlmodules

    \brief Provides styling for Qt Virtual Keyboard.

    The QML types can be imported into your application using the following
    import statements in your .qml file:

    \qml
    import QtQuick.VirtualKeyboard.Styles
    \endqml
*/

QtQuickVirtualKeyboardStylesPlugin::QtQuickVirtualKeyboardStylesPlugin(QObject *parent) :
    QQmlExtensionPlugin(parent)
{
    volatile auto registration = &qml_register_types_QtQuick_VirtualKeyboard_Styles;
    Q_UNUSED(registration);
}

void QtQuickVirtualKeyboardStylesPlugin::registerTypes(const char *uri)
{
    Q_UNUSED(uri);
}

void QtQuickVirtualKeyboardStylesPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    engine->addImageProvider(QStringLiteral("qtvkbsvg"), new SvgImageProvider());
}

QT_END_NAMESPACE
