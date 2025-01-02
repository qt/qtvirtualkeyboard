// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef INPUTVIEW_P_H
#define INPUTVIEW_P_H

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

#include <QQuickView>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Q_VIRTUALKEYBOARD_EXPORT InputView : public QQuickView
{
    Q_OBJECT
public:
    explicit InputView(QWindow *parent = nullptr);

signals:
    void sizeChanged();

protected:
    void resizeEvent(QResizeEvent *event) override;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // INPUTVIEW_P_H
