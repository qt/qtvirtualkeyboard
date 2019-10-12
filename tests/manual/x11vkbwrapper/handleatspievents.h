/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef HANDLEATSPIEVENTS_H
#define HANDLEATSPIEVENTS_H

#include <QObject>
#include <QVector>
#include <atspi/atspi.h>

class HandleATSPIEvents : public QObject
{
    Q_OBJECT

public:
    explicit HandleATSPIEvents(QObject *parent = nullptr);
    ~HandleATSPIEvents();

    bool init();

    void gotFocusEventFromInput(const AtspiEvent *event);


private:
    void storeFocusElement(const qint8 role);
    bool isThereFocus(const qint8 role);

public slots:
    void setKeyboardVisible(const bool visible);

private:
    bool m_keyboardVisible;
    QVector<qint8> m_focuses;
};

#endif // HANDLEATSPIEVENTS_H
