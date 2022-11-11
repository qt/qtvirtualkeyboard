// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/unipentrace_p.h>
#include <QRectF>
#include <QDir>
#include <QFile>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

UnipenTrace::UnipenTrace(const QVariantMap &traceCaptureDeviceInfo,
                         const QVariantMap &traceScreenInfo,
                         QObject *parent) :
    QObject(parent)
{
    m_lines.append(QLatin1String(".VERSION 1.0"));
    m_lines.append(QLatin1String(".HIERARCHY CHARACTER"));
    m_lines.append(QLatin1String(".COORD X Y T"));
    m_lines.append(QLatin1String(".SEGMENT CHARACTER"));
    const QRectF boundingBox = traceScreenInfo[QLatin1String("boundingBox")].toRectF();
    if (!boundingBox.isEmpty()) {
        m_lines.append(QStringLiteral(".X_DIM %1").arg(qRound(boundingBox.right())));
        m_lines.append(QStringLiteral(".Y_DIM %1").arg(qRound(boundingBox.bottom())));
    }
    bool ok = false;
    int dpi = traceCaptureDeviceInfo[QLatin1String("dpi")].toInt(&ok);
    if (ok) {
        m_lines.append(QStringLiteral(".X_POINTS_PER_INCH %1").arg(dpi));
        m_lines.append(QStringLiteral(".Y_POINTS_PER_INCH %1").arg(dpi));
    }
    ok = false;
    int sampleRate = traceCaptureDeviceInfo[QLatin1String("sampleRate")].toInt(&ok);
    if (ok)
        m_lines.append(QStringLiteral(".POINTS_PER_SECOND %1").arg(sampleRate));
}

void UnipenTrace::record(const QList<QVirtualKeyboardTrace *> &traceList)
{
    qlonglong t0 = 0;
    for (const QVirtualKeyboardTrace *trace : std::as_const(traceList)) {
        const QVariantList &points = trace->points();
        const bool hasTime = trace->channels().contains(QLatin1String("t"));
        const QVariantList timeData = hasTime ? trace->channelData(QLatin1String("t")) : QVariantList();
        QVariantList::ConstIterator t = timeData.constBegin();
        if (t0 == 0 && hasTime)
            t0 = t->toLongLong();

        m_lines.append(QLatin1String(".PEN_DOWN"));

        for (const QVariant &point : points) {
            const QPointF pt(point.toPointF());
            QString pointStr(QStringLiteral("%1 %2 ").arg(qRound(pt.x())).arg(qRound(pt.y())));
            if (hasTime) {
                pointStr.append(QString::number(t->toLongLong() - t0));
                t++;
            } else {
                pointStr.append(QLatin1String("0"));
            }
            m_lines.append(pointStr);
        }

        m_lines.append(QLatin1String(".PEN_UP"));
    }
}

void UnipenTrace::save(uint unicode, uint confidence)
{
    if (m_directory.isEmpty())
        return;

    QString fileName;
    QDir fileDir(m_directory);
    if (!fileDir.exists())
        fileDir.mkpath(m_directory);
    if (fileDir.exists()) {
        int fileIndex = 0;
        do {
            fileName = fileDir.absoluteFilePath(QStringLiteral("%1_%2_%3.txt").arg(unicode).arg(confidence, 3, 10, QLatin1Char('0')).arg(fileIndex++));
        } while (QFileInfo::exists(fileName));
    }

    QString dataStr(m_lines.join(QLatin1Char('\n')));
    dataStr.append(QLatin1Char('\n'));
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        file.write(dataStr.toUtf8().constData());
    } else {
        qWarning() << "Cannot open file for writing" << fileName;
    }
}

QString UnipenTrace::directory() const
{
    return m_directory;
}

void UnipenTrace::setDirectory(const QString &directory)
{
    m_directory = directory;
}

}
