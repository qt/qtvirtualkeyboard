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

#ifndef VIRTUALKEYBOARDATTACHEDTYPE_P_H
#define VIRTUALKEYBOARDATTACHEDTYPE_P_H

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
#include <QtVirtualKeyboard/private/virtualkeyboard_p.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class QVIRTUALKEYBOARD_EXPORT VirtualKeyboardAttachedType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList extraDictionaries READ extraDictionaries WRITE setExtraDictionaries NOTIFY extraDictionariesChanged)

public:
    explicit VirtualKeyboardAttachedType(QObject *parent);

    QStringList extraDictionaries() const;
    void setExtraDictionaries(const QStringList& dictionaries);

signals:
    void extraDictionariesChanged();

private:
    QStringList _extraDictionaries;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
