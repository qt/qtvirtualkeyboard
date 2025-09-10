// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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

class Q_VIRTUALKEYBOARD_EXPORT VirtualKeyboardAttachedType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList extraDictionaries READ extraDictionaries WRITE setExtraDictionaries NOTIFY extraDictionariesChanged)
    QML_ANONYMOUS
    QML_ADDED_IN_VERSION(6, 1)

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
