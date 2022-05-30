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

#ifndef QVIRTUALKEYBOARDEXTENSIONPLUGIN_H
#define QVIRTUALKEYBOARDEXTENSIONPLUGIN_H

#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/QtPlugin>

QT_BEGIN_NAMESPACE

#define QVirtualKeyboardExtensionPluginFactoryInterface_iid "org.qt-project.qt.virtualkeyboard.plugin/5.12"

class QVIRTUALKEYBOARD_EXPORT QVirtualKeyboardExtensionPlugin : public QObject
{
    Q_OBJECT
public:
    virtual ~QVirtualKeyboardExtensionPlugin();

    virtual void registerTypes(const char *uri) const;
};

Q_DECLARE_INTERFACE(QVirtualKeyboardExtensionPlugin,
                    QVirtualKeyboardExtensionPluginFactoryInterface_iid)

QT_END_NAMESPACE

#endif
