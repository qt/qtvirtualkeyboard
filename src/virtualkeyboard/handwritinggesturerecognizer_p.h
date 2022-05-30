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

class QVIRTUALKEYBOARD_EXPORT HandwritingGestureRecognizer : public GestureRecognizer
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
