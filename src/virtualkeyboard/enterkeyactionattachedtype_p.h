// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef ENTERKEYACTIONATTACHEDTYPE_P_H
#define ENTERKEYACTIONATTACHEDTYPE_P_H

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
#include <QtVirtualKeyboard/private/enterkeyaction_p.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Q_VIRTUALKEYBOARD_EXPORT EnterKeyActionAttachedType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int actionId READ actionId WRITE setActionId NOTIFY actionIdChanged)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    QML_ANONYMOUS
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit EnterKeyActionAttachedType(QObject *parent);

    int actionId() const;
    void setActionId(int actionId);
    QString label() const;
    void setLabel(const QString& label);
    bool enabled() const;
    void setEnabled(bool enabled);

signals:
    void actionIdChanged();
    void labelChanged();
    void enabledChanged();

private:
    int m_actionId;
    QString m_label;
    bool m_enabled;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
