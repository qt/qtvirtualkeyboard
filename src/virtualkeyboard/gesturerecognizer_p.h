// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef GESTURERECOGNIZER_P_H
#define GESTURERECOGNIZER_P_H

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

#include <QObject>
#include <QVariantMap>
#include <QtVirtualKeyboard/qvirtualkeyboardtrace.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Q_VIRTUALKEYBOARD_EXPORT GestureRecognizer : public QObject
{
    Q_OBJECT
public:
    explicit GestureRecognizer(QObject *parent = nullptr);

    virtual QVariantMap recognize(const QList<QVirtualKeyboardTrace *> traceList) = 0;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // GESTURERECOGNIZER_P_H
