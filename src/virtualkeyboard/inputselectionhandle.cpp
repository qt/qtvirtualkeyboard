// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/inputselectionhandle_p.h>
#include <QtVirtualKeyboard/private/desktopinputselectioncontrol_p.h>

#include <QtCore/qcoreapplication.h>
#include <QtGui/QPainter>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {
InputSelectionHandle::InputSelectionHandle(DesktopInputSelectionControl *control, QWindow *eventWindow)
    : QRasterWindow()
    , m_control(control)
    , m_eventWindow(eventWindow)
{
    setFlags(Qt::ToolTip |
             Qt::FramelessWindowHint |
             Qt::WindowStaysOnTopHint |
             Qt::WindowDoesNotAcceptFocus);

    QSurfaceFormat format;
    format.setAlphaBufferSize(8);
    setFormat(format);
}

void InputSelectionHandle::applyImage(const QSize &windowSize)
{
    resize(windowSize);
    update();   // update paint device in case resize() did not resize.
}

void InputSelectionHandle::paintEvent(QPaintEvent *pe)
{
    Q_UNUSED(pe);
    QPainter painter(this);

    Q_ASSERT(m_control);
    QImage *img = m_control->handleImage();
    const QSize szDelta = size() - img->size();
    // center image onto window
    painter.drawImage(QPoint(szDelta.width(), szDelta.height())/2, *img);
}

bool InputSelectionHandle::event(QEvent *e)
{
    switch (e->type())
    {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
            return QCoreApplication::sendEvent(m_eventWindow, e);
        default:
            break;
    }
    return QRasterWindow::event(e);
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
