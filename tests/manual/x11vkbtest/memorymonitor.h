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

#ifndef MEMORYMONITOR_H
#define MEMORYMONITOR_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class QMainWindow;

class MemoryMonitor : public QChart
{
    Q_OBJECT
public:
    explicit MemoryMonitor(QMainWindow &window, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
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
