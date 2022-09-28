// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDTRACE_H
#define QVIRTUALKEYBOARDTRACE_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QPointF>
#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardTracePrivate;

class Q_VIRTUALKEYBOARD_EXPORT QVirtualKeyboardTrace : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QVirtualKeyboardTrace)
    Q_PROPERTY(int traceId READ traceId WRITE setTraceId NOTIFY traceIdChanged)
    Q_PROPERTY(QStringList channels READ channels WRITE setChannels NOTIFY channelsChanged)
    Q_PROPERTY(int length READ length NOTIFY lengthChanged)
    Q_PROPERTY(bool final READ isFinal WRITE setFinal NOTIFY finalChanged)
    Q_PROPERTY(bool canceled READ isCanceled WRITE setCanceled NOTIFY canceledChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    QML_NAMED_ELEMENT(Trace)
    QML_UNCREATABLE("Trace object is created by InputContext.inputEngine.traceBegin() function")
    QML_ADDED_IN_VERSION(2, 0)

public:
    explicit QVirtualKeyboardTrace(QObject *parent = nullptr);
    ~QVirtualKeyboardTrace();

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

    qreal opacity() const;
    void setOpacity(qreal opacity);

    Q_REVISION(6, 1) Q_INVOKABLE void startHideTimer(int delayMs);

protected:
    void timerEvent(QTimerEvent *event) override;

Q_SIGNALS:
    void traceIdChanged(int traceId);
    void channelsChanged();
    void lengthChanged(int length);
    void finalChanged(bool isFinal);
    void canceledChanged(bool isCanceled);
    void opacityChanged(qreal opacity);
};

QT_END_NAMESPACE

#endif // QVIRTUALKEYBOARDTRACE_H
