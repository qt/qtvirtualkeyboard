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

#ifndef ABSTRACTINPUTPANEL_H
#define ABSTRACTINPUTPANEL_H

#include <QObject>

namespace QtVirtualKeyboard {

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

} // namespace QtVirtualKeyboard

#endif // ABSTRACTINPUTPANEL_H
