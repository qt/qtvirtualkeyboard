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

#ifndef HUNSPELLINPUTMETHOD_P_H
#define HUNSPELLINPUTMETHOD_P_H

#include "hunspellinputmethod.h"
#include "hunspellworker.h"

class HunspellInputMethodPrivate : public AbstractInputMethodPrivate
{
    Q_DECLARE_PUBLIC(HunspellInputMethod)

public:
    HunspellInputMethodPrivate(HunspellInputMethod *q_ptr);
    ~HunspellInputMethodPrivate();

    bool createHunspell(const QString &locale);
    void reset();
    bool updateSuggestions();
    bool clearSuggestions();
    bool hasSuggestions() const;
    bool isAutoSpaceAllowed() const;
    bool isValidInputChar(const QChar &c) const;
    bool isJoiner(const QChar &c) const;

    HunspellInputMethod *q_ptr;
    QScopedPointer<HunspellWorker> hunspellWorker;
    QString locale;
    QString word;
    QStringList wordCandidates;
    int activeWordIndex;
    int wordCompletionPoint;
    bool ignoreUpdate;
    bool autoSpaceAllowed;
};

#endif // HUNSPELLINPUTMETHOD_P_H
