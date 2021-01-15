/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#ifndef DESKTOPINPUTPANEL_P_H
#define DESKTOPINPUTPANEL_P_H

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

#include <QtVirtualKeyboard/private/appinputpanel_p.h>

QT_BEGIN_NAMESPACE

class QWindow;

namespace QtVirtualKeyboard {

class DesktopInputPanelPrivate;

class QVIRTUALKEYBOARD_EXPORT DesktopInputPanel : public AppInputPanel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DesktopInputPanel)
public:
    explicit DesktopInputPanel(QObject *parent = nullptr);
    ~DesktopInputPanel();

    void show() override;
    void hide() override;
    bool isVisible() const override;

    void setInputRect(const QRect &inputRect) override;

public slots:
    void createView() override;
    void destroyView() override;

protected slots:
    void repositionView(const QRect &rect);
    void focusWindowChanged(QWindow *focusWindow);
    void focusWindowVisibleChanged(bool visible);
    void previewRectangleChanged();
    void previewVisibleChanged();

protected:
    void updateInputRegion();
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // DESKTOPINPUTPANEL_P_H
