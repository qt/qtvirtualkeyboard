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

#ifndef ABSTRACTINPUTPANEL_H
#define ABSTRACTINPUTPANEL_H

#include <QObject>

class AbstractInputPanel : public QObject
{
    Q_OBJECT
protected:
    AbstractInputPanel(QObjectPrivate &dd, QObject *parent = 0);
public:
    explicit AbstractInputPanel(QObject *parent = 0);
    ~AbstractInputPanel();

    virtual void show() = 0;
    virtual void hide() = 0;
    virtual bool isVisible() const = 0;

    virtual void setInputRect(const QRect &inputRect);

public slots:
    virtual void createView();
    virtual void destroyView();
};

#endif // ABSTRACTINPUTPANEL_H
