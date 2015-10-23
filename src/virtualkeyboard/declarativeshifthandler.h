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

#ifndef DECLARATIVESHIFTHANDLER_H
#define DECLARATIVESHIFTHANDLER_H

#include <QObject>

namespace QtVirtualKeyboard {

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

} // namespace QtVirtualKeyboard

#endif // DECLARATIVESHIFTHANDLER_H
