// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDBusConnection>
#include <QtVirtualKeyboard>
#include <QObject>
#include <QtDBus/QtDBus>
#include <X11/Xutil.h>

#include <atspi/atspi.h>
#include <dbus/dbus.h>

#include "handlekeyevents.h"
#include "handleatspievents.h"
#include "handledbusforchrome.h"
#include "common_defs.h"

#ifdef QT_TESTING_RUN
    #include "handlelanguagechange.h"
#endif

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    bool error = false;

    QApplication app(argc, argv);

    /** Setup DBus starts */
    auto *extensionHandler = new HandleDbusForChrome(&app);
    if (!QDBusConnection::sessionBus().isConnected()) {
        qWarning() << "Cannot connect to the D-Bus session bus.\n"
                 << "To start it, run:\n"
                 << "\teval `dbus-launch --auto-syntax`\n";
    }

    QDBusConnection::sessionBus().registerObject("/", &app);
    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME))
    {
        qWarning() << "Failed to register D-Bus service x11vkb.chromium.dbus.service: " << qPrintable(QDBusConnection::sessionBus().lastError().message());
    }
    /** Setup DBus ends */

    QQmlApplicationEngine engine(QStringLiteral("qrc:/main.qml"));

    QQmlContext* ctx = engine.rootContext();

    /** Only for testing purpose*/
    #ifdef QT_TESTING_RUN
        ctx->setContextProperty("QT_TESTING_RUN", QVariant(true));
    #endif

    HandleKeyEvents handleKeyEvents;
    if (!handleKeyEvents.init()) {
        qWarning() << "Creation of xdo_t instance failed";
        error = true;
    }
    app.installEventFilter(&handleKeyEvents);
    ctx->setContextProperty("receiver", &handleKeyEvents);

    HandleATSPIEvents handleATSPIEvents;
    if (!handleATSPIEvents.init()) {
        error = true;
    }
    ctx->setContextProperty("atspiFocus", &handleATSPIEvents);

    QObject::connect(extensionHandler, &HandleDbusForChrome::showKeyboard, &handleATSPIEvents, &HandleATSPIEvents::setKeyboardVisible);

    /** Only for testing purpose*/
    #ifdef QT_TESTING_RUN
        HandleLanguageChange hj;
        QObject::connect(engine.rootObjects().last(), SIGNAL(languageChangedSignal(QString)),
                         &hj, SLOT(languageChanged(QString)));
    #endif

    /** If error(s) exit */
    if (!error) {
        return app.exec();
    } else {
        return 1;
    }
}
