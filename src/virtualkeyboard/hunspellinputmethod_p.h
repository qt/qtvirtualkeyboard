/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
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
