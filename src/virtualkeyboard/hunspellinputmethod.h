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

#ifndef HUNSPELLINPUTMETHOD_H
#define HUNSPELLINPUTMETHOD_H

#include "abstractinputmethod.h"

namespace QtVirtualKeyboard {

class HunspellInputMethodPrivate;

class HunspellInputMethod : public AbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HunspellInputMethod)
protected:
    HunspellInputMethod(HunspellInputMethodPrivate &dd, QObject *parent);
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

    bool reselect(int cursorPosition, const DeclarativeInputEngine::ReselectFlags &reselectFlags);

    void reset();
    void update();

protected slots:
    void updateSuggestions(const QStringList &wordList, int activeWordIndex);
};

} // namespace QtVirtualKeyboard

#endif // HUNSPELLINPUTMETHOD_H
