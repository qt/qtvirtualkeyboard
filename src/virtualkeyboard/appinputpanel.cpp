/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include "appinputpanel.h"

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
