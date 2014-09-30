/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

#ifndef DECLARATIVESHIFTHANDLER_H
#define DECLARATIVESHIFTHANDLER_H

#include <QObject>

class DeclarativeInputContext;
class DeclarativeShiftHandlerPrivate;

class DeclarativeShiftHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarativeShiftHandler)
    Q_DECLARE_PRIVATE(DeclarativeShiftHandler)
    Q_PROPERTY(QString sentenceEndingCharacters READ sentenceEndingCharacters WRITE setSentenceEndingCharacters NOTIFY sentenceEndingCharactersChanged)
    Q_PROPERTY(bool autoCapitalizationEnabled READ autoCapitalizationEnabled NOTIFY autoCapitalizationEnabledChanged)
    Q_PROPERTY(bool toggleShiftEnabled READ toggleShiftEnabled NOTIFY toggleShiftEnabledChanged)

    explicit DeclarativeShiftHandler(DeclarativeInputContext *parent = 0);

public:
    ~DeclarativeShiftHandler();

    QString sentenceEndingCharacters() const;
    void setSentenceEndingCharacters(const QString &value);
    bool autoCapitalizationEnabled() const;
    bool toggleShiftEnabled() const;

    Q_INVOKABLE void toggleShift();

signals:
    void sentenceEndingCharactersChanged();
    void toggleShiftEnabledChanged();
    void autoCapitalizationEnabledChanged();

private slots:
    void reset();
    void autoCapitalize();
    void restart();
    void localeChanged();
    void shiftChanged();

private:
    void setAutoCapitalizationEnabled(bool enabled);
    void setToggleShiftEnabled(bool enabled);

private:
    friend class DeclarativeInputContext;
};

#endif // DECLARATIVESHIFTHANDLER_H
