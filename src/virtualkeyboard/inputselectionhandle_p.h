// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef INPUTSELECTIONHANDLE_P_H
#define INPUTSELECTIONHANDLE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/QRasterWindow>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE

class QWindow;

namespace QtVirtualKeyboard {

class DesktopInputSelectionControl;

class Q_VIRTUALKEYBOARD_EXPORT InputSelectionHandle : public QRasterWindow
{
    Q_OBJECT

public:
    InputSelectionHandle(DesktopInputSelectionControl *control, QWindow *eventWindow);
    void applyImage(const QSize &windowSize);

protected:
    void paintEvent(QPaintEvent *pe) override;
    bool event(QEvent *event) override;

private:
    DesktopInputSelectionControl *m_control;
    QWindow *m_eventWindow;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // INPUTSELECTIONHANDLE_P_H
