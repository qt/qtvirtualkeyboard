// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
    QString imagePath = QLatin1String(":/") + request.path();
    if (request.hasQuery()) {
        const QString query = request.query();
        const QStringList paramList = query.split(QLatin1Char('&'), Qt::SkipEmptyParts);
        QVariantMap params;
        for (const QString &param : paramList) {
            QStringList keyValue = param.split(QLatin1Char('='), Qt::SkipEmptyParts);
            if (keyValue.size() == 2)
                params[keyValue[0]] = keyValue[1];
        }
        const auto widthIt = params.constFind(QLatin1String("width"));
        if (widthIt != params.cend()) {
            bool ok = false;
            int value = widthIt.value().toInt(&ok);
            if (ok)
                imageSize.setWidth(value);
        }
        const auto heightIt = params.constFind(QLatin1String("height"));
        if (heightIt != params.cend()) {
            bool ok = false;
            int value = heightIt.value().toInt(&ok);
            if (ok)
                imageSize.setHeight(value);
        }
    } else {
        imageSize = requestedSize;
    }

    QPixmap image;
    if ((imageSize.width() > 0 || imageSize.height() > 0) && imagePath.endsWith(QLatin1String(".svg"))) {
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
