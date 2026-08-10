// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
// Qt-Security score:significant reason:default

#include <QtVirtualKeyboard/private/qvirtualkeyboard_global_p.h>
#include <QtVirtualKeyboard/private/desktopinputpanel_p.h>
#include <QtVirtualKeyboard/private/appinputpanel_p_p.h>
#include <QtVirtualKeyboard/private/inputview_p.h>
#include <QtVirtualKeyboard/private/platforminputcontext_p.h>
#include <QtVirtualKeyboard/private/qvirtualkeyboardinputcontext_p.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QtVirtualKeyboard/private/settings_p.h>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QScreen>
#include <QtVirtualKeyboard/private/virtualkeyboarddebug_p.h>
#include <qpa/qplatformnativeinterface.h>
#include <QtCore/private/qobject_p.h>
#include <QtCore/QLibraryInfo>
#include <QtCore/qpointer.h>
#include <QtGui/qscreen.h>

#include <algorithm>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class DesktopInputPanelPrivate : public AppInputPanelPrivate
{
public:
    enum WindowingSystem {
        Windows,
        Xcb,
        Other,
    };

    DesktopInputPanelPrivate() :
        AppInputPanelPrivate(),
        view(),
        keyboardRect(),
        previewRect(),
        previewVisible(false),
        previewBindingActive(false),
        windowingSystem(Other)
    {
        const QString platformName = QGuiApplication::platformName();
        if (platformName == QLatin1String("windows"))
            windowingSystem = Windows;
        else if (platformName == QLatin1String("xcb"))
            windowingSystem = Xcb;
    }

    QScopedPointer<InputView> view;
    QMetaObject::Connection m_focusWindowVisibleConnection;
    QMetaObject::Connection m_focusWindowScreenConnection;
    QPointer<QScreen> m_screen;
    QPointer<QScreen> m_focusScreen;
    QRectF keyboardRect;
    QRectF previewRect;
    bool previewVisible;
    bool previewBindingActive;
    WindowingSystem windowingSystem;
};

/*!
    \class QtVirtualKeyboard::DesktopInputPanel
    \internal
*/

DesktopInputPanel::DesktopInputPanel(QObject *parent) :
    AppInputPanel(*new DesktopInputPanelPrivate(), parent)
{
    /*  Activate the alpha buffer for this application.
    */
    QQuickWindow::setDefaultAlphaBuffer(true);

    connect(Settings::instance(), &Settings::screenNameChanged,
            this, &DesktopInputPanel::updateEffectiveScreen);
    if (qGuiApp) {
        /*  Re-evaluate the effective screen when screens come and go, so that
            a configured screen is picked up if it is connected later, and
            released when it disappears. */
        connect(qGuiApp, &QGuiApplication::screenAdded,
                this, &DesktopInputPanel::updateEffectiveScreen);
        connect(qGuiApp, &QGuiApplication::screenRemoved,
                this, &DesktopInputPanel::updateEffectiveScreen);
    }
}

DesktopInputPanel::~DesktopInputPanel()
{
}

void DesktopInputPanel::show()
{
    AppInputPanel::show();
    Q_D(DesktopInputPanel);
    if (d->view) {
        if (auto *screen = d->m_screen.isNull() ? QGuiApplication::primaryScreen() : d->m_screen.data())
            repositionView(screen->availableGeometry());
        d->view->show();
    }
}

void DesktopInputPanel::hide()
{
    AppInputPanel::hide();
    Q_D(DesktopInputPanel);
    if (d->view)
        d->view->hide();
}

bool DesktopInputPanel::isVisible() const
{
    return AppInputPanel::isVisible();
}

void DesktopInputPanel::setInputRect(const QRect &inputRect)
{
    Q_D(DesktopInputPanel);
    d->keyboardRect = inputRect;
    updateInputRegion();
}

void DesktopInputPanel::createView()
{
    Q_D(DesktopInputPanel);
    if (!d->view) {
        if (qGuiApp) {
            connect(qGuiApp, SIGNAL(focusWindowChanged(QWindow*)), SLOT(focusWindowChanged(QWindow*)));
            focusWindowChanged(qGuiApp->focusWindow());
        }
        d->view.reset(new InputView());
        d->view->setFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
        /*  Set appropriate WindowType for target environment.
            There seems to be no common type which would
            work in all environments. The purpose of this
            flag is to avoid the window from capturing focus,
            as well as hiding it from the task bar. */
        switch (d->windowingSystem) {
        case DesktopInputPanelPrivate::Xcb:
            d->view->setFlags(d->view->flags() | Qt::Window | Qt::BypassWindowManagerHint);
            break;
        default:
            d->view->setFlags(d->view->flags() | Qt::Tool);
            break;
        }
        d->view->setColor(QColor(Qt::transparent));
#if defined(QT_STATIC)
        d->view->setSource(QUrl(QLatin1String("qrc:///qt-project.org/imports/QtQuick/VirtualKeyboard/InputPanel.qml")));
#else
        d->view->loadFromModule("QtQuick.VirtualKeyboard", "InputPanel");
#endif
        if (QGuiApplication *app = qGuiApp)
            connect(app, SIGNAL(aboutToQuit()), SLOT(destroyView()));
    }
}

void DesktopInputPanel::destroyView()
{
    Q_D(DesktopInputPanel);
    d->view.reset();
    d->previewBindingActive = false;
}

