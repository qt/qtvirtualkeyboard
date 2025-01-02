// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef APPINPUTPANEL_P_P_H
#define APPINPUTPANEL_P_P_H

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

#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/private/qobject_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::AppInputPanelPrivate
    \internal
*/

class Q_VIRTUALKEYBOARD_EXPORT AppInputPanelPrivate : public QObjectPrivate
{
public:
    AppInputPanelPrivate() :
        QObjectPrivate(),
        visible(false)
    {
    }

    bool visible;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // APPINPUTPANEL_P_P_H
