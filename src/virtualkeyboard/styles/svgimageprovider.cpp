/****************************************************************************
**
** Copyright (C) 2015 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

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
