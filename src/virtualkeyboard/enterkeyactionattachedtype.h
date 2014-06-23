/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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
