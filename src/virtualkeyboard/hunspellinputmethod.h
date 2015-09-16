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

#ifndef HUNSPELLINPUTMETHOD_H
#define HUNSPELLINPUTMETHOD_H

#include "abstractinputmethod.h"

class HunspellInputMethodPrivate;

class HunspellInputMethod : public AbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HunspellInputMethod)
public:
    explicit HunspellInputMethod(QObject *parent = 0);
    ~HunspellInputMethod();

    QList<DeclarativeInputEngine::InputMode> inputModes(const QString &locale);
    bool setInputMode(const QString &locale, DeclarativeInputEngine::InputMode inputMode);
    bool setTextCase(DeclarativeInputEngine::TextCase textCase);

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    QList<DeclarativeSelectionListModel::Type> selectionLists();
    int selectionListItemCount(DeclarativeSelectionListModel::Type type);
    QVariant selectionListData(DeclarativeSelectionListModel::Type type, int index, int role);
    void selectionListItemSelected(DeclarativeSelectionListModel::Type type, int index);

    void reset();
    void update();

protected slots:
    void updateSuggestions(const QStringList &wordList, int activeWordIndex);
};

#endif // HUNSPELLINPUTMETHOD_H
