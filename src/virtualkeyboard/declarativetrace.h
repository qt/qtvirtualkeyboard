/****************************************************************************
**
** Copyright (C) 2015 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

#ifndef DECLARATIVETRACE_H
#define DECLARATIVETRACE_H

#include <QObject>
#include <QVariant>
#include <QPointF>

class DeclarativeTracePrivate;

class DeclarativeTrace : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeclarativeTrace)
    Q_PROPERTY(int traceId READ traceId WRITE setTraceId NOTIFY traceIdChanged)
    Q_PROPERTY(QStringList channels READ channels WRITE setChannels NOTIFY channelsChanged)
    Q_PROPERTY(int length READ length NOTIFY lengthChanged)
    Q_PROPERTY(bool isFinal READ isFinal WRITE setFinal NOTIFY finalChanged)
    Q_PROPERTY(bool isCanceled READ isCanceled WRITE setCanceled NOTIFY canceledChanged)
public:
    explicit DeclarativeTrace(QObject *parent = 0);
    ~DeclarativeTrace();

    int traceId() const;
    void setTraceId(int id);

    QStringList channels() const;
    void setChannels(const QStringList &channels);

    int length() const;

    Q_INVOKABLE QVariantList points(int pos = 0, int count = -1) const;
    Q_INVOKABLE int addPoint(const QPointF &point);

    Q_INVOKABLE void setChannelData(const QString &channel, int index, const QVariant &data);
    Q_INVOKABLE QVariantList channelData(const QString &channel, int pos = 0, int count = -1) const;

    bool isFinal() const;
    void setFinal(bool final);

    bool isCanceled() const;
    void setCanceled(bool canceled);

signals:
    void traceIdChanged(int traceId);
    void channelsChanged();
    void lengthChanged(int length);
    void finalChanged(bool isFinal);
    void canceledChanged(bool isCanceled);
};

#endif // DECLARATIVETRACE_H
