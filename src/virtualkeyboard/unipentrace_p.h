// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef UNIPENTRACE_H
#define UNIPENTRACE_H

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
#include <QtVirtualKeyboard/qvirtualkeyboardtrace.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Q_VIRTUALKEYBOARD_EXPORT UnipenTrace : public QObject
{
    Q_OBJECT
public:
    explicit UnipenTrace(const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo, QObject *parent = nullptr);

    void record(const QList<QVirtualKeyboardTrace *> &traceList);
    void save(uint unicode, uint confidence);

    QString directory() const;
    void setDirectory(const QString &directory);

private:
    QStringList m_lines;
    QString m_directory;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // UNIPENTRACE_H
