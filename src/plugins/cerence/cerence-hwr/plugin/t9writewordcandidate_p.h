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

#ifndef T9WRITEWORDCANDIDATE_H
#define T9WRITEWORDCANDIDATE_H

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

#include <QString>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class T9WriteWordCandidate
{
public:
    enum class Origin {
        None,
        T9Write,
        XT9
    };

    T9WriteWordCandidate(QString symbs, int resultIndex = -1, Origin origin = Origin::None);

public:
    QString symbs;
    int resultIndex;
    Origin origin;
};

bool operator==(const T9WriteWordCandidate &a, const T9WriteWordCandidate &b);

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // T9WRITEWORDCANDIDATE_H
