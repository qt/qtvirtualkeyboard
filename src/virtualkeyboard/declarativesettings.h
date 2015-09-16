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
