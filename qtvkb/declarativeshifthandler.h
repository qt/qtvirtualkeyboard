/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#ifndef AUTOSHIFTHANDLER_H
#define AUTOSHIFTHANDLER_H

#include <QObject>
#include <QScopedPointer>

class DeclarativeInputContext;
class DeclarativeShiftHandlerPrivate;

class DeclarativeShiftHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarativeShiftHandler)
    Q_DECLARE_PRIVATE(DeclarativeShiftHandler)
    Q_PROPERTY(QString sentenceEndingCharacters READ sentenceEndingCharacters WRITE setSentenceEndingCharacters NOTIFY sentenceEndingCharactersChanged)

    explicit DeclarativeShiftHandler(DeclarativeInputContext* parent = 0);

public:
    ~DeclarativeShiftHandler();

    QString sentenceEndingCharacters() const;
    void setSentenceEndingCharacters(const QString& value);

signals:
    void sentenceEndingCharactersChanged();

private slots:
    void reset();
    void autoCapitalize();
    void restart();

private:
    bool isEnabled() const;

private:
    friend class DeclarativeInputContext;
    QScopedPointer<DeclarativeShiftHandlerPrivate> d_ptr;
};

#endif // AUTOSHIFTHANDLER_H
