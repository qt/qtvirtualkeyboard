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

#ifndef T9WRITEINPUTMETHOD_H
#define T9WRITEINPUTMETHOD_H

#include "abstractinputmethod.h"

class T9WriteInputMethodPrivate;

class T9WriteInputMethod : public AbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(T9WriteInputMethod)

public:
    explicit T9WriteInputMethod(QObject *parent = 0);
    ~T9WriteInputMethod();

    QList<DeclarativeInputEngine::InputMode> inputModes(const QString &locale);
    bool setInputMode(const QString &locale, DeclarativeInputEngine::InputMode inputMode);
    bool setTextCase(DeclarativeInputEngine::TextCase textCase);

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    void reset();
    void update();

    QList<DeclarativeSelectionListModel::Type> selectionLists();
    int selectionListItemCount(DeclarativeSelectionListModel::Type type);
    QVariant selectionListData(DeclarativeSelectionListModel::Type type, int index, int role);
    void selectionListItemSelected(DeclarativeSelectionListModel::Type type, int index);

    QList<DeclarativeInputEngine::PatternRecognitionMode> patternRecognitionModes() const;
    DeclarativeTrace *traceBegin(int traceId, DeclarativeInputEngine::PatternRecognitionMode patternRecognitionMode,
                                 const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo);
    bool traceEnd(DeclarativeTrace *trace);

    bool reselect(int cursorPosition, const DeclarativeInputEngine::ReselectFlags &reselectFlags);

protected:
    void timerEvent(QTimerEvent *timerEvent);

protected slots:
    void dictionaryLoadCompleted(const QString &fileUri, void *dictionary);
    void resultsAvailable(const QVariantList &resultList);
};

#endif