void DesktopInputPanel::repositionView(const QRect &rect)
{
    Q_D(DesktopInputPanel);
    VIRTUALKEYBOARD_DEBUG() << "DesktopInputPanel::repositionView():" << rect;
    if (d->view && d->view->geometry() != rect) {
        QVirtualKeyboardInputContext *inputContext = qobject_cast<PlatformInputContext *>(parent())->inputContext();
        if (inputContext) {
            inputContext->setAnimating(true);
            if (!d->previewBindingActive) {
                QVirtualKeyboardInputContextPrivate *inputContextPrivate = inputContext->priv();
                QObject::connect(inputContextPrivate, &QVirtualKeyboardInputContextPrivate::previewRectangleChanged, this, &DesktopInputPanel::previewRectangleChanged);
                QObject::connect(inputContextPrivate, &QVirtualKeyboardInputContextPrivate::previewVisibleChanged, this, &DesktopInputPanel::previewVisibleChanged);
                d->previewBindingActive = true;
            }
        }
        d->view->setResizeMode(QQuickView::SizeViewToRootObject);
        setInputRect(QRect());
        d->view->setGeometry(rect);
        d->view->setResizeMode(QQuickView::SizeRootObjectToView);
        if (inputContext)
            inputContext->setAnimating(false);
    }
}

void DesktopInputPanel::focusWindowChanged(QWindow *focusWindow)
{
    Q_D(DesktopInputPanel);
    disconnect(d->m_focusWindowVisibleConnection);
    disconnect(d->m_focusWindowScreenConnection);
    if (focusWindow) {
        d->m_focusWindowVisibleConnection =
                connect(focusWindow, &QWindow::visibleChanged,
                        this, &DesktopInputPanel::focusWindowVisibleChanged);
        d->m_focusWindowScreenConnection =
                connect(focusWindow, &QWindow::screenChanged,
                        this, &DesktopInputPanel::screenChanged);
        screenChanged(focusWindow->screen());
    } else {
        /*  Do not clear the tracked focus screen here: the application may
            simply have lost focus to another application. Re-evaluate so that
            a configured screen still takes effect. */
        updateEffectiveScreen();
    }
}

void DesktopInputPanel::screenChanged(QScreen *screen)
{
    Q_D(DesktopInputPanel);
    d->m_focusScreen = screen;
    updateEffectiveScreen();
}

void DesktopInputPanel::updateEffectiveScreen()
{
    Q_D(DesktopInputPanel);

    QScreen *screen = nullptr;
    const QString screenName = Settings::instance()->screenName();
    if (!screenName.isEmpty()) {
        const auto screens = QGuiApplication::screens();
        const auto it = std::find_if(screens.cbegin(), screens.cend(),
                                     [&screenName](QScreen *candidate) {
                                         return candidate->name() == screenName;
                                     });
        if (it != screens.cend())
            screen = *it;
        else
            VIRTUALKEYBOARD_DEBUG() << "DesktopInputPanel: configured screen" << screenName
                                    << "not found, falling back to the default screen";
    }

    if (!screen)
        screen = d->m_focusScreen.data();

    if (d->m_screen.data() == screen)
        return;

    if (!d->m_screen.isNull()) {
        disconnect(d->m_screen.data(), &QScreen::availableGeometryChanged,
                   this, &DesktopInputPanel::repositionView);
    }

    d->m_screen = screen;

    if (!d->m_screen.isNull()) {
        connect(screen, &QScreen::availableGeometryChanged,
                this, &DesktopInputPanel::repositionView, Qt::UniqueConnection);
        repositionView(d->m_screen->availableGeometry());
    }
}

void DesktopInputPanel::focusWindowVisibleChanged(bool visible)
{
    if (!visible) {
        QVirtualKeyboardInputContext *inputContext = qobject_cast<PlatformInputContext *>(parent())->inputContext();
        if (inputContext)
            inputContext->priv()->hideInputPanel();
    }
}

void DesktopInputPanel::previewRectangleChanged()
{
    Q_D(DesktopInputPanel);
    QVirtualKeyboardInputContext *inputContext = qobject_cast<PlatformInputContext *>(parent())->inputContext();
    d->previewRect = inputContext->priv()->previewRectangle();
    if (d->previewVisible)
        updateInputRegion();
}

void DesktopInputPanel::previewVisibleChanged()
{
    Q_D(DesktopInputPanel);
    QVirtualKeyboardInputContext *inputContext = qobject_cast<PlatformInputContext *>(parent())->inputContext();
    d->previewVisible = inputContext->priv()->previewVisible();
    if (d->view->isVisible())
        updateInputRegion();
}

void DesktopInputPanel::updateInputRegion()
{
    Q_D(DesktopInputPanel);

    if (d->view.isNull())
        return;

    // Make sure the native window is created
    if (!d->view->handle())
        d->view->create();

    if (d->keyboardRect.isEmpty()) {
        /*  The view is a transparent window covering the available geometry of
            the screen. Leaving it without an input region would make it consume
            all mouse and touch input on that area, so restrict the input region
            to a region outside the window instead. An empty QRegion cannot be
            used for this, because that resets the mask.
        */
        d->view->setMask(QRegion(-1, -1, 1, 1));
        return;
    }

    QRegion inputRegion(d->keyboardRect.toRect());
    if (d->previewVisible && !d->previewRect.isEmpty())
        inputRegion += d->previewRect.toRect();

    d->view->setMask(inputRegion);
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
