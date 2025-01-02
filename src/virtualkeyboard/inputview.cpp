// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/inputview_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::InputView
    \internal
*/

InputView::InputView(QWindow *parent) :
    QQuickView(parent)
{
}

void InputView::resizeEvent(QResizeEvent *event)
{
    QQuickWindow::resizeEvent(event);
    emit sizeChanged();
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
