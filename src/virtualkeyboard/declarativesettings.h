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

#ifndef DECLARATIVESETTINGS_H
#define DECLARATIVESETTINGS_H

#include "qqml.h"

namespace QtVirtualKeyboard {

class DeclarativeSettingsPrivate;

class DeclarativeSettings : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeclarativeSettings)
    Q_PROPERTY(QUrl style READ style NOTIFY styleChanged)
    Q_PROPERTY(QString styleName READ styleName WRITE setStyleName NOTIFY styleNameChanged)
    Q_PROPERTY(QString locale READ locale WRITE setLocale NOTIFY localeChanged)
    Q_PROPERTY(QStringList availableLocales READ availableLocales NOTIFY availableLocalesChanged)
    Q_PROPERTY(QStringList activeLocales READ activeLocales WRITE setActiveLocales NOTIFY activeLocalesChanged)

public:
    static QObject *registerSettingsModule(QQmlEngine *engine, QJSEngine *jsEngine);

    explicit DeclarativeSettings(QQmlEngine *engine);

    QString style() const;

    QString styleName() const;
    void setStyleName(const QString &styleName);

    QString locale() const;
    void setLocale(const QString &locale);

    QStringList availableLocales() const;

    void setActiveLocales(const QStringList &activeLocales);
    QStringList activeLocales() const;

signals:
    void styleChanged();
    void styleNameChanged();
    void localeChanged();
    void availableLocalesChanged();
    void activeLocalesChanged();

private:
    void resetStyle();
};

}

#endif // DECLARATIVESETTINGS_H
