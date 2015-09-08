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

#ifndef DESKTOPINPUTPANEL_H
#define DESKTOPINPUTPANEL_H

#include "abstractinputpanel.h"

QT_BEGIN_NAMESPACE
class QWindow;
QT_END_NAMESPACE

class DesktopInputPanelPrivate;

class DesktopInputPanel : public AbstractInputPanel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DesktopInputPanel)
public:
    explicit DesktopInputPanel(QObject *parent = 0);
    ~DesktopInputPanel();

    void show();
    void hide();
    bool isVisible() const;

    void setInputRect(const QRect &inputRect);

public slots:
    void createView();
    void destroyView();

protected slots:
    void repositionView(const QRect &rect);
    void focusWindowChanged(QWindow *focusWindow);
    void focusWindowVisibleChanged(bool visible);
    void previewRectangleChanged();
    void previewVisibleChanged();

protected:
    void updateInputRegion();
};

#endif // DESKTOPINPUTPANEL_H
