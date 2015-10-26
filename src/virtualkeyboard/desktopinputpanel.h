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

#ifndef DESKTOPINPUTPANEL_H
#define DESKTOPINPUTPANEL_H

#include "appinputpanel.h"

QT_BEGIN_NAMESPACE
class QWindow;
QT_END_NAMESPACE

class DesktopInputPanelPrivate;

class DesktopInputPanel : public AppInputPanel
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
