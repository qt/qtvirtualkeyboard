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

#ifndef ABSTRACTINPUTMETHOD_H
#define ABSTRACTINPUTMETHOD_H

#include "inputengine.h"
#include "selectionlistmodel.h"
#include <QtCore/private/qobject_p.h>

namespace QtVirtualKeyboard {

class AbstractInputMethodPrivate : public QObjectPrivate
{
public:
    AbstractInputMethodPrivate();

    InputEngine *inputEngine;
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

    InputContext *inputContext() const;
    InputEngine *inputEngine() const;

    virtual QList<InputEngine::InputMode> inputModes(const QString &locale) = 0;
    virtual bool setInputMode(const QString &locale, InputEngine::InputMode inputMode) = 0;
    virtual bool setTextCase(InputEngine::TextCase textCase) = 0;

    virtual bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) = 0;

    virtual QList<SelectionListModel::Type> selectionLists();
    virtual int selectionListItemCount(SelectionListModel::Type type);
    virtual QVariant selectionListData(SelectionListModel::Type type, int index, int role);
    virtual void selectionListItemSelected(SelectionListModel::Type type, int index);

    virtual QList<InputEngine::PatternRecognitionMode> patternRecognitionModes() const;
    virtual Trace *traceBegin(int traceId, InputEngine::PatternRecognitionMode patternRecognitionMode,
                              const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo);
    virtual bool traceEnd(Trace *trace);

    virtual bool reselect(int cursorPosition, const InputEngine::ReselectFlags &reselectFlags);

signals:
    void selectionListChanged(int type);
    void selectionListActiveItemChanged(int type, int index);

public slots:
    virtual void reset();
    virtual void update();

private:
    void setInputEngine(InputEngine *inputEngine);

    friend class InputEngine;
};

} // namespace QtVirtualKeyboard

#endif
