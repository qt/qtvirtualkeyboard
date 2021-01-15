/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

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

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class QVIRTUALKEYBOARD_EXPORT UnipenTrace : public QObject
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
