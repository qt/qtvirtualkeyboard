/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
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

#ifndef APPINPUTPANEL_H
#define APPINPUTPANEL_H

#include "abstractinputpanel.h"

class AppInputPanelPrivate;

class AppInputPanel : public AbstractInputPanel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AppInputPanel)
public:
    explicit AppInputPanel(QObject *parent = 0);
    ~AppInputPanel();

    void show();
    void hide();
    bool isVisible() const;
};

#endif // APPINPUTPANEL_H
