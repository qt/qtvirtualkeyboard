/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qtquickvirtualkeyboardstylesplugin.h"
#include "svgimageprovider.h"

#include <qqml.h>
#include <QtCore/QLibraryInfo>
#include <QtVirtualKeyboard/private/qvirtualkeyboard_staticplugin_p.h>

QT_BEGIN_NAMESPACE

/*!
    \qmlmodule QtQuick.VirtualKeyboard.Styles 2.\QtMinorVersion
    \title Qt Quick Virtual Keyboard Styles QML Types
    \ingroup qmlmodules

    \brief Provides styling for Qt Virtual Keyboard.

    The QML types can be imported into your application using the following
    import statements in your .qml file:

    \qml \QtMinorVersion
    import QtQuick.VirtualKeyboard.Styles 2.\1
    \endqml
*/

void QtQuickVirtualKeyboardStylesPlugin::registerTypes(const char *uri)
{
#if defined(QT_STATICPLUGIN)
    Q_VKB_IMPORT_PLUGIN(QtQuick2Plugin)
#endif

    const QString path(QStringLiteral("qrc:///QtQuick/VirtualKeyboard/Styles/content/"));
    qmlRegisterType(QUrl(path + QLatin1String("KeyboardStyle.qml")), uri, 1, 0, "KeyboardStyle");
    qmlRegisterType(QUrl(path + QLatin1String("KeyboardStyle.qml")), uri, 1, 1, "KeyboardStyle");
    qmlRegisterType(QUrl(path + QLatin1String("KeyboardStyle.qml")), uri, 1, 2, "KeyboardStyle");
    qmlRegisterType(QUrl(path + QLatin1String("KeyboardStyle.qml")), uri, 1, 3, "KeyboardStyle");
    qmlRegisterType(QUrl(path + QLatin1String("KeyboardStyle.qml")), uri, 2, 0, "KeyboardStyle");
    qmlRegisterType(QUrl(path + QLatin1String("KeyboardStyle.qml")), uri, 2, 1, "KeyboardStyle");
    qmlRegisterType(QUrl(path + QLatin1String("KeyboardStyle.qml")), uri, 2, 2, "KeyboardStyle");
    qmlRegisterType(QUrl(path + QLatin1String("KeyIcon.qml")), uri, 1, 0, "KeyIcon");
    qmlRegisterType(QUrl(path + QLatin1String("KeyIcon.qml")), uri, 2, 0, "KeyIcon");
    qmlRegisterType(QUrl(path + QLatin1String("KeyPanel.qml")), uri, 1, 0, "KeyPanel");
    qmlRegisterType(QUrl(path + QLatin1String("KeyPanel.qml")), uri, 2, 0, "KeyPanel");
    qmlRegisterType(QUrl(path + QLatin1String("SelectionListItem.qml")), uri, 1, 0, "SelectionListItem");
    qmlRegisterType(QUrl(path + QLatin1String("SelectionListItem.qml")), uri, 2, 0, "SelectionListItem");
    qmlRegisterType(QUrl(path + QLatin1String("TraceInputKeyPanel.qml")), uri, 2, 0, "TraceInputKeyPanel");
    qmlRegisterType(QUrl(path + QLatin1String("TraceCanvas.qml")), uri, 2, 0, "TraceCanvas");

    // The minor version used to be the current Qt 5 minor. For compatibility it is the last
    // Qt 5 release.
    qmlRegisterModule(uri, 2, 15);
}

void QtQuickVirtualKeyboardStylesPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    engine->addImageProvider(QStringLiteral("qtvkbsvg"), new SvgImageProvider());
}

QT_END_NAMESPACE
