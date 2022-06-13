// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
    QElapsedTimer timer;
    timer.restart();
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    int result = app.exec();

    qDebug() << "Start to finish" << timer.elapsed() << "ms";
    return result;
}
