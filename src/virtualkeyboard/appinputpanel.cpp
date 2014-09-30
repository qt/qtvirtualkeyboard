/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

#include "appinputpanel.h"
#include <QtCore/private/qobject_p.h>

class AppInputPanelPrivate : public QObjectPrivate
{
public:
    AppInputPanelPrivate() :
        QObjectPrivate(),
        visible(false)
    {
    }

    bool visible;
};

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
