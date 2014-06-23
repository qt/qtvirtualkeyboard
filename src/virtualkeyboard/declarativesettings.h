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

#ifndef DECLARATIVESETTINGS_H
#define DECLARATIVESETTINGS_H

#include "qqml.h"

class DeclarativeSettingsPrivate;

class DeclarativeSettings : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeclarativeSettings)
    Q_PROPERTY(QUrl style READ style NOTIFY styleChanged)
    Q_PROPERTY(QString styleName READ styleName WRITE setStyleName NOTIFY styleNameChanged)

public:
    static QObject *registerSettingsModule(QQmlEngine *engine, QJSEngine *jsEngine);

    explicit DeclarativeSettings(QQmlEngine *engine);

    QString style() const;

    QString styleName() const;
    void setStyleName(const QString &styleName);

signals:
    void styleChanged();
    void styleNameChanged();

private:
    void resetStyle();
};

#endif // DECLARATIVESETTINGS_H
