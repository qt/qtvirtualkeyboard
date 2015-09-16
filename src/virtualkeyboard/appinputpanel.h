/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

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
