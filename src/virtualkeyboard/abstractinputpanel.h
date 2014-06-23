/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
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
