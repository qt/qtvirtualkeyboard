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

#include "memorymonitor.h"

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QLoggingCategory>

#include <QMainWindow>
#include <QWindow>
#include <QScreen>
#include <QDir>

#include <QTime>

extern "C" {
#include <unistd.h>
#include <sys/resource.h>
}
#include <cstdio>

namespace  {
const QString KChartFileName = "MemoryUsageChart";
const quint8 KYPosition = 15;
const quint8 KReadingMargin = 80;
const quint16 KToKilo = 1024;
}

Q_LOGGING_CATEGORY(lcMemoryMonitor, "qt.virtualkeyboard.tests.manual.x11vkbtest.memorymonitor")

MemoryMonitor::MemoryMonitor(QMainWindow &window, QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(nullptr),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    m_x(0),
    m_y(0),
    m_peakMemory(0),
    m_minMemory(0),
    m_procID(0),
    m_MainWindow(window),
    m_screen(nullptr),
    m_drawInterval(new QTimer()),
    m_elapsedTime(0),
    m_minMemReading(nullptr),
    m_curMemReading(nullptr),
    m_peakMemReading(nullptr),
    m_elapsedTimeReading(nullptr)
{
    m_series = new QSplineSeries(this);
    QPen red(Qt::red);
    red.setWidth(3);
    m_series->setPen(red);

    this->addSeries(m_series);

    this->addAxis(m_axisX,Qt::AlignBottom);
    m_axisX->setTitleText("Time");
    this->addAxis(m_axisY,Qt::AlignLeft);
    m_axisY->setTitleText("Memory KB");
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
    m_axisX->setTickCount(15);
    m_axisX->setLabelFormat("%.1u");
    m_axisY->setTickCount(15);
    m_axisY->setLabelFormat("%.1u");
    m_axisX->setRange(0, 500);
    m_axisY->setRange(0, 100 * KToKilo);
}

void MemoryMonitor::init()
{
    QWindow *win = m_MainWindow.windowHandle();
    m_screen = win->screen();

    m_minMemReading = new QGraphicsSimpleTextItem(this);
    m_minMemReading->setPen(QPen(QBrush("black"), 1));
    m_minMemReading->setText("Min mem ----- KB");
    m_minMemReading->setPos(KReadingMargin, KYPosition);

    m_curMemReading = new QGraphicsSimpleTextItem(this);
    m_curMemReading->setPen(QPen(QBrush("black"), 1));
    m_curMemReading->setText("Current mem ----- KB");
    m_curMemReading->setPos((this->size().width() / 2) - KReadingMargin, KYPosition);

    m_peakMemReading = new QGraphicsSimpleTextItem(this);
    m_peakMemReading->setPen(QPen(QBrush("black"), 1));
    m_peakMemReading->setText("Peak mem ----- KB");
    m_peakMemReading->setPos(this->size().width() - (KReadingMargin * 2), KYPosition);

    m_elapsedTimeReading = new QGraphicsSimpleTextItem(this);
    m_elapsedTimeReading->setPen(QPen(QBrush("black"), 1));
    m_elapsedTimeReading->setText("-- s");
    m_elapsedTimeReading->setPos((this->size().width() / 2) + KReadingMargin, this->size().height() - KYPosition * 3);

    QObject::connect(this, &QChart::geometryChanged, [this]() {
        m_minMemReading->setPos(KReadingMargin, KYPosition);
        m_curMemReading->setPos((this->size().width() / 2) - KReadingMargin, KYPosition);
        m_peakMemReading->setPos(this->size().width() - (KReadingMargin * 2), KYPosition);
        m_elapsedTimeReading->setPos((this->size().width() / 2) + KReadingMargin, this->size().height() - KYPosition * 3);
    });
}

void MemoryMonitor::setProcID(const qint64 procID)
{
    m_procID = procID;
}

void MemoryMonitor::start()
{
    QObject::connect(m_drawInterval, &QTimer::timeout, [&]() {
        ulong memUsed = currentMemUsage();
        this->drawMemUsage(memUsed);
        this->storeMemValues(memUsed);
    });
    m_drawInterval->setInterval(1000);
    m_drawInterval->start();
}

/**
 * @brief currentMemUsage
 * @param procID
 * @return current memory by procID in kB
 * Getting memory usage of a given process using
 * Linux proc filesystem.
 */
ulong MemoryMonitor::currentMemUsage()
{
    ulong memSize = 0UL;
    QString str = QString("/proc/" + QString::number(m_procID)  + "/statm");
    QFile procFile(str);

    if (procFile.open(QIODevice::ReadOnly)) {
        QTextStream procStream(&procFile);
        ulong mem = procStream.readLine().split(" ").at(1).toULong();
        memSize = mem * static_cast<ulong>(sysconf(_SC_PAGESIZE));
        procFile.close();
    }
    auto result = memSize / KToKilo;
    qCDebug(lcMemoryMonitor).noquote() << QTime::currentTime().toString() << "memory usage:" << result;

    emit memUsage(m_elapsedTime, result);

    return result;
}

MemoryMonitor::~MemoryMonitor()
{
    qCDebug(lcMemoryMonitor) << "Destroying MemoryChart";
}

void MemoryMonitor::saveChart()
{
    QPixmap pix = m_screen->grabWindow(m_MainWindow.winId());

    const QString format = "png";
    QString path = QDir::currentPath();
    path += "/" + KChartFileName + "." + format;
    pix.save(path);
}

void MemoryMonitor::stopChart()
{
    this->saveChart();
    m_drawInterval->stop();

    emit minAndPeakReport(QString("Min process memory: %1 KB\nPeak process memory: %2 KB")
                                .arg(QString::number(m_minMemory))
                                .arg(QString::number(m_peakMemory)));
}

void MemoryMonitor::storeMemValues(const ulong memValue)
{
    if ((m_minMemory == 0 || m_minMemory > memValue)) {
        m_minMemory = memValue;
    }
    if (m_peakMemory < memValue) {
        m_peakMemory = memValue;
    }
    m_minMemReading->setText(QString("Min mem %1 KB").arg(QString::number(m_minMemory)));
    m_curMemReading->setText(QString("Current mem %1 KB").arg(QString::number(memValue)));
    m_peakMemReading->setText(QString("Peak mem %1 KB").arg(QString::number(m_peakMemory)));
    m_elapsedTimeReading->setText(QString("%1 s").arg(m_elapsedTime += 1));
}

void MemoryMonitor::drawMemUsage(const ulong memUsed)
{
    m_x += 1;
    m_y = memUsed;
    if (m_y >= m_axisY->max()) {
        m_axisY->setRange(0, (m_axisY->max() * 2));
    }
    if (m_x >= m_axisX->max()) {
        m_axisX->setRange(0, (m_axisX->max() * 2));
    }
    m_series->append(m_x, m_y);
}
