/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

#include "desktopinputpanel.h"
#include "inputview.h"
#include "platforminputcontext.h"
#include "declarativeinputcontext.h"
#include <QGuiApplication>
#include <QQmlEngine>
#include <QScreen>
#include "virtualkeyboarddebug.h"
#if defined(QT_VIRTUALKEYBOARD_HAVE_XCB)
#include <xcb/xcb.h>
#include <xcb/xfixes.h>
#endif
#include <qpa/qplatformnativeinterface.h>
#include <QtCore/private/qobject_p.h>
#include <QtCore/QLibraryInfo>

class DesktopInputPanelPrivate : public QObjectPrivate
{
public:
    DesktopInputPanelPrivate() :
        QObjectPrivate(),
        view(),
        keyboardRect(),
        previewRect(),
        previewVisible(false),
        previewBindingActive(false) {}

    QScopedPointer<InputView> view;
    QRectF keyboardRect;
    QRectF previewRect;
    bool previewVisible;
    bool previewBindingActive;
};

DesktopInputPanel::DesktopInputPanel(QObject *parent) :
    AbstractInputPanel(*new DesktopInputPanelPrivate(), parent)
{
    /*  Activate the alpha buffer for this application.
    */
    QQuickWindow::setDefaultAlphaBuffer(true);
    QScreen *screen = QGuiApplication::primaryScreen();
    connect(screen, SIGNAL(virtualGeometryChanged(QRect)), SLOT(repositionView(QRect)));
}

DesktopInputPanel::~DesktopInputPanel()
{
}

void DesktopInputPanel::show()
{
    Q_D(DesktopInputPanel);
    if (d->view) {
        repositionView(QGuiApplication::primaryScreen()->availableGeometry());
        d->view->show();
    }
}

void DesktopInputPanel::hide()
{
    Q_D(DesktopInputPanel);
    if (d->view)
        d->view->hide();
}

bool DesktopInputPanel::isVisible() const
{
    Q_D(const DesktopInputPanel);
    return d->view && d->view->isVisible();
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
#if defined(Q_OS_WIN32)
        d->view->setFlags(d->view->flags() | Qt::Tool);
#elif defined(QT_VIRTUALKEYBOARD_HAVE_XCB)
        d->view->setFlags(d->view->flags() | Qt::Window | Qt::BypassWindowManagerHint);
#else
        d->view->setFlags(d->view->flags() | Qt::ToolTip);
#endif
        d->view->setColor(QColor(Qt::transparent));
        d->view->setSource(QUrl("qrc:///content/InputPanel.qml"));
        /*  Destroy the view along with the last window in application. */
        connect(qGuiApp, SIGNAL(lastWindowClosed()), SLOT(destroyView()));
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
        DeclarativeInputContext *inputContext = qobject_cast<PlatformInputContext *>(parent())->declarativeInputContext();
        if (inputContext) {
            inputContext->setAnimating(true);
            if (!d->previewBindingActive) {
                connect(inputContext, SIGNAL(previewRectangleChanged()), SLOT(previewRectangleChanged()));
                connect(inputContext, SIGNAL(previewVisibleChanged()), SLOT(previewVisibleChanged()));
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
    disconnect(this, SLOT(focusWindowVisibleChanged(bool)));
    if (focusWindow)
        connect(focusWindow, &QWindow::visibleChanged, this, &DesktopInputPanel::focusWindowVisibleChanged);
}

void DesktopInputPanel::focusWindowVisibleChanged(bool visible)
{
    if (!visible) {
        DeclarativeInputContext *inputContext = qobject_cast<PlatformInputContext *>(parent())->declarativeInputContext();
        if (inputContext)
            inputContext->hideInputPanel();
    }
}

void DesktopInputPanel::previewRectangleChanged()
{
    Q_D(DesktopInputPanel);
    DeclarativeInputContext *inputContext = qobject_cast<PlatformInputContext *>(parent())->declarativeInputContext();
    d->previewRect = inputContext->previewRectangle();
    if (d->previewVisible)
        updateInputRegion();
}

void DesktopInputPanel::previewVisibleChanged()
{
    Q_D(DesktopInputPanel);
    DeclarativeInputContext *inputContext = qobject_cast<PlatformInputContext *>(parent())->declarativeInputContext();
    d->previewVisible = inputContext->previewVisible();
    if (d->view->isVisible())
        updateInputRegion();
}

#if defined(QT_VIRTUALKEYBOARD_HAVE_XCB)
static inline xcb_rectangle_t qRectToXCBRectangle(const QRect &r)
{
    xcb_rectangle_t result;
    result.x = qMax(SHRT_MIN, r.x());
    result.y = qMax(SHRT_MIN, r.y());
    result.width = qMin((int)USHRT_MAX, r.width());
    result.height = qMin((int)USHRT_MAX, r.height());
    return result;
}
#endif

void DesktopInputPanel::updateInputRegion()
{
    Q_D(DesktopInputPanel);

    if (d->view.isNull() || d->keyboardRect.isEmpty())
        return;

    // Make sure the native window is created
    if (!d->view->handle())
        d->view->create();

#if defined(QT_VIRTUALKEYBOARD_HAVE_XCB)
    QVector<xcb_rectangle_t> rects;
    rects.push_back(qRectToXCBRectangle(d->keyboardRect.toRect()));
    if (d->previewVisible && !d->previewRect.isEmpty())
        rects.push_back(qRectToXCBRectangle(d->previewRect.toRect()));

    QWindow *window = d->view.data();
    QPlatformNativeInterface *platformNativeInterface = QGuiApplication::platformNativeInterface();
    xcb_connection_t *xbcConnection = static_cast<xcb_connection_t *>(platformNativeInterface->nativeResourceForWindow("connection", window));
    xcb_xfixes_region_t xbcRegion = xcb_generate_id(xbcConnection);
    xcb_xfixes_create_region(xbcConnection, xbcRegion, rects.size(), rects.constData());
    xcb_xfixes_set_window_shape_region(xbcConnection, window->winId(), XCB_SHAPE_SK_INPUT, 0, 0, xbcRegion);
    xcb_xfixes_destroy_region(xbcConnection, xbcRegion);
#else
    QRegion inputRegion(d->keyboardRect.toRect());
    if (d->previewVisible && !d->previewRect.isEmpty())
        inputRegion += d->previewRect.toRect();

    d->view->setMask(inputRegion);
#endif
}
