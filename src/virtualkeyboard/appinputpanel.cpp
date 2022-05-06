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

#include <QtVirtualKeyboard/private/appinputpanel_p.h>
#include <QtVirtualKeyboard/private/appinputpanel_p_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

AppInputPanel::AppInputPanel(AppInputPanelPrivate &dd, QObject *parent) :
    AbstractInputPanel(dd, parent)
{
}

AppInputPanel::AppInputPanel(QObject *parent) :
    AbstractInputPanel(*new AppInputPanelPrivate(), parent)
{
}

AppInputPanel::~AppInputPanel()
{
}

void AppInputPanel::show()
{
    Q_D(AppInputPanel);
    if (!d->visible) {
        d->visible = true;
    }
}

void AppInputPanel::hide()
{
    Q_D(AppInputPanel);
    if (d->visible) {
        d->visible = false;
    }
}

bool AppInputPanel::isVisible() const
{
    Q_D(const AppInputPanel);
    return d->visible;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
