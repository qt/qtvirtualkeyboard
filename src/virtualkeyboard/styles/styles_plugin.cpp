/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
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

#include "styles_plugin.h"

#include <qqml.h>

/*!
    \qmlmodule QtQuick.Enterprise.VirtualKeyboard.Styles 1.1

    This module provides styling components for the Qt Virtual Keyboard.
*/

void StylesPlugin::registerTypes(const char *uri)
{
#ifdef COMPILING_QML
    Q_INIT_RESOURCE(styles_qtquickcompiler);
#endif
    const QString path(STYLES_IMPORT_PATH);
    qmlRegisterType(QUrl(path + "KeyboardStyle.qml"), uri, 1, 0, "KeyboardStyle");
    qmlRegisterType(QUrl(path + "KeyboardStyle.qml"), uri, 1, 1, "KeyboardStyle");
    qmlRegisterType(QUrl(path + "KeyIcon.qml"), uri, 1, 0, "KeyIcon");
    qmlRegisterType(QUrl(path + "KeyPanel.qml"), uri, 1, 0, "KeyPanel");
    qmlRegisterType(QUrl(path + "SelectionListItem.qml"), uri, 1, 0, "SelectionListItem");
}
