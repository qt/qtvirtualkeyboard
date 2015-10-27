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

#ifndef TCINPUTMETHOD_H
#define TCINPUTMETHOD_H

#include "abstractinputmethod.h"

namespace QtVirtualKeyboard {

class TCInputMethodPrivate;

class TCInputMethod : public AbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(TCInputMethod)
    Q_PROPERTY(bool simplified READ simplified WRITE setSimplified NOTIFY simplifiedChanged)

public:
    explicit TCInputMethod(QObject *parent = 0);
    ~TCInputMethod();

    bool simplified() const;
    void setSimplified(bool simplified);

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

signals:
    void simplifiedChanged();
};

} // namespace QtVirtualKeyboard

#endif
