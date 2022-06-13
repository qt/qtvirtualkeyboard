// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef SVGIMAGEPROVIDER_H
#define SVGIMAGEPROVIDER_H

#include <QQuickImageProvider>

class SvgImageProvider : public QQuickImageProvider
{
public:
    explicit SvgImageProvider();
    ~SvgImageProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // SVGIMAGEPROVIDER_H

