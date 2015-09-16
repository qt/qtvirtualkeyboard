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

#ifndef ABSTRACTINPUTMETHOD_H
#define ABSTRACTINPUTMETHOD_H

#include "declarativeinputengine.h"
#include "declarativeselectionlistmodel.h"
#include <QtCore/private/qobject_p.h>

class AbstractInputMethodPrivate : public QObjectPrivate
{
public:
    AbstractInputMethodPrivate();

    DeclarativeInputEngine *inputEngine;
};

class AbstractInputMethod : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractInputMethod)

protected:
    AbstractInputMethod(AbstractInputMethodPrivate &dd, QObject *parent = 0);
public:
    explicit AbstractInputMethod(QObject *parent = 0);
    ~AbstractInputMethod();

    DeclarativeInputContext *inputContext() const;
    DeclarativeInputEngine *inputEngine() const;

    virtual QList<DeclarativeInputEngine::InputMode> inputModes(const QString &locale) = 0;
    virtual bool setInputMode(const QString &locale, DeclarativeInputEngine::InputMode inputMode) = 0;
    virtual bool setTextCase(DeclarativeInputEngine::TextCase textCase) = 0;

    virtual bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) = 0;

    virtual QList<DeclarativeSelectionListModel::Type> selectionLists();
    virtual int selectionListItemCount(DeclarativeSelectionListModel::Type type);
    virtual QVariant selectionListData(DeclarativeSelectionListModel::Type type, int index, int role);
    virtual void selectionListItemSelected(DeclarativeSelectionListModel::Type type, int index);

signals:
    void selectionListChanged(int type);
    void selectionListActiveItemChanged(int type, int index);

public slots:
    virtual void reset();
    virtual void update();

private:
    void setInputEngine(DeclarativeInputEngine *inputEngine);

    friend class DeclarativeInputEngine;
};

#endif
