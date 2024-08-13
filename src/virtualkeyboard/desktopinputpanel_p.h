// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
class QScreen;

namespace QtVirtualKeyboard {

class DesktopInputPanelPrivate;

class Q_VIRTUALKEYBOARD_EXPORT DesktopInputPanel : public AppInputPanel
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
    void screenChanged(QScreen *);

protected:
    void updateInputRegion();
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // DESKTOPINPUTPANEL_P_H
