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

#ifndef ENTERKEYACTIONATTACHEDTYPE_H
#define ENTERKEYACTIONATTACHEDTYPE_H

#include <QObject>
#include "enterkeyaction.h"

class EnterKeyActionAttachedType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int actionId READ actionId WRITE setActionId NOTIFY actionIdChanged)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit EnterKeyActionAttachedType(QObject *parent);

    int actionId() const;
    void setActionId(int actionId);
    QString label() const;
    void setLabel(const QString& label);
    bool enabled() const;
    void setEnabled(bool enabled);

signals:
    void actionIdChanged();
    void labelChanged();
    void enabledChanged();

private:
    int m_actionId;
    QString m_label;
    bool m_enabled;
};

#endif
