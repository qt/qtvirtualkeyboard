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

#ifndef INPUTVIEW_H
#define INPUTVIEW_H

#include <QQuickView>

class InputView : public QQuickView
{
    Q_OBJECT
public:
    explicit InputView(QWindow *parent = 0);

signals:
    void sizeChanged();

protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // INPUTVIEW_H
