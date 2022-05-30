/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

#ifndef DESKTOPINPUTSELECTIONCONTROL_P_H
#define DESKTOPINPUTSELECTIONCONTROL_P_H

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

#include <QtCore/qpointer.h>
#include <QtCore/qobject.h>
#include <QtGui/qimage.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE

class QMouseEvent;
class QVirtualKeyboardInputContext;

namespace QtVirtualKeyboard {

class InputSelectionHandle;

class QVIRTUALKEYBOARD_EXPORT DesktopInputSelectionControl : public QObject
{
    Q_OBJECT

public:
    DesktopInputSelectionControl(QObject *parent, QVirtualKeyboardInputContext *inputContext);
    ~DesktopInputSelectionControl() {}

    void createHandles();
    void destroyHandles();
    void setEnabled(bool enable);
    QImage *handleImage();

public Q_SLOTS:
    void updateAnchorHandlePosition();
    void updateCursorHandlePosition();
    void updateVisibility();
    void reloadGraphics();
protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    QRect anchorHandleRect() const;
    QRect cursorHandleRect() const;
    QRect handleRectForCursorRect(const QRectF &cursorRect) const;

private:
    QVirtualKeyboardInputContext *m_inputContext;
    QSharedPointer<InputSelectionHandle> m_anchorSelectionHandle;
    QSharedPointer<InputSelectionHandle> m_cursorSelectionHandle;
    QImage m_handleImage;

    enum {
        HandleIsReleased = 0,
        HandleIsHeld = 1,
        HandleIsMoving = 2
    };
    enum HandleType {
        AnchorHandle = 0,
        CursorHandle = 1
    };

    unsigned m_handleState : 2;
    unsigned m_currentDragHandle : 1;
    unsigned m_enabled : 1;
    unsigned m_anchorHandleVisible : 1;
    unsigned m_cursorHandleVisible : 1;
    unsigned m_eventFilterEnabled : 1;
    QPoint m_otherSelectionPoint;
    QList<QMouseEvent*> m_eventQueue;
    QPoint m_distanceBetweenMouseAndCursor;
    QPoint m_handleDragStartedPosition;
    QSize m_handleWindowSize;
};
} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // DESKTOPINPUTSELECTIONCONTROL_P_H
