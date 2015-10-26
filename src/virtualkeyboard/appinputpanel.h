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

#ifndef APPINPUTPANEL_H
#define APPINPUTPANEL_H

#include "abstractinputpanel.h"
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

class AppInputPanel : public AbstractInputPanel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AppInputPanel)

protected:
    AppInputPanel(AppInputPanelPrivate &dd, QObject *parent = 0);

public:
    explicit AppInputPanel(QObject *parent = 0);
    ~AppInputPanel();

    void show();
    void hide();
    bool isVisible() const;
};

#endif // APPINPUTPANEL_H
