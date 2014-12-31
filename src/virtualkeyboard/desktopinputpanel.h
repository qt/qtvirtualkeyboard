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
