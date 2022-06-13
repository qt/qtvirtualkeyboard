// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef APPINPUTPANEL_P_H
#define APPINPUTPANEL_P_H

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

#include <QtVirtualKeyboard/private/abstractinputpanel_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class AppInputPanelPrivate;

/*!
    \class QtVirtualKeyboard::AppInputPanel
    \internal
*/

class Q_VIRTUALKEYBOARD_EXPORT AppInputPanel : public AbstractInputPanel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AppInputPanel)

protected:
    AppInputPanel(AppInputPanelPrivate &dd, QObject *parent = nullptr);

public:
    explicit AppInputPanel(QObject *parent = nullptr);
    ~AppInputPanel();

    void show() override;
    void hide() override;
    bool isVisible() const override;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // APPINPUTPANEL_P_H
