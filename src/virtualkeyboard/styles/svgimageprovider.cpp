/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include "svgimageprovider.h"
#include <QImage>
#include <QPixmap>
#include <QSvgRenderer>
#include <QPainter>

SvgImageProvider::SvgImageProvider() :
    QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

SvgImageProvider::~SvgImageProvider()
{
}

QPixmap SvgImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QSize imageSize(-1, -1);
    QUrl request(id);
    QString imagePath = ":/" + request.path();
    if (request.hasQuery()) {
        const QString query = request.query();
        const QStringList paramList = query.split(QChar('&'), QString::SkipEmptyParts);
        QVariantMap params;
        foreach (const QString &param, paramList) {
            QStringList keyValue = param.split(QChar('='), QString::SkipEmptyParts);
            if (keyValue.length() == 2)
                params[keyValue[0]] = keyValue[1];
        }
        if (params.contains("width")) {
            bool ok = false;
            int value = params["width"].toInt(&ok);
            if (ok)
                imageSize.setWidth(value);
        }
        if (params.contains("height")) {
            bool ok = false;
            int value = params["height"].toInt(&ok);
            if (ok)
                imageSize.setHeight(value);
        }
    } else {
        imageSize = requestedSize;
    }

    QPixmap image;
    if ((imageSize.width() > 0 || imageSize.height() > 0) && imagePath.endsWith(".svg")) {
        QSvgRenderer renderer(imagePath);
        QSize defaultSize(renderer.defaultSize());
        if (defaultSize.isEmpty())
            return image;
        if (imageSize.width() <= 0 && imageSize.height() > 0) {
            double aspectRatio = (double)defaultSize.width() / (double)defaultSize.height();
            imageSize.setWidth(qRound(imageSize.height() * aspectRatio));
        } else if (imageSize.width() > 0 && imageSize.height() <= 0) {
            double aspectRatio = (double)defaultSize.width() / (double)defaultSize.height();
            imageSize.setHeight(qRound(imageSize.width() / aspectRatio));
        }
        image = QPixmap(imageSize);
        image.fill(Qt::transparent);
        QPainter painter(&image);
        renderer.render(&painter, image.rect());
    } else {
        image = QPixmap(imagePath);
        imageSize = image.size();
    }

    QPixmap result;
    if (requestedSize.isValid() && requestedSize != imageSize)
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    else
        result = image;

    *size = result.size();

    return result;
}
