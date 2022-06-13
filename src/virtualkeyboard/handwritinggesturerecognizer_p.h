// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef HANDWRITINGGESTURERECOGNIZER_P_H
#define HANDWRITINGGESTURERECOGNIZER_P_H

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

#include <QtVirtualKeyboard/private/gesturerecognizer_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Q_VIRTUALKEYBOARD_EXPORT HandwritingGestureRecognizer : public GestureRecognizer
{
    Q_OBJECT
public:
    explicit HandwritingGestureRecognizer(QObject *parent = nullptr);

    void setDpi(int dpi);
    int dpi() const;

    QVariantMap recognize(const QList<QVirtualKeyboardTrace *> traceList) override;

private:
    int m_dpi;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // HANDWRITINGGESTURERECOGNIZER_P_H
