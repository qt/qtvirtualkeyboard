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

#ifndef INPUTMETHOD_H
#define INPUTMETHOD_H

#include "abstractinputmethod.h"

namespace QtVirtualKeyboard {

class InputMethod : public AbstractInputMethod
{
    Q_OBJECT
    Q_PROPERTY(QtVirtualKeyboard::InputContext *inputContext READ inputContext CONSTANT)
    Q_PROPERTY(QtVirtualKeyboard::InputEngine *inputEngine READ inputEngine CONSTANT)

public:
    explicit InputMethod(QObject *parent = 0);
    ~InputMethod();

    QList<InputEngine::InputMode> inputModes(const QString &locale);
    bool setInputMode(const QString &locale, InputEngine::InputMode inputMode);
    bool setTextCase(InputEngine::TextCase textCase);

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    QList<SelectionListModel::Type> selectionLists();
    int selectionListItemCount(SelectionListModel::Type type);
    QVariant selectionListData(SelectionListModel::Type type, int index, int role);
    void selectionListItemSelected(SelectionListModel::Type type, int index);

    QList<InputEngine::PatternRecognitionMode> patternRecognitionModes() const;
    Trace *traceBegin(int traceId, InputEngine::PatternRecognitionMode patternRecognitionMode,
                      const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo);
    bool traceEnd(Trace *trace);

    bool reselect(int cursorPosition, const InputEngine::ReselectFlags &reselectFlags);

    void reset();
    void update();
};

} // namespace QtVirtualKeyboard

#endif // INPUTMETHOD_H
