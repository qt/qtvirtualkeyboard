// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MEMORYMONITOR_H
#define MEMORYMONITOR_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>

QT_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_END_NAMESPACE

class QMainWindow;

class MemoryMonitor : public QChart
{
    Q_OBJECT
public:
    explicit MemoryMonitor(QMainWindow &window, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~MemoryMonitor();

public:
    void init();
    void start();
    void drawMemUsage(const ulong memUsed);
    void setProcID(const qint64 procID);

signals:
    void memUsage(const quint64 timeElapsed, const ulong memSize);
    void minAndPeakReport(const QString minPeakMemoryReport);

public slots:
    void saveChart();
    void stopChart();

private:
    ulong currentMemUsage();
    void storeMemValues(const ulong memValue);

private:
    QSplineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    ulong m_x;
    ulong m_y;
    ulong m_peakMemory;
    ulong m_minMemory;
    qint64 m_procID;
    QMainWindow &m_MainWindow;
    QScreen *m_screen;
    QTimer *m_drawInterval;
    quint64 m_elapsedTime;
    QGraphicsSimpleTextItem *m_minMemReading;
    QGraphicsSimpleTextItem *m_curMemReading;
    QGraphicsSimpleTextItem *m_peakMemReading;
    QGraphicsSimpleTextItem *m_elapsedTimeReading;
};

#endif // MEMORYMONITOR_H
